#include "stm32f10x.h" // Device header
#include "HCSR05.h"
#include "GPIO.h"
#include "TIM.h"
#include "Delay.h"

void HCSR04_Init(void)
{
    MyGPIO_Init(HCSR04_PORT, TRIG, GPIO_Mode_Out_PP);
    MyGPIO_Init(HCSR04_PORT, ECHO, GPIO_Mode_IPD);
    TIM_General_Init(HCSR04_TIM, 20, ENABLE, 1, 1);
}

void TriggerSigner(void)
{

}
