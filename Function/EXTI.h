#ifndef EXTI_H_
#define EXTI_H_

void MyEXTI_Init(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource, EXTITrigger_TypeDef EXTI_Trigger, uint8_t PreemptionPriority, uint8_t SubPriority);


#endif