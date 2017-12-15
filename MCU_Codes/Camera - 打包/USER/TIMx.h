#ifndef __TIMX_H
#define __TIMX_H


#include "stm32f10x.h"
#include "stm32f103.h"
void PWM_Send(int x);
void TIM4_Config(void);
void TIM2_Config(void);
void LED_Hurry(void);
void LED_Slow(void);
void TIM1_Config(void);
void TIM1_GPIO_Config(void); 


void TIM6_Config(void);

#define WorkStatusLED_ON		GPIO_ResetBits(WS_OUTPUT_GPIO_PORT, WS_OUTPUT_PIN)
#define WorkStatusLED_OFF		GPIO_SetBits(WS_OUTPUT_GPIO_PORT, WS_OUTPUT_PIN)

#define COMM_LED_ON			GPIO_SetBits(COMM_OUTPUT_GPIO_PORT, 	COMM_OUTPUT_PIN)
#define COMM_LED_OFF		GPIO_ResetBits(COMM_OUTPUT_GPIO_PORT, 	COMM_OUTPUT_PIN)

#define AUTO_LED_ON		   GPIO_SetBits(WS_OUTPUT1_GPIO_PORT, WS_OUTPUT1_PIN)
#define AUTO_LED_OFF		 GPIO_ResetBits(WS_OUTPUT1_GPIO_PORT, WS_OUTPUT1_PIN)

// void TIM3_Config(void);

#endif
