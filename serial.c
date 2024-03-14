#include "events.h"
#include "stm8s.h"
#include "stm8_tsl_api.h"
#include "defines.h" 
#include "serial.h" 

char dadoEnvia[10];
char dadoRecebido[10];
char index_envia;
char flag_envia_frame;
char index_RX;
char contTimeoutRx;
char cks;
int cont;
int contTimeOutSerial_LD;
int contTimeOutSerial_LE;


#define CARACTER_INICIO 5
#define CARACTER_FINAL  6
#define MEU_ENDERECO    10
#define ENDERECO_CONTROLE_LD_DIREITO  11
#define ENDERECO_CONTROLE_LD_ESQUERDO 12

typedef struct // 
{
    char inicio_recebido;
    char final_recebido;
    char checksum_validado;
} protocoloControle;

protocoloControle protocolo;

typedef struct // 
{
    char inicio;
    char endereco_origem;
    char endereco_destino;
    char potencia;
    char checksum;
    char fim;
} frame;

frame maqGeral, maqGeralOld, RECEBIDO_LD_D_maqGeral, RECEBIDO_LD_E_maqGeral;

void setupInicial_MAQ(void)
{
  maqGeral.inicio           = 5;
  maqGeral.endereco_origem  = MEU_ENDERECO;
  //maqGeral.endereco_destino = 11;
  maqGeral.potencia         = 0;
  maqGeral.checksum         = 0;
  maqGeral.fim              = 6;
}

char dadosalterados (void)
{
  char alterado = 0;
    if(maqGeralOld.inicio != maqGeral.inicio)
    {
      maqGeralOld.inicio = maqGeral.inicio;
      alterado = 1;
    }

    if(maqGeralOld.endereco_origem != maqGeral.endereco_origem)
    {
      maqGeralOld.endereco_origem = maqGeral.endereco_origem;
      alterado = 1;
    }

    if(maqGeralOld.endereco_destino != maqGeral.endereco_destino)
    {
      maqGeralOld.endereco_destino = maqGeral.endereco_destino;
      alterado = 1;
    }

    if(maqGeralOld.potencia != maqGeral.potencia)
    {
      maqGeralOld.potencia = maqGeral.potencia;
      alterado = 1;
    }

    if(maqGeralOld.checksum != maqGeral.checksum)
    {
      maqGeralOld.checksum = maqGeral.checksum;
      alterado = 1;
    }

    if(maqGeralOld.fim != maqGeral.fim)
    {
      maqGeralOld.fim = maqGeral.fim;
      alterado = 1;
    }

    if(alterado)
    {
      maqGeral.checksum = maqGeralOld.inicio + maqGeralOld.endereco_origem + maqGeralOld.endereco_destino + maqGeralOld.potencia;
      maqGeralOld.checksum = maqGeral.checksum;
    }

    return alterado;
}

void tick_serial(void)
{
  cont++;
  if(cont == 400)
  {
    maqGeral.endereco_destino = ENDERECO_CONTROLE_LD_DIREITO;
    flag_envia_frame = 1;
  }
  else if(cont > 800)
  {
    maqGeral.endereco_destino = ENDERECO_CONTROLE_LD_ESQUERDO;
    flag_envia_frame = 1;
    cont = 0;
  }


  contTimeOutSerial_LD++;
  if(contTimeOutSerial_LD > 2000)
  {
    contTimeOutSerial_LD = 0;
    RECEBIDO_LD_D_maqGeral.potencia = 0;
  }

  contTimeOutSerial_LE++;
  if(contTimeOutSerial_LE > 2000)
  {
    contTimeOutSerial_LE = 0;
    RECEBIDO_LD_E_maqGeral.potencia = 0;
  }
}

