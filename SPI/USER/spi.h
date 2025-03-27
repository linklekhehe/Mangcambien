#ifndef __SPI__H
#define __SPI__H

#include "stm32f10x.h"                  
#include "stm32f10x_spi.h"              
#include "stm32f10x_rcc.h"              

void SPI_Config(void);
uint8_t SPI_SendByte(uint8_t byte);

#endif