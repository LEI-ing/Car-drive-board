#ifndef HCSR05_H
#define HCSR05_H

#define HCSR04_PORT GPIOB
#define TRIG GPIO_Pin_0
#define ECHO GPIO_Pin_1
#define HCSR04_TIM TIM3

void HCSR04_Init(void);
float GetDistance(void);
void TriggerSigner(void);


#endif