void controle_UART_TX(void) // roda periodicamente no while
{
  if(dadosalterados()); // NÃO REMOVER IF - CALCULA CKS DENTRO DESTA FUNÇÃO
  {
    dadoEnvia[0] = maqGeral.inicio;
    //dadoEnvia[1] = maqGeral.endereco_origem;
    //dadoEnvia[2] = maqGeral.endereco_destino;
    //dadoEnvia[3] = maqGeral.potencia;

    dadoEnvia[1] = maqGeral.endereco_origem;
    dadoEnvia[2] = maqGeral.endereco_destino;
    dadoEnvia[3] = maqGeral.potencia;

    dadoEnvia[4] = maqGeral.checksum;
    dadoEnvia[5] = maqGeral.fim;
    
  }

  if(flag_envia_frame)
  {
    if(UART1->SR & (1 << 6))
    {
      UART1_SendData8(dadoEnvia[index_envia]);
      index_envia++;
    }
    if(index_envia > 5)
    {
      index_envia = 0;
      flag_envia_frame = 0;
    }
  }
}

void verificaTimeoutRX(void)
{
  if(index_RX > 0)
  {
    ++contTimeoutRx;
    if(contTimeoutRx > 30)
    {
      resetVariaveisProtocolo();

      contTimeoutRx = 0;
    }
  }
}

void resetVariaveisProtocolo(void)
{
  cks = 0;
  index_RX = 0;
  protocolo.inicio_recebido = 0;
  protocolo.final_recebido = 0;
  protocolo.checksum_validado = 0;
}

void atualizaVariaveisRecebidas(void)
{
  if(dadoRecebido[1] == ENDERECO_CONTROLE_LD_DIREITO)
  {
    RECEBIDO_LD_D_maqGeral.potencia = dadoRecebido[3];
    contTimeOutSerial_LD = 0;
  }
  else if(dadoRecebido[1] == ENDERECO_CONTROLE_LD_ESQUERDO)
  {
    RECEBIDO_LD_E_maqGeral.potencia = dadoRecebido[3];
    contTimeOutSerial_LE = 0;
  }
}

void reserVetorRecebimento(void)
{
  dadoRecebido[0] = 0;
  dadoRecebido[1] = 0;
  dadoRecebido[2] = 0;
  dadoRecebido[3] = 0;
  dadoRecebido[4] = 0;
  dadoRecebido[5] = 0;
  dadoRecebido[6] = 0;
  dadoRecebido[7] = 0;
  dadoRecebido[8] = 0;
  dadoRecebido[9] = 0;

}

void identifica_inicioEfim(void)
{
  if(index_RX > 0)
  {
    if(dadoRecebido[index_RX - 1] == CARACTER_INICIO)
    {
      protocolo.inicio_recebido = 1;
    }

    if(protocolo.inicio_recebido  == 1 &&
        dadoRecebido[index_RX - 1] == CARACTER_FINAL)
    {
      protocolo.final_recebido = 1;
    }
  }
}

void verificaChecksum(void)
{
  if(index_RX > 2)
  {
    if(protocolo.inicio_recebido == 1 &&
       protocolo.final_recebido  == 1)
      {
        cks = 0;
        char i;
        for(i=0; i<(index_RX-2); i++)
        {
          cks = cks + dadoRecebido[i];
        }

        if(dadoRecebido[index_RX - 2] == cks)
        {
          protocolo.checksum_validado = 1;
        }
        else
        {
          resetVariaveisProtocolo();
          reserVetorRecebimento();
        }
      }
  }
}

void verificaEndereco(void)
{
  if(index_RX > 2)
  {
    if(protocolo.checksum_validado == 1)
    {
      if(dadoRecebido[2] == MEU_ENDERECO)
      {
        atualizaVariaveisRecebidas();
      }

      resetVariaveisProtocolo();
      reserVetorRecebimento();
    }
  }
}

void controle_UART_RX(void)
{
  if (UART1->SR & (1 << 5)) {
    contTimeoutRx = 0;
    dadoRecebido[index_RX++] = UART1_ReceiveData8();

    if(index_RX > 6)
    {
      resetVariaveisProtocolo();
    }

    identifica_inicioEfim();
    verificaChecksum();
    verificaEndereco();

  }
}
