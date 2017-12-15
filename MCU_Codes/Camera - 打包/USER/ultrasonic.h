#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include "stm32f103.h"
void Ultrasonic_Config(void);
void Ultrasonic_Send(void);
static void SendPin_GPIO_Config(void);
static void TIM2_GPIO_Config(void);
static void TIM2_Mode_Config(void);
#endif
