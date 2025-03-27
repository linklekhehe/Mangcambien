#include "sys.h"

void Sys_Config(void){
	Timer_Config();
  GPIO_Config();
  USART_Config(9600);
  Delay_ms(200);
  RFID_Init();
  USART_SendString("RFID Reader Initialized\r\n");
  Off();
}

void Sys_Run(void)
{
  //RFID_Debug_ReadCard();
  //On();
	//Delay_ms(1000);
  //Off();
	Debug();
}