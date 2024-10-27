#include "stm32f10x.h" // Device header

/**
 * @brief 自定义EXTI初始化函数，需要自己配置对应的GPIO初始化（ 使用MyGPIO_Init() ）
 *
 * @param GPIO_PortSource 使用EXTI的GPIO端口
 * @param GPIO_PinSource 使用EXTI的GPIO引脚
 * @param EXTI_Trigger EXTI的触发方式
 * @param PreemptionPriority 抢占优先级
 * @param SubPriority 从占优先级
 */
void MyEXTI_Init(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource, EXTITrigger_TypeDef EXTI_Trigger, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);

    const uint32_t EXTI_Lines[] = {
        EXTI_Line0,
        EXTI_Line1,
        EXTI_Line2,
        EXTI_Line3,
        EXTI_Line4,
        EXTI_Line5,
        EXTI_Line6,
        EXTI_Line7,
        EXTI_Line8,
        EXTI_Line9,
        EXTI_Line10,
        EXTI_Line11,
        EXTI_Line12,
        EXTI_Line13,
        EXTI_Line14,
        EXTI_Line15};
    const uint8_t GPIO_PinSources[] = {
        GPIO_PinSource1,
        GPIO_PinSource2,
        GPIO_PinSource3,
        GPIO_PinSource4,
        GPIO_PinSource5,
        GPIO_PinSource6,
        GPIO_PinSource7,
        GPIO_PinSource8,
        GPIO_PinSource9,
        GPIO_PinSource10,
        GPIO_PinSource11,
        GPIO_PinSource12,
        GPIO_PinSource13,
        GPIO_PinSource14,
        GPIO_PinSource15};
    const uint8_t NVIC_IRQChannals[] = {
        EXTI0_IRQn,
        EXTI1_IRQn,
        EXTI2_IRQn,
        EXTI3_IRQn,
        EXTI4_IRQn,
        EXTI9_5_IRQn,
        EXTI15_10_IRQn};
    uint8_t i = 0;
    for (i = 0; i < sizeof(GPIO_PinSources) / sizeof(GPIO_PinSources[0]); i++) {
        if (GPIO_PinSource == GPIO_PinSources[i]) {
            break;
        }
    }
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line    = EXTI_Lines[i];
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger;
    EXTI_Init(&EXTI_InitStruct);

    if (i > 4 && i < 9) {
        i = 5;
    } else if (i > 9) {
        i = 6;
    }

    NVIC_InitTypeDef NVIC_InitTypeDefStruct;
    NVIC_InitTypeDefStruct.NVIC_IRQChannel                   = NVIC_IRQChannals[i];
    NVIC_InitTypeDefStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitTypeDefStruct.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitTypeDefStruct.NVIC_IRQChannelSubPriority        = SubPriority;
    NVIC_Init(&NVIC_InitTypeDefStruct);
}
