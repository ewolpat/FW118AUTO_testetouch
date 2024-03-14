//----------------------------------------------------------------------------------------------+
//          A T I V I T A   A   M A R C A   D O   B E M   E S T A R                             |
//                                                                                              |
//  File: stm8s_DispLed.c                                                                       |
//                                                                                              |
//  Produto: Geral                                                                              |
//                                                                                              |
//  Descrição: Rotinas para tratar de estruturas de display de Leds                             |
//  Desenvolvimento: Marcio Lafourcade Rodrigues                                                |
//  Inicio: 05/04/2017                                                                          |
//  Atualização: 05/04/2017                                                                     |
//                                                                                              |
//  Modelo da Placa: Geral                                                                      |
//                                                                                              |
//                                                                                              |
//----------------------------------------------------------------------------------------------+

//----------------------------------------------------------------------------------------------+
// Includes
#include "main.h"
#include "stm8s_gpio.h"
#include "stm8s_DispLed.h"
#include "structs.h"
//----------------------------------------------------------------------------------------------+

//----------------------------------------------------------------------------------------------+
//Global Variables
u8 Switchable;      
                    //  0    1    2    3    4    5    6    7    8    9   Blank   A     E     F     i     n     o     r 
u8 MatrixDigit[18] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F, 0x00, 0x77, 0x79, 0x71, 0x04, 0x54, 0x5C, 0x50};
//----------------------------------------------------------------------------------------------+

//----------------------------------------------------------------------------------------------+
//0x01 = A
//0x02 = B
//0x04 = C
//0x08 = D
//0x10 = E
//0x20 = F
//0x40 = G
//0x80 = Point
//----------------------------------------------------------------------------------------------+

//----------------------------------------------------------------------------------------------+
void DSP7SEG_Write (u16 DSPChar)
{
     u8 Unid, Dez, Cen, Mil;
     
     GPIO_WriteLow(DSP1);
     GPIO_WriteLow(DSP2);
     GPIO_WriteLow(DSP3);
     GPIO_WriteLow(DSP4);
  
	 if (sysvar.PontoHoraBit)
		GPIO_WriteHigh(PONTO_HORA);
	 else 
		GPIO_WriteLow(PONTO_HORA);

     if(sysvar.TestEnd)
     {
          Unid = 11;
          Dez = 15;
          Cen = 14;
          Mil = 13;
          sysvar.PontoDsp = 0;
     }
     else if (sysvar.FaultEvent > 0)
     {
          Unid = 16;
          Dez = 17;
          Cen = 17;
          Mil = 12;
          sysvar.PontoDsp = 0;
     }
     else
     {
          Unid = DSPChar%10;
          Dez = (DSPChar%100)/10;
          Cen = (DSPChar%1000)/100;
          Mil = (DSPChar/1000);
     }
     
     switch(Switchable)
     {
          case 0:
               GPIO_Write(GPIOB, MatrixDigit[Unid]);
               Switchable = 1;
               GPIO_WriteHigh(DSP4);
          break;
            
          case 1:
               GPIO_Write(GPIOB,  MatrixDigit[Dez] | (sysvar.PontoDsp << 7));
               Switchable = 2;
               GPIO_WriteHigh(DSP3);
          break;

          case 2:
               GPIO_Write(GPIOB,  MatrixDigit[Cen]);
               Switchable = 3;
               GPIO_WriteHigh(DSP2);
          break;

          default:
               GPIO_Write(GPIOB, MatrixDigit[Mil]);
               Switchable = 0;
               GPIO_WriteHigh(DSP1);
          break;
     }
}
//----------------------------------------------------------------------------------------------+

