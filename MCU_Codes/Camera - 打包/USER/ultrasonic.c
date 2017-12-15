#include "ultrasonic.h"
#include "delay.h"


float gDistance = 0;

/*
*function:config the ultrasonic to detect the distance
*use TIM2-channel2 pin:PA1
*
*/
void Ultrasonic_Config(void)
{
    SendPin_GPIO_Config();
    TIM2_GPIO_Config();
    TIM2_Mode_Config();
}


void Ultrasonic_Send(void)
{
    int i = 0;
    GPIO_SetBits(GPIOA,GPIO_Pin_0);
    for(i=0;i<1000;i++){}
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

static void SendPin_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                                              
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
static void TIM2_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                                               //TIM2_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    
}

static void TIM2_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef        TIM2_ICInitStructure;
    
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_Period = 9999;                                                    //10msÖÐ¶ÏÒ»´Î
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
    
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);                                     //TIM2ÎªÃÅ¿ØÄ£Ê½
    TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);       //Ê¹ÄÜTIM2µÄÖ÷´ÓÄ£Ê½
    TIM_SelectInputTrigger(TIM2,TIM_TS_TI2FP2);                                             //TI2FP2Îª´¥·¢Ô´
    
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;            //
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //Ó³Éäµ½TI1ÉÏ  Ö±½ÓÓ³Éä
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;              //ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;                           //IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);                                                 //¿ªÆô¸üÐÂÖÐ¶Ï
    TIM_ClearFlag(TIM2,TIM_FLAG_Trigger);
    TIM_ITConfig(TIM2,TIM_IT_Trigger, ENABLE);                                              //¿ªÆô´¥·¢ÖÐ¶Ï
    TIM_Cmd(TIM2, ENABLE);
    
}



//the code following should be put into void  TIM2_IRQHandler(void)
/*
void  TIM2_IRQHandler(void)
{
    uint16_t  counter = 0;
    float     time = 0;
    static unsigned char temp = 0;
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        num++;
    }
    if(TIM_GetITStatus(TIM2, TIM_IT_Trigger) != RESET)
    {   
        static uint8_t temp = 0;
        if(temp == 0)                                                                       //ÃÅÐÅºÅÓÐÐ§£¬Æô¶¯¶¨Ê±Æ÷¿ªÊ¼¼ÆÊý
        {
            TIM2->CNT = 0;
            temp ++;
        }
        else if(temp == 1)                                                          //ÃÅÐÅºÅÊ§Ð§£¬¶ÁÈ¡¼ÆÊýÖµ
        {
            counter = TIM2->CNT;
            time = 10*num + counter/1000.0;
            gDistance = 17*time;                                                     //µ¥Î»£ºcm
            temp = 0;
            num = 0;
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Trigger);
    }
}
*/

//the code following should be put into the NVIC_Config()

/*
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure); 

*/
