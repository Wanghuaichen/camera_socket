#include "encoder.h"

#define ENCODER_TIMER                TIM3  // Encoder unit connected to TIM3
#define ENCODER_PPR           (u16)(600)   // number of pulses per revolution

#define COUNTER_RESET   (u16)0
#define ICx_FILTER      (u8) 6 


int gEncoderDir = 0;
int gEncoderPos = 0;

void Encoder_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    /* Encoder unit connected to TIM3, 4X mode */   
    GPIO_InitTypeDef GPIO_InitStructure;
     

    /* TIM3 clock source enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* Enable GPIOA, clock */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
     
    GPIO_StructInit(&GPIO_InitStructure);
    /* Configure PA.06,07 as encoder input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

    
    /* Timer configuration in Encoder mode */
    TIM_DeInit(ENCODER_TIMER);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
    TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
    TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(ENCODER_TIMER, TIM_EncoderMode_TI12, 
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6; 
    TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);


    TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
    TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE);
       
    ENCODER_TIMER->CNT = COUNTER_RESET;
       
    TIM_Cmd(ENCODER_TIMER, ENABLE);  
}

void Encoder_GetInfo(void)
{
    gEncoderDir = (ENCODER_TIMER->CR1 & 0x0010)?1:0;
    gEncoderPos = TIM_GetCounter(ENCODER_TIMER);
}
//the code following should be put into NVIC_Config()
// NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3
// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
// NVIC_Init(&NVIC_InitStructure); 


//the code following should be put into TIM3_IRQHandler(),per circle
// void TIM3_IRQHandler(void)   //TIM3中断
// {
//     if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
        // {
        // TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

        // }
// }

