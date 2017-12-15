#include "systick.h"

uint32_t TimingDelay = 0x0000;

void Delay_10uS(__IO u32 nCount)
{
	TimingDelay = nCount;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay != 0);
}
void SysTick_Init(void)
{
// 	SystemCoreClock/1000     1mS中断
// 	SystemCoreClock/100000   10uS中断
// 	SystemCoreClock/1000000  1uS中断
	if(SysTick_Config(SystemCoreClock/100000))
	{
		while(1);
	}
	//关闭滴答定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void TimingDelay_Decrement(void)
{	
	if(TimingDelay != 0)
	{
		TimingDelay--;
	}
}

