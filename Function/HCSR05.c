#include "stm32f10x.h" // Device header
#include "HCSR05.h"
#include "GPIO.h"
#include "TIM.h"
#include "Delay.h"

#define WINDOW_SIZE 2
#define SOUNDSPEED 34000

static float distance, smooth_distance;
uint32_t count;

float moving_filter(float new_value)
{
    static float window[WINDOW_SIZE] = {0};
    static uint8_t index = 0;
    static float sum = 0;
    static uint8_t count = 0;

    sum -= window[index];
    window[index] = new_value;
    index = (index + 1) % WINDOW_SIZE;
    sum += window[index];

    if(count < WINDOW_SIZE)
        count++;
    
    return sum / count;
}

void HCSR04_Init(void)
{
    MyGPIO_Init(HCSR04_PORT, TRIG, GPIO_Mode_Out_PP);
    GPIO_WriteBit(HCSR04_PORT, TRIG, Bit_RESET);
    MyGPIO_Init(HCSR04_PORT, ECHO, GPIO_Mode_IPD);
    TIM_General_Init(HCSR04_TIM, 20, DISABLE, 2, 1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI1_IRQn;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitTypeDef NVIC_InitTypeDefStruct;
    NVIC_InitTypeDefStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitTypeDefStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitTypeDefStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitTypeDefStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitTypeDefStruct);
}

void TriggerSigner(void)
{
    GPIO_WriteBit(HCSR04_PORT, TRIG, Bit_SET);
    Delay_us(10);
    GPIO_WriteBit(HCSR04_PORT, TRIG, Bit_RESET);
    Delay_ms(10);
}

float GetDistance(void)
{
    if(count == 0)
        return -1.0;
    distance = (float)count / TimerFrequency * SOUNDSPEED / 2;
    smooth_distance = moving_filter(distance);
    return distance;
}

void EXTI1_IRQHandler(void)
{
    if(EXTI_GetFlagStatus(EXTI_Line1) != RESET)
    {
        TIM_Cmd(HCSR04_TIM, ENABLE);
        while(GPIO_ReadInputDataBit(HCSR04_PORT, ECHO) == SET);
        TIM_Cmd(HCSR04_TIM, DISABLE);
        count = TIM_GetCounter(HCSR04_TIM);
        TIM_SetCounter(HCSR04_TIM, 0);
        
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
