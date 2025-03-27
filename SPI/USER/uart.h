#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"  
#include "stm32f10x_usart.h"   
#include "stm32f10x_gpio.h"            
		
void USART_Config(uint32_t baud_rate);
void USART_SendChar( char chr);
void USART_SendString(char* str);
void USART_Send_Data(uint8_t* data, uint8_t length);
void USART_SendNumber(int16_t num);
void USART_SendFloat(float num);
void USART_SendHex(uint8_t num);

#endif