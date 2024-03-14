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


void Timer1(void) // timer de 1 ms
{
  //controle_UART_RX();

  //aplicacao();
  //verificaTimeoutRX();

  //tick_serial();

  if(++contTeste == 300)
  {
    contTeste = 0;
    GPIO_WriteReverse(GPIOA, GPIO_PIN_3);
  }

  if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_6))
  {
    GPIO_WriteLow(GPIOB, GPIO_PIN_4);
    GPIO_WriteLow(GPIOB, GPIO_PIN_5);
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
      GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
    }


    GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
  }

}

