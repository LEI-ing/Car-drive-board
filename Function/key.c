#include "stm32f10x.h" // Device header
#include "key.h"
#include "GPIO.h"

void Key_Init(void)
{
    MyGPIO_Init(KEY_PORT, KEY1, GPIO_Mode_IPU);
    MyGPIO_Init(KEY_PORT, KEY2, GPIO_Mode_IPU);
    MyGPIO_Init(KEY_PORT, KEY3, GPIO_Mode_IPU);
    MyGPIO_Init(KEY_PORT, KEY4, GPIO_Mode_IPU);
}
