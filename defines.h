/* 	defines.h file
 * 	Projeto:	Kit Massagens Life
 * 	PCI: 		118 - Controle Touch Life
 *	Micro:		STM8S003F3P - TSSOP20
 *	Data:		23/08/2018
 *	Autor:		Johnatan E. Candaten (Bibliotecas - Antonio Cenci)
 *      Revis�o:        00.00
 *	OBS:		Drive => PCI 111
 * 
*/
/*
                       STM8S003F3P - TSSOP 20
                         ________________
            TL_LIGA __1_|PD4          PD3|_20_ LOAD
            MOTOR2D __2_|PD5          PD2|_19_ MOTOR2E
            MOTOR1D __3_|PD6     SWIM PD1|_18_
                    __4_|RESET        PC7|_17_ TL_POTENCIA
           QUANTICA __5_|PA1          PC6|_16_ TL_LADO
                    __6_|PA2          PC5|_15_ MOTOR1E
                    __7_|GND          PC4|_14_ LD_LADO_E
                    __8_|VCAP         PC3|_13_ LD_POT1
                    __9_|VCC          PB4|_12_ LD_POT2
          LD_LADO_D _10_|PA3          PB5|_11_ LD_POT3
                        |________________|
*/

#include "stm8s.h"
//#include "main.h"
#include "stm8s_gpio.h"
 
//PCI 118
#define Potencia_1      GPIOC, GPIO_PIN_3       // LED POTENCIA 1
#define Potencia_2	GPIOB, GPIO_PIN_4       // LED POTENCIA 2
#define Potencia_3	GPIOB, GPIO_PIN_5       // LED POTENCIA 1
#define Saida_Quantica  GPIOA, GPIO_PIN_1       // QUANTICA
#define motor_1         GPIOD, GPIO_PIN_6       // Motor 1D
#define motor_2         GPIOD, GPIO_PIN_5       // Motor 2D
//#define motor_3       GPIOC, GPIO_PIN_5       // Motor 3D
//#define motor_4       GPIOD, GPIO_PIN_2       // Motor 4D
#define motor_e         GPIOC, GPIO_PIN_5       // Lado Esquerdo
#define motor_d         GPIOD, GPIO_PIN_2       // Lado Direito
#define LADO_D          GPIOA, GPIO_PIN_3       // LED LADO DIREITO
#define LADO_E		      GPIOC, GPIO_PIN_4       // LED LADO ESQUERDO


// PCI 130
/*
#define Potencia_1      GPIOC, GPIO_PIN_6       // LED POTENCIA 1
#define Potencia_2	GPIOC, GPIO_PIN_5       // LED POTENCIA 2
#define Potencia_3	GPIOC, GPIO_PIN_4       // LED POTENCIA 1
#define Saida_Quantica  GPIOD, GPIO_PIN_5       // QUANTICA
#define motor_1         GPIOD, GPIO_PIN_6       // Motor 1D
#define motor_2         GPIOC, GPIO_PIN_3       // Motor 2D
#define motor_3         GPIOA, GPIO_PIN_2       // Motor 3D
#define motor_e         GPIOB, GPIO_PIN_5       // Lado Esquerdo
//#define TERMICO         GPIOB, GPIO_PIN_5       // Lado Aquecimento
#define motor_d         GPIOB, GPIO_PIN_4       // Lado Direito
#define LADO_D          GPIOA, GPIO_PIN_3       // LED LADO ESQUERDO & TERMICO
//#define LD_TERMICO      GPIOA, GPIO_PIN_3       // LED LADO ESQUERDO & TERMICO
#define LADO_E		GPIOA, GPIO_PIN_1       // LED LADO DIREITO
*/
