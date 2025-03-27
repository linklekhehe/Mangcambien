#include "tim.h"

void Timer_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitTypeDef timer;
	timer.TIM_Period = 0xFFFF;
	timer.TIM_Prescaler = 72 - 1; //f_timer = 1MHz;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &timer);
	TIM_Cmd(TIM2, ENABLE);
}

void Delay_ms(uint32_t time){
	while(time--) {
		Delay_us(1000);
  }
}

void Delay_us(uint16_t time){
  TIM_SetCounter(TIM2, 0);
  while(TIM_GetCounter(TIM2) < time);
}