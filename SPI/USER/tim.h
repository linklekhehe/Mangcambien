#ifndef __TIM2_H__
#define __TIM2_H__

#include "stm32f10x.h"                 
#include "stm32f10x_tim.h"          

void Timer_Config(void);
void Delay_us(uint16_t us);
void Delay_ms(uint32_t ms);

#endif