/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  西南交大萃思团队X6403实验室
  * @version V1.0
  * @date    2016-11
  * @brief   SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
//SysTick_Config主要用来配置中端向量，重置STK_VAL寄存器，配置SysTick时钟为AHB 
#include "bsp_SysTick.h"
static __IO u32 TimingDelay; 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock/1000))	// 1ms中断一次,ST3.5.0库版本SystemCoreClock/10不能超过16777216
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
/**
  * @brief  ms延时程序
  * @param  无
	* @arg nTime: delay_ms(10) 则实现的延时为 1ms * 10 = 10ms
  * @retval 无
  */
void delay_ms(__IO u32 nTime)
{
	TimingDelay = nTime;	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;               // 使能滴答定时器  
	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
