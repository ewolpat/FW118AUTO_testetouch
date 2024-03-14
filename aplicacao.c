/*	events.c
 * 	Projeto:	Kit Massagens Life
 * 	PCI: 		118 - Controle Touch Life
 *	Micro:		STM8S003F3P - TSSOP20
 *	Data:		23/08/2018
 *	Autor:		Johnatan E. Candaten (Bibliotecas - Antonio Cenci)
 *      Revis�o:        00.00
 *	OBS:		Drive => PCI 111
*/

#include "events.h"
#include "stm8s.h"
#include "stm8_tsl_api.h"
#include "defines.h" 
#include "aplicacao.h" 

extern char KEY_1,KEY_2,KEY_3;
extern char flag_envia_frame;


typedef struct // 
{
    char inicio;
    char endereco_origem;
    char endereco_destino;
    char potencia;
    char checksum;
    char fim;
} frame;
extern frame maqGeral, RECEBIDO_LD_D_maqGeral, RECEBIDO_LD_E_maqGeral;


void aplicacao(void)
{
  trata_teclas();
  trata_leds();
      
}


void trata_teclas(void)
{
  if(KEY_3)
  {
      KEY_3 = 0;
      maqGeral.potencia++;
      if(maqGeral.potencia > 3)
      {
        maqGeral.potencia = 3;
      }
  }
  
  if(KEY_2)
  {
      KEY_2 = 0;
      if(maqGeral.potencia > 0)
      {
        maqGeral.potencia--;
      }
  }
}

void trata_leds(void)
{

  switch(RECEBIDO_LD_D_maqGeral.potencia)
  {
    case 0:
        GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
        break;
    case 1:
        GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
        GPIO_WriteLow(GPIOA, GPIO_PIN_3);
        break;
    case 2:
        GPIO_WriteLow(GPIOC, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
        break;
    case 3:
        GPIO_WriteLow(GPIOC, GPIO_PIN_4);
        GPIO_WriteLow(GPIOA, GPIO_PIN_3);
        break;
    default:
        GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
    break;
  }

  switch(RECEBIDO_LD_E_maqGeral.potencia)
  {
    case 0:
        GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
        GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
        break;
    case 1:
        GPIO_WriteLow(GPIOC, GPIO_PIN_3);
        GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
        break;
    case 2:
        GPIO_WriteLow(GPIOC, GPIO_PIN_3);
        GPIO_WriteLow(GPIOB, GPIO_PIN_4);
        GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
        break;
    case 3:
        GPIO_WriteLow(GPIOC, GPIO_PIN_3);
        GPIO_WriteLow(GPIOB, GPIO_PIN_4);
        GPIO_WriteLow(GPIOB, GPIO_PIN_5);
        break;
    default:
        GPIO_WriteLow(GPIOC, GPIO_PIN_3);
        GPIO_WriteLow(GPIOB, GPIO_PIN_4);
        GPIO_WriteLow(GPIOB, GPIO_PIN_5);
    break;
  }
}