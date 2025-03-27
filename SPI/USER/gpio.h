#ifndef __GPIO__
#define __GPIO__

#include "stm32f10x.h"    
#include "stm32f10x_gpio.h" 
#include "stm32f10x_rcc.h"             
#include "tim.h"

#define LED_PIN GPIO_Pin_13
#define LED_PORT GPIOC

void GPIO_Config(void);
void Debug(void);
void On (void);
void Off (void);

#endif