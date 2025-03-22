#include "usart.h"
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_usart.h"            
#include "misc.h"

void USART_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Kích ho?t clock cho GPIOA

    // C?u hình chân PA2 (TX) và PA3 (RX)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // C?u hình USART
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600; // T?c d? baud
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 8 bit
    USART_InitStruct.USART_StopBits = USART_StopBits_1; // 1 stop bit
    USART_InitStruct.USART_Parity = USART_Parity_No; // Không có parity
    USART_InitStruct.USART_Mode = USART_Mode_Tx; // Ch? truy?n
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Không ki?m soát dòng

    // G?i hàm kh?i t?o USART
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE); // B?t USART1
}
void USART_SendChar(char c){
	while (!(USART1->SR & USART_SR_TXE)); // Ch? cho d?n khi TXE (Transmit Data Register Empty) = 1
    USART_SendData(USART1, c); // G?i ký t?
}
void USART_SendString(char* str) {
    while (*str) {
        USART_SendChar(*str++);
    }
}
