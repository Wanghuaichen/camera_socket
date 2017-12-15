#ifndef _PWM_H_
#define _PWM_H_
#include "stm32f103.h"


void PWM_Init(void);
void PWM_SetPeriod(int x); // ms
void PWM_SetDuty(int channel,int x);
void PWM_SinglePulse(int channel,int x);
void PWM_SetOrdinary(int channel);
void TIM5_GPIO_Config(void);
void TIM5_Config(void);


#endif
