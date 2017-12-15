#include "pwm.h"


static float gDuty = 50;
static int gPeriod = 1000; //us

int gSinglePulseMode3 = 0;
int gSinglePulseCnt3 =0;
int gSinglePulseMode4 = 0;
int gSinglePulseCnt4 =0;

void PWM_Init(void)
{
    TIM5_GPIO_Config();
    TIM5_Config();
}

void PWM_SetOrdinary(int channel)
{
    switch(channel)
    {
        case 3:
            gSinglePulseMode3 = 0;
            break;
        case 4:
            gSinglePulseMode4 = 0;
            break;
    }
}

void PWM_SetPeriod(int x) // us
{
    gPeriod = x;
    TIM_SetAutoreload(TIM5,gPeriod);
    PWM_SetDuty(3,gDuty);
    PWM_SetDuty(4,gDuty);
}

void PWM_SetDuty(int channel,int x)
{
    if(x >= 100) gDuty = 100;
    else if(x <= 0) gDuty = 0;
    else gDuty = x;
    switch(channel)
    {
        case 1:
            TIM_SetCompare1(TIM5,(gDuty/100)*gPeriod-1);
            break;
        case 2:
            TIM_SetCompare2(TIM5,(gDuty/100)*gPeriod-1);
            break;
        case 3:
            TIM_SetCompare3(TIM5,(gDuty/100)*gPeriod-1);
            break;
        case 4:
            TIM_SetCompare4(TIM5,(gDuty/100)*gPeriod-1);
            break;
        default:
            break;
    }
}



void PWM_SinglePulse(int channel,int x)
{
    switch(channel)
    {
        case 3:
            gSinglePulseMode3 = 1;
            gSinglePulseCnt3 = x + 1;
            break;
        case 4:
            gSinglePulseMode4 = 1;
            gSinglePulseCnt4 = x+1;
            break;
    }
    
    
}


static void TIM5_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;                                               //TIM5_CH3,CH4
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3);
}

static void TIM5_Config(void)
{
    
    TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    TIM_DeInit(TIM5);

    TIM_TimeBaseStructure.TIM_Period = gPeriod-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); // Time base configuration

    TIM_ClearFlag(TIM5, TIM_FLAG_Update);                                       
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
    TIM_ARRPreloadConfig(TIM5,ENABLE);
    TIM_SetCounter(TIM5, 0);
    
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;       
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = (gDuty/100)*gPeriod-1;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
//  
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);     //enable ch3,ch4
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_Cmd(TIM5, ENABLE);   /* ¿ªÆôÊ±ÖÓ */
}


// the following code should be put into NVIC_Config();
//        NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                             
//        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              
//        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//        NVIC_Init(&NVIC_InitStructure);
