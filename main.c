/* 	MAIN.C file
 * 	Projeto:	Kit Massagens Life
 * 	PCI: 		118 - Controle Touch Life
 *	Micro:		STM8S003F3P - TSSOP20
 *	Data:		23/08/2018
 *	Autor:		Johnatan E. Candaten (Bibliotecas - Antonio Cenci)
 *      Revis�o:        00.00
 *	OBS:		Drive => PCI 111
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8_tsl_api.h"
#include "defines.h"
#include "events.h"
//#include "quantica_lib.h"
#include "stm8s_gpio.h"
#include "stm8s_clk.h"     

#include "stm8s_uart1.h"
#include "stm8s_uart1.c"

#include "stm8s_tim1.h"
//#include "stm8s_tim2.h"
//#include "stm8s_tim4.h"
#include "stm8s_conf.h"

void Clock_Init(void);//funcao do clock
void GPIO_Config(void);//configuracao dos IO
void timer1_config(void);//configuracao dos pwm do canal tim1
//void timer2_config (void);//funcao para base de tempo do timer 2
//void timer4_config (void);//funcao para base de tempo do timer 4
//void Uart1_Init (void);//funcao para configuracao da uart1

/* Private function prototypes -----------------------------------------------*/
void Init_keys(void);
void Application_Action(void);
void Init_uart(void);


/* Private define ------------------------------------------------------------*/
#define KEY01_DETECTED (sSCKeyInfo[0].Setting.b.DETECTED)
#define KEY02_DETECTED (sSCKeyInfo[1].Setting.b.DETECTED)
#define KEY03_DETECTED (sSCKeyInfo[2].Setting.b.DETECTED)

//volatile unsigned char teste = 0;

//variaveis globais do programa
int CheckFlag = 1;
char KEY_1,KEY_2,KEY_3;
char reset;


//FUN��O PRINCIPAL DO C�DIGO
//******************************************************************************
main()
{
  Clock_Init();
  GPIO_Config();
  timer1_config();
  enableInterrupts();
  Init_uart();
  setupInicial_MAQ();

  GPIO_WriteHigh(GPIOA, GPIO_PIN_3);

	while (1)
  {
    controle_UART_TX();
	}

}
//******************************************************************************
//FIM

void Init_uart (void)
{
  UART1_DeInit();

  UART1_Init(9600, 
                UART1_WORDLENGTH_8D, 
                UART1_STOPBITS_1, 
                UART1_PARITY_NO, 
                UART1_SYNCMODE_CLOCK_DISABLE, 
                UART1_MODE_TXRX_ENABLE);
                
  UART1_Cmd(ENABLE);

}

//FUN��O DE INICIALIZA��O DAS TECLAS TOUCH
//******************************************************************************
void Init_keys(void)
{

  u8 i;
  /* All keys are implemented and enabled */

#if NUMBER_OF_SINGLE_CHANNEL_KEYS > 0
  for (i = 0; i < NUMBER_OF_SINGLE_CHANNEL_KEYS; i++)
  {
    sSCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sSCKeyInfo[i].Setting.b.ENABLED = 1;
    sSCKeyInfo[i].DxSGroup = 0x00; /* 0x00 = DxS disabled, other values = DxS enabled */
  }
#endif

#if NUMBER_OF_MULTI_CHANNEL_KEYS > 0
  for (i = 0; i < NUMBER_OF_MULTI_CHANNEL_KEYS; i++)
  {
    sMCKeyInfo[i].Setting.b.IMPLEMENTED = 1;
    sMCKeyInfo[i].Setting.b.ENABLED = 1;
    sMCKeyInfo[i].DxSGroup = 0x00; /* 0x00 = DxS disabled, other values = DxS enabled */
  }
#endif
 
  enableInterrupts();

}
//******************************************************************************
//FIM


//FUN��O DE DETEC��O DAS TECLAS TOUCH
//******************************************************************************
void Application_Action(void){

  if ((TSL_GlobalSetting.b.CHANGED) && (TSLState == TSL_IDLE_STATE))
  {   
    TSL_GlobalSetting.b.CHANGED = 0;
    
    if (KEY01_DETECTED)
    {
      KEY_1=1;
    }
    
    if (KEY02_DETECTED)
    {
      KEY_2=1;	
    }
    
    if (KEY03_DETECTED)
    {
      KEY_3=1;
    }
  }  
}
//******************************************************************************
//FIM

