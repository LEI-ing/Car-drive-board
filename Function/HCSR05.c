#include "stm32f10x.h" // Device header
#include "HCSR05.h"
#include "Delay.h"

void HCSR04_Init(void)
{
    RCC_APB2PeriphClockCmd(HCSR04_PORT, ENABLE);
    RCC_APB1PeriphClockCmd(HCSR04_TIM, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = 

    GPIO_Init(HCSR04_PORT, &GPIO_InitStruct);
}

void TriggerSigner(void)
{

}
