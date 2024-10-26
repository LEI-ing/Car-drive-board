#include "stm32f10x.h" // Device header

/**
 * @brief 自定义GPIO初始化函数
 * 
 * @param GPIOx GPIO端口
 * @param GPIO_Pin GPIO引脚
 * @param GPIO_Mode GPIO模式 value: GPIO_Mode_AIN, GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD, GPIO_Mode_IPU, GPIO_Mode_Out_OD,
 *                                  GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP
 */
void MyGPIO_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
    uint32_t  GPIO_RCC_Clk[] = {
        RCC_APB2Periph_GPIOA,
        RCC_APB2Periph_GPIOB,
        RCC_APB2Periph_GPIOC
        };
    GPIO_TypeDef *GPIO_Port[] = {GPIOA, GPIOB, GPIOC};

    uint8_t i;
    for(i = 0;i < sizeof(GPIO_Port)/sizeof(GPIO_Port[0]);i++)
    {
        if(GPIOx == GPIO_Port[i])
        {
            RCC_APB2PeriphClockCmd(GPIO_RCC_Clk[i], ENABLE);
            break;
        }
    }

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}