//FUN��O DE CONFIGURA��O DO CLOCK
//Clock: 16Mhz
//******************************************************************************
void Clock_Init(void)
{
  //CLK_HSIPrescalerConfig (CLK_PRESCALER_HSIDIV1);
  CLK->CKDIVR = 0x00;

  CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);           

}
//******************************************************************************
//FIM


//FUN��O DE CONFIGURA��O DOS GPIO
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
//******************************************************************************
void GPIO_Config(void)
{
  
     GPIO_DeInit(GPIOA);//habilita o  port A
     GPIO_DeInit(GPIOB);//habilita o  port B
     GPIO_DeInit(GPIOC);//habilita o  port C
     GPIO_DeInit(GPIOD);//habilita o  port D
     
     
     //PCI 118
     
     
     //GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //LADO ESQUERDO & TERMICO
     //GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);   //LADO DIREITO
     
     //GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);   //MOTOR 1
     //GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //MOTOR 2
                
     GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);    // TX
     GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);         // RX
     
     GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);   //LED LADO ESQUERDO
     GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);   //LED LADO DIREITO & TERMICO
     
     GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 1
     GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 2
     GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 3
     
       
     //PCI 130
     /*
     GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //LADO ESQUERDO & TERMICO
     GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);   //LADO DIREITO
     
     GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);   //MOTOR 1
     GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);   //MOTOR 2
     GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);   //MOTOR 3
     
     GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);   //LED LADO DIREITO
     GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);   //LED LADO ESQUERDO & TERMICO
     
     GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 1
     GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 2
     GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);   //LED POTENCIA 3
     
     GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);   //SAIDA QUANTICA
     */
}
//******************************************************************************
//FIM

//FUN��O DE CONFIGURA��O TIMER 1
//Timer: 2us
//******************************************************************************
void timer1_config(void)
{
  // Time Base configuration
  //---------------------------------
  //Para fins de calculo sempre somar 1 no prescaler
  //TIM1_TimeBaseInit(16, TIM1_COUNTERMODE_UP, 37, 0);
  
  //TIM1_Prescaler = 8
  //TIM1_CounterMode = TIM1_COUNTERMODE_UP
  //TIM1_Period = 47
  //TIM1_RepetitionCounter = 0  
  
  /* Set the Autoreload value */
    //TIM1->ARRH = (uint8_t)(TIM1_Period >> 8);
    //TIM1->ARRL = (uint8_t)(TIM1_Period);
    TIM1->ARRH = (uint8_t)(128 >> 8);
    TIM1->ARRL = (uint8_t)(128);

    /* Set the Prescaler value */
    //TIM1->PSCRH = (uint8_t)(TIM1_Prescaler >> 8);
    //TIM1->PSCRL = (uint8_t)(TIM1_Prescaler);
    TIM1->PSCRH = (uint8_t)(123 >> 8);
    TIM1->PSCRL = (uint8_t)(123);

    /* Select the Counter Mode */
	//TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR)))
    //                       | (uint8_t)(TIM1_CounterMode));
    TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR)))
                           | (uint8_t)(TIM1_COUNTERMODE_UP));

    /* Set the Repetition Counter value */
    //TIM1->RCR = TIM1_RepetitionCounter;
    TIM1->RCR = 0;
  
  // Clear TIM1 update flag
  //---------------------------------
  //TIM1_ClearFlag(TIM1_FLAG_UPDATE);
  
  /* Check the parameters */
    //assert_param(IS_TIM1_CLEAR_FLAG_OK(TIM1_FLAG));
	assert_param(IS_TIM1_CLEAR_FLAG_OK(TIM1_FLAG_UPDATE));

    /* Clear the flags (rc_w0) clear this bit by writing 0. Writing �1� has no effect*/
    TIM1->SR1 = (uint8_t)(~(uint8_t)(TIM1_FLAG_UPDATE));
    TIM1->SR2 = (uint8_t)((uint8_t)(~((uint8_t)((uint16_t)TIM1_FLAG_UPDATE >> 8))) & 
                          (uint8_t)0x1E);
 
  // TIM1 counter enable
  //---------------------------------
  //TIM1_Cmd(ENABLE);
  TIM1->CR1 |= TIM1_CR1_CEN;
  
  //Enable update interrupt
  //---------------------------------
  //TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  //TIM1->IER |= (uint8_t)TIM1_IT;
  TIM1->IER |= (uint8_t)ENABLE;
}
//******************************************************************************
//FIM

