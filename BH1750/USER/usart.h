#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

void USART_Config(void);
void USART_SendChar(char c);
void USART_SendString(char* str);

#endif