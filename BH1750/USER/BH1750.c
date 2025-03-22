#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_i2c.h"              
#include "stm32f10x_rcc.h" 
#include "misc.h"
#include "BH1750.h"

#define BH1750_ADDRESS (0x23 << 1)

void I2C_Start(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);
void I2C_SendDeviceAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_SendByte(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReceiveByte(I2C_TypeDef* I2Cx);

uint16_t BH1750_ReadLight(void) {
    uint8_t data[2];
    I2C_Start(I2C1);
    I2C_SendDeviceAddress(I2C1, BH1750_ADDRESS, 0); // G?i d?a ch? trong ch? d? truy?n
    I2C_SendByte(I2C1, 0x10); // G?i l?nh b?t d?u do
    I2C_Stop(I2C1);

    // Ch? 180ms d? do
    for (volatile int i = 0; i < 180000; i++);

    I2C_Start(I2C1);
    I2C_SendDeviceAddress(I2C1, BH1750_ADDRESS, 1); // G?i d?a ch? trong ch? d? nh?n
    data[0] = I2C_ReceiveByte(I2C1);
    data[1] = I2C_ReceiveByte(I2C1); // Nh?n giá tr? ánh sáng
    I2C_Stop(I2C1);

    // Chuy?n d?i d? li?u thành giá tr? ánh sáng
    return (data[0] << 8) | data[1];
}