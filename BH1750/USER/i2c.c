#include "i2c.h"
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_i2c.h"            
#include "misc.h"

void I2C_Config(void) {
    // Kích ho?t clock cho I2C1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    // Kích ho?t clock cho GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // C?u hình chân PB6 (SCL) và PB7 (SDA)
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // Open Drain
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // C?u hình I2C
    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_ClockSpeed = 100000; // 100 kHz
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00; // Ð?a ch? riêng c?a I2C
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    // G?i hàm kh?i t?o I2C
    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE); // B?t I2C1
}
void I2C_Start(I2C_TypeDef* I2Cx) {
    I2Cx->CR1 |= I2C_CR1_START; // G?i tín hi?u START
    while (!(I2Cx->SR1 & I2C_SR1_SB)); // Ch? cho d?n khi SB (Start Bit) = 1
}
void I2C_SendDeviceAddress(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction) {
    if (direction == 0) { // Transmitter
        address &= ~0x01; // Clear LSB for write
    } else { // Receiver
        address |= 0x01; // Set LSB for read
    }
    I2Cx->DR = address; // G?i d?a ch?
    while (!(I2Cx->SR1 & I2C_SR1_ADDR)); // Ch? cho d?n khi ADDR (Address Sent) = 1
    (void)I2Cx->SR2; // Ð?c SR2 d? xóa c? ADDR
}
void I2C_SendByte(I2C_TypeDef* I2Cx, uint8_t data) {
    I2Cx->DR = data; // G?i d? li?u
    while (!(I2Cx->SR1 & I2C_SR1_TXE)); // Ch? cho d?n khi TXE = 1
}
uint8_t I2C_ReceiveByte(I2C_TypeDef* I2Cx) {
    while (!(I2Cx->SR1 & I2C_SR1_RXNE)); // Ch? cho d?n khi RXNE (Receive Buffer Not Empty) = 1
    return I2Cx->DR; // Tr? v? d? li?u nh?n du?c
}
void I2C_Stop(I2C_TypeDef* I2Cx) {
    I2Cx->CR1 |= I2C_CR1_STOP; // G?i tín hi?u STOP
}