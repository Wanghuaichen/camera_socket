#include "TIMx.h"

//extern __IO  uint8_t 			WorkStatusLEDSpeed;

int gPWMCount = 0;

void TIM1_Config(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                                               //TIM5_CH3
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
    


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_DeInit(TIM1);
    TIM_TimeBaseStructure.TIM_Period = 1000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // Time base configuration
    //TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    
    
    
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
    

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500-1;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
    
    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;//???????????
//    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//?????????????
// 	
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);	 
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    
    TIM_Cmd(TIM1, ENABLE);   /* ����ʱ�� */
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

void PWM_Send(int x)
{
    gPWMCount = x;
    TIM_Cmd(TIM1,ENABLE);
    //TIM_CtrlPWMOutputs(TIM1,ENABLE);
    
}

void TIM2_Config(void)
{
    
    
	//ms��ʱ�ж�
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=(100-1);		 					    /* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200-1);				    /* ʱ��Ԥ��Ƶ�� 72M/7200 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* ����ʱ�� */
	
    
    
//	WorkStatusLEDSpeed =1;
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
  
  
}


// void TIM3_Config(void)
// {
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	TIM_OCInitTypeDef  TIM_OCInitStructure;

// 	u16 CCR_Val = 5;//PWM�źŵ�ƽ����ֵ

// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
// 	
//   TIM_DeInit(TIM3);
//   TIM_TimeBaseStructure.TIM_Period=(10-1);		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
//   /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
//   TIM_TimeBaseStructure.TIM_Prescaler= (7200-1);				    /* ʱ��Ԥ��Ƶ�� 72M/7200 */
// //	TIM_TimeBaseStructure.TIM_Period=999;
// //	TIM_TimeBaseStructure.TIM_Prescaler= 0;
//   TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
//   TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
//   TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
// 	
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
// 	//PWM Mode configuration: Channel 3
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
// 	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
// 	
//   TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��3

//   TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
// 	
//   TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR
//   TIM_Cmd(TIM3, ENABLE);																		/* ����ʱ�� */
// }


void TIM4_Config(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_DeInit(TIM4);

    TIM_TimeBaseStructure.TIM_Period = 10000-1;//100ms per IT
    TIM_TimeBaseStructure.TIM_Prescaler = 720-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); // Time base configuration
    TIM_ARRPreloadConfig(TIM4,ENABLE);
    
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    
    
    
    TIM_Cmd(TIM4, ENABLE);   /* ����ʱ�� */
}



void TIM6_Config(void) //1ms
{
    TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    TIM_DeInit(TIM6);
    TIM_TimeBaseStructure.TIM_Period = 1000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); // Time base configuration
  
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);							    		
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    TIM_ARRPreloadConfig(TIM6,DISABLE);
    TIM_Cmd(TIM6, ENABLE);   
}
