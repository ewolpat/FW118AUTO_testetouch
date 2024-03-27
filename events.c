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



int cont_process = 0;
int cont_motor = 0;
//int cont_quant = 0;
int contTeste;

char desacopla;
char contDesliga;

int filtroTouchTimeout;
int contFiltroLeTecla;
int FiltroEstagio_0;
int FiltroEstagio_1;
int FiltroEstagio_2;
char teclaAcionada;

#define FILTRO_TARGET 3 // quantos pultos em 100 mili segundos


void Timer1(void) // timer de 1 ms
{
  //controle_UART_RX();

  //aplicacao();
  //verificaTimeoutRX();

  //tick_serial();

  if(++contTeste == 300)
  {
    contTeste = 0;
    //GPIO_WriteReverse(GPIOC, GPIO_PIN_7);
  }

  contFiltroLeTecla++;
  if(!GPIO_ReadInputPin(GPIOA, GPIO_PIN_1))
  {
    

    filtroTouchTimeout = 0;
    if(contFiltroLeTecla >= 0 && contFiltroLeTecla < 50)
    {
      FiltroEstagio_0++;
    }
    else if(contFiltroLeTecla >= 50 && contFiltroLeTecla < 100)
    {
      FiltroEstagio_1++;
    }
    else if(contFiltroLeTecla >= 100 && contFiltroLeTecla < 150)
    {
      FiltroEstagio_2++;
    }
    else
    {
      contFiltroLeTecla = 0;
      FiltroEstagio_0 = 0;
      FiltroEstagio_1 = 0;
      FiltroEstagio_2 = 0;
    }
  }
  else
  {
    filtroTouchTimeout++;
    if(filtroTouchTimeout > 50)
    {
      filtroTouchTimeout = 0;
      contFiltroLeTecla = 0;
      FiltroEstagio_0 = 0;
      FiltroEstagio_1 = 0;
      FiltroEstagio_2 = 0;
      teclaAcionada = 0;
    }
  }

  if(FiltroEstagio_0 > FILTRO_TARGET &&
     FiltroEstagio_1 > FILTRO_TARGET &&
     FiltroEstagio_2 > FILTRO_TARGET)
  {
    teclaAcionada = 1;
  }


  if(teclaAcionada)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_7);
    if(desacopla == 0)
    {
      desacopla = 1;
      contDesliga++;
    }
  }
  else
  {
    desacopla = 0;
    if(contDesliga > 10)
    {
      contDesliga = 0;
      GPIO_WriteLow(GPIOC, GPIO_PIN_7);
    }
  }

}

