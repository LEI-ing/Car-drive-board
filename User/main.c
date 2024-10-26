#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "TIM.h"

uint8_t runtime_min = 0, runtime_s = 0;
uint16_t runtime_ms = 0;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    OLED_Init();
    TIM_General_Init(TIM2, 1, ENABLE, 2, 2);
    OLED_ShowString(1, 1, "HELLO WORLD!!!");
    OLED_ShowString(2, 1, "Time:  :  :");
    OLED_ShowString(3, 1, "ID:2204451216");
    OLED_ShowString(4, 1, "Disigner:LEI");

    while (1) 
	{
        OLED_ShowNum(2, 7, runtime_min, 1);
        OLED_ShowNum(2, 9, runtime_s, 2);
        OLED_ShowNum(2, 12, runtime_ms, 3);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        if (runtime_ms < 1000) 
		{
            runtime_ms++;
        } else 
		{
            runtime_ms = 0;
            runtime_s++;
            if (runtime_s >= 60) 
			{
                runtime_s = 0;
                runtime_min++;
            }
        }
    }
}