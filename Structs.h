/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STRUCTS_H
#define __STRUCTS_H

//--------------------------------------------------------------------------/
//  Variaveis usadas na rotina da constante de tempo
//--------------------------------------------------------------------------/
typedef struct 
{
     uint8_t TestEnd:1;
     uint8_t OnOff:1;
     uint8_t PontoDsp:1;
     uint8_t EnableOut:1;
     uint8_t PontoHoraBit:1;
	 
     uint8_t DesKey:1;
	 
     uint16_t DBCKey;
     uint8_t StoreKey;
	 
     uint8_t ano;
     uint16_t time;
     uint8_t Time_index;

     uint8_t CntSetTimer;
     uint8_t FaultEvent;
     uint8_t StateMachine;
     uint8_t BlinkLed;
     uint8_t SecurTime;
     uint8_t ShowChannel;
     uint8_t um_segundo;

     uint16_t TimeOnOff;
     uint16_t Contador;
     uint16_t mili_segundo;
     uint16_t segundo;

     uint32_t TimeStamp;
     uint32_t TimerCounter;
     uint32_t VoltageValue;
     
     float calc1;
     float calc2;
  
} _SysVar;
extern volatile _SysVar sysvar;
//--------------------------------------------------------------------------/

//--------------------------------------------------------------------------/
//  Variaveis usadas na rotina da constante de tempo
//--------------------------------------------------------------------------/
typedef struct 
{
     uint8_t Enable;
     uint8_t ChannelSel;

     uint16_t CntAdValue1;
     uint16_t AdValue1;
     uint32_t StoreAdValue1;
     
     uint16_t CntAdValue2;
     uint16_t AdValue2;
     uint32_t StoreAdValue2;
} _AdVar;
extern volatile _AdVar advar;
//--------------------------------------------------------------------------/

//--------------------------------------------------------------------------/
//  Variaveis usadas na rotina da constante de tempo
//--------------------------------------------------------------------------/
typedef struct 
{
     uint8_t BleSend:1;
     uint8_t BLEhit:1;
     uint8_t PackReceived:1;
     uint8_t TimerSend:1;

     uint8_t cntcmd;
     uint8_t cntsent;
     uint8_t cntdata;
     uint8_t cmd[2];
     uint8_t size;
     uint8_t data[16];
     uint8_t index;
     uint8_t CntTimerSend;
     uint16_t CountBuffer;
} _UartVar;
extern volatile _UartVar uart_var;
//--------------------------------------------------------------------------/




#endif 
