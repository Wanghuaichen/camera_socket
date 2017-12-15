#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"
//#include "stm32f10x_it.h"

void Delay_10uS(__IO u32 nCount);
void SysTick_Init(void);
void TimingDelay_Decrement(void);

#endif
