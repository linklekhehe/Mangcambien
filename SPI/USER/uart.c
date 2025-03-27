#include "uart.h"

void USART_Config(uint32_t baud_rate){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef gpio;
    
  //PA9 - Tx
  gpio.GPIO_Pin = GPIO_Pin_9;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &gpio);

  //PA10 - Rx
  gpio.GPIO_Pin = GPIO_Pin_10;
  gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio);

  USART_InitTypeDef uart;
	
  uart.USART_BaudRate = baud_rate;
  uart.USART_WordLength = USART_WordLength_8b;
  uart.USART_StopBits = USART_StopBits_1;
  uart.USART_Parity = USART_Parity_No;
  uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &uart);
  USART_Cmd(USART1, ENABLE);
}

void USART_SendChar(char chr){
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, (uint8_t)chr); 
}

void USART_SendString(char *str){
	while(*str){
		USART_SendData(USART1, *str);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		str++;
	}
}

void USART_Send_Data(uint8_t* data, uint8_t length){
	int i;
  for(i = 0; i < length; i++){
    while(!(USART1->SR & ( 1 << 7)));
		USART1->DR = data[i];
  }
}

void USART_SendNumber(int16_t num){
  if(num < 0) {
		USART_SendChar('-');
    num = -num;
  }
  uint8_t length = 0;
  uint8_t temp[10];
  if(num == 0) {
		USART_SendChar('0');
    return;
  }else{
		while(num != 0) {
			uint8_t value = num % 10;
      temp[length++] = value + '0';
      num /= 10;
    }
		int i;
    for(i = length - 1; i >= 0; i--){
			USART_SendChar(temp[i]);
    }
  }
}

void USART_SendFloat(float num){
  if (num < 0) {
		USART_SendChar('-');
    num = -num;
  }
  int16_t integer = (int16_t)num;
  float decimal = num - integer;
  USART_SendNumber(integer);
  USART_SendChar('.');
  decimal *= 1000;
  USART_SendNumber((int16_t)decimal);
}

void USART_SendHex(uint8_t num){
	uint8_t temp;
  temp = num >> 4;
  if(temp > 9){
		temp += 0x37;
  }else{
    temp += 0x30;
  }
  USART_SendChar(temp);
  temp = num & 0x0F;
  if(temp > 9){
		temp += 0x37;
  }else{
    temp += 0x30;
  }
  USART_SendChar(temp);
}