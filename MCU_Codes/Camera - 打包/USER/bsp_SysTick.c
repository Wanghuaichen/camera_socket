/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  ���Ͻ�����˼�Ŷ�X6403ʵ����
  * @version V1.0
  * @date    2016-11
  * @brief   SysTick ϵͳ�δ�ʱ��10us�жϺ�����,�ж�ʱ����������ã�
  *          ���õ��� 1us 10us 1ms �жϡ�     
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
//SysTick_Config��Ҫ���������ж�����������STK_VAL�Ĵ���������SysTickʱ��ΪAHB 
#include "bsp_SysTick.h"
static __IO u32 TimingDelay; 
/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  ��
  * @retval ��
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock/1000))	// 1ms�ж�һ��,ST3.5.0��汾SystemCoreClock/10���ܳ���16777216
	{ 
		/* Capture error */ 
		while (1);
	}
		// �رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
/**
  * @brief  ms��ʱ����
  * @param  ��
	* @arg nTime: delay_ms(10) ��ʵ�ֵ���ʱΪ 1ms * 10 = 10ms
  * @retval ��
  */
void delay_ms(__IO u32 nTime)
{
	TimingDelay = nTime;	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;               // ʹ�ܵδ�ʱ��  
	while(TimingDelay != 0);
}

/**
  * @brief  ��ȡ���ĳ���
  * @param  ��
  * @retval ��
  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
