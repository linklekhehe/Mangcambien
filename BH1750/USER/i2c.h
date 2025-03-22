#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
void I2C_Config(void);
void I2C_Start(I2C_TypeDef* I2Cx);
void I2C_SendDeviceAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_SendByte(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReceiveByte(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);

#endif