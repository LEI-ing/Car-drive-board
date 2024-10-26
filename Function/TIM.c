#include "stm32f10x.h"                  // Device header

/**
 * @brief 通用定时器初始化，stm32f103c8t6只有TIM2~4三个通用定时器
 * 
 * @param TIM 要初始化的定时器
 * @param time_ms 计数溢出时间（ms）
 * @param IT_State 中断状态
 * @param PreemptionPriority 抢占优先级
 * @param SubPriority 从占优先级
 */
void TIM_General_Init(TIM_TypeDef *TIM, uint8_t time_ms, FunctionalState IT_State, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    uint32_t TIM_RCC_Clk[] = {
        RCC_APB1Periph_TIM2,
        RCC_APB1Periph_TIM3,
        RCC_APB1Periph_TIM4,
        RCC_APB1Periph_TIM5,
        RCC_APB1Periph_TIM6,
        RCC_APB1Periph_TIM7
    };
    uint8_t NVIC_IRQChannel[] = {
        TIM2_IRQn,
        TIM3_IRQn,
        TIM4_IRQn
    };
    TIM_TypeDef *TIMs[] = {TIM2, TIM3, TIM4, TIM5, TIM6, TIM7};

    uint8_t i;
    for(i = 0;i < sizeof(TIMs)/sizeof(TIMs[0]);i++)
    {
        if(TIM == TIMs[i])
        {
            RCC_APB1PeriphClockCmd(TIM_RCC_Clk[i], ENABLE);
            break;
        }
    }

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = time_ms * 1000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM, &TIM_TimeBaseInitStruct);

    TIM_Cmd(TIM, ENABLE);
    TIM_ITConfig(TIM, TIM_IT_Update, IT_State);

    if(IT_State == ENABLE)
    {
        NVIC_InitTypeDef NVIC_InitTypeDefStruct;
        NVIC_InitTypeDefStruct.NVIC_IRQChannel = NVIC_IRQChannel[i];
        NVIC_InitTypeDefStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitTypeDefStruct.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
        NVIC_InitTypeDefStruct.NVIC_IRQChannelSubPriority = SubPriority;

        NVIC_Init(&NVIC_InitTypeDefStruct);
    }
}
