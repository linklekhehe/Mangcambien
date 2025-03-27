#include "spi.h"

void SPI_Config(void){
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef gpio;
	SPI_InitTypeDef spi;
	
	// Configure SPI2 pins: SCK, MISO and MOSI
	gpio.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &gpio);
	
	//miso pin
	gpio.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_Pin=GPIO_Pin_14;
	GPIO_Init(GPIOB, &gpio);
	
	// Configure SPI2
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS = SPI_NSS_Soft;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &spi);
	
	SPI_Cmd(SPI2, ENABLE);
}

uint8_t SPI_SendByte(uint8_t byte){
	// Wait until transmit buffer is empty
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  // Send byte to SPI2
  SPI_I2S_SendData(SPI2, byte);
  // Wait to receive a byte
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
  // Return the byte read from the SPI bus
  return SPI_I2S_ReceiveData(SPI2);
}