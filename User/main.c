#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "TIM.h"
#include "HCSR05.h"
#include "key.h"

#define PAGE_MAX 2

uint8_t runtime_min = 0, runtime_s = 0;
uint16_t runtime_ms = 0;
uint8_t page = 1;
static uint8_t temp = 1;
float distance = 0;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    OLED_Init();
    Key_Init();
    HCSR04_Init();
    TIM_General_Init(TIM2, 1, ENABLE, 2, 2);
        
    while (1) 
	{
        switch (page)
        {
        case 1: 
            if(temp == 1)
            {
                OLED_Clear();
                OLED_ShowString(1, 1, "Distance:");
                temp = 2;
            }
            TriggerSigner();
            distance = GetDistance();
			OLED_ShowNum(1, 10, distance, 2); 
			break;
        case 2: 
            if(temp == 2)
            {
                OLED_Clear();
                OLED_ShowString(1, 1, "HELLO WORLD!!!");
                OLED_ShowString(2, 1, "Time:  :  :");
                OLED_ShowString(3, 1, "ID:2204451216");
                OLED_ShowString(4, 1, "Disigner:LEI");
                temp = 1;
            }
            OLED_ShowNum(2, 7, runtime_min, 1);
            OLED_ShowNum(2, 9, runtime_s, 2);
            OLED_ShowNum(2, 12, runtime_ms, 3);
            break;
        }
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
        if(GPIO_ReadInputDataBit(KEY_PORT, KEY2) == RESET)
        {
            if(page > 1)
                page--;
        }else if (GPIO_ReadInputDataBit(KEY_PORT, KEY1) == RESET)
        {
            if(page < PAGE_MAX)
                page++;
        }
        
    }
}
