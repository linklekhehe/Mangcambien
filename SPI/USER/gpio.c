#include "gpio.h"
#include "tim.h"

void GPIO_Config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef gpio;
  gpio.GPIO_Pin = LED_PIN;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED_PORT, &gpio);
}

void Debug(void){
  BitAction cur_state = (BitAction)GPIO_ReadOutputDataBit(LED_PORT, LED_PIN);
	GPIO_WriteBit(LED_PORT, LED_PIN, (cur_state == Bit_RESET) ? Bit_SET : Bit_RESET);
  Delay_ms(1000);
}

void On(void){
	GPIO_SetBits(LED_PORT, LED_PIN);
}

void Off(void){
	GPIO_WriteBit(LED_PORT, LED_PIN, Bit_RESET);
}