#include "stm32f10x.h"          // Thu vi?n cho STM32F103
#include "i2c.h"      // Thu vi?n cho I2C
#include "usart.h"    // Thu vi?n cho USART
#include "stdio.h"
#include "BH1750.h"

int main(void) {
    // C?u hình I2C và USART
    I2C_Config();
    USART_Config();

    while (1) {
        // Ð?c giá tr? ánh sáng t? BH1750
        uint16_t lightValue = BH1750_ReadLight();

        // Chuy?n d?i giá tr? thành chu?i d? g?i qua UART
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Light: %d lux\r\n", lightValue);
        USART_SendString(buffer);

        // Thêm d? tr? tru?c l?n d?c ti?p theo
        for (volatile int i = 0; i < 1000000; i++);
    }
}