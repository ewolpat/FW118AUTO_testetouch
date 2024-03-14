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


void Timer1(void) // timer de 1 ms
{
  controle_UART_RX();

  aplicacao();
  verificaTimeoutRX();

  tick_serial();
}

