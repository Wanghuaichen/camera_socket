#include "motor.h"
#include "math.h"
#include "debug.h"
#include "usart.h"
#include "string.h"
#include "DataScope_DP.h"

int gMode = 0;
float gAngle = 0;

MotorStatus MotorA = {0};
MotorStatus MotorB = {0};
extern float gRoll;
extern float gPitch;
extern float gSpeedX;
extern float gSpeedY;

extern unsigned char DataScope_OutPut_Buffer[42];

void Mode_1(void)
{		
	char strDebug[100] = {0};
	static int count_usart4 = 0;
	static int count_usart1 = 0;
	const float priod = 1600;
	static uint32_t MoveTimeCnt = 0;
	float SetX = 0.0;
	float A = 0.0;
	float Normalization = 0.0;
	float Omega = 0.0;
	MoveTimeCnt += 10;
	Normalization = (float)MoveTimeCnt /priod;
	Omega = 2*3.14159 * Normalization;
	A = atan((MotorA.LineLen/88.0))*57.2958f;//
	SetX = A * sin(Omega);


	MotorA.SetAngle = SetX;
	MotorA.CurAngle = gRoll;


	MotorA_Calc();

	MotorA_Move();


	//debug
	/*
	if(count_usart4++ >=20)
	{
	count_usart4 = 0;
	sprintf(strDebug,"A:Amp:%.3f;SetA:%.3f;CurAngle:%.3f;Err:%.3f\r\n",A,MotorA.SetAngle,MotorA.CurAngle,MotorA.SetAngle-MotorA.CurAngle);
	Send_UART4((uint8_t*)strDebug,strlen(strDebug));
	}
	*/

	//debug
	if(count_usart1++ >= 10)
	{
	count_usart1 = 0;
	DataScope_Get_Channel_Data(MotorA.SetAngle,1);
	DataScope_Get_Channel_Data(MotorA.CurAngle,2);
	DataScope_Get_Channel_Data(MotorA.PWM,3);
	DataScope_Data_Generate(3);
	Send_UART1((uint8_t*)DataScope_OutPut_Buffer,strlen((char*)DataScope_OutPut_Buffer));
	}




	MotorB.CurAngle = gPitch;
	MotorB.SetAngle = 0;
	MotorB_Calc();
	MotorB_Move();

	//		if(gSpeedY >= 0 && MotorB.CurAngle >=0)
	//			MotorB.PWM = 0;
	//		else if(gSpeedY <= 0 && MotorB.CurAngle >=0)
	//			MotorB.PWM = -MotorB.PWM;
	//		else if (gSpeedY >= 0 && MotorB.CurAngle <=0)
	//			MotorB.PWM = -MotorB.PWM;
	//		else if(gSpeedY <= 0 && MotorB.CurAngle <=0)
	//			MotorB.PWM = 0;



    
}




void Mode_2(void)
{
	char strDebug[100] = {0};
	static int count_usart1 = 0;
	static int count_usart4 = 0;
	const float priod = 1600;
	float SetX = 0.0;
	float A = 0.0;
	static uint32_t MoveTimeCnt = 0;
	float angle = gAngle / 180 * 3.14;
	
	float Normalization = 0.0;
	float Omega = 0.0;

	MoveTimeCnt += 10;
	Normalization = (float)MoveTimeCnt /priod;
	Omega = 2*3.14159 * Normalization;
	A = atan((MotorA.LineLen/88.0))*57.2958f;//
	SetX = A * sin(Omega);

	
	
	MotorA.CurAngle = gRoll;
	MotorA.SetAngle = SetX * sin(angle);
	MotorA_Calc();
	MotorA_Move();
	
	
	MotorB.CurAngle = gPitch;
	MotorB.SetAngle = SetX * cos(angle);
	MotorB_Calc();
	MotorB_Move();

}


void Mode_3(void)
{
	char strDebug[100] = {0};
	static int count_usart1 = 0;
	static int count_usart4 = 0;
	const float priod = 1600;
	float SetX = 0.0;
	float SetY = 0.0;
	float A = 0.0;
	static uint32_t MoveTimeCnt = 0;
	float angle = 3.14/4;
	
	float Normalization = 0.0;
	float Omega = 0.0;

	MoveTimeCnt += 10;
	Normalization = (float)MoveTimeCnt /priod;
	Omega = 2*3.14159 * Normalization;
	A = atan((MotorA.LineLen/88.0))*57.2958f;//
	SetX = A * sin(Omega);
	SetY = A * cos(Omega);
	
	
	MotorA.CurAngle = gRoll;
	MotorA.SetAngle = SetX;
	MotorA_Calc();
	MotorA_Move();
	
	
	MotorB.CurAngle = gPitch;
	MotorB.SetAngle = SetY;
	MotorB_Calc();
	MotorB_Move();
}


void Mode_4(void)
{
	char strDebug[100] = {0};
	static int count_usart1 = 0;
	static int count_usart4 = 0;
	const float priod = 1600;
	float SetX = 0.0;
	float SetY = 0.0;
	float A = 0.0;
	static uint32_t MoveTimeCnt = 0;
	float angle = 3.14/4;
	static float R = 0;
	static int flag = 0;
	float Normalization = 0.0;
	float Omega = 0.0;

	MoveTimeCnt += 10;
	Normalization = (float)MoveTimeCnt /priod;
	Omega = 2*3.14159 * Normalization;
	
	
	if(flag == 0)
	{
		R -= MotorA.LineLen/1000;
		if(R <= 0)
		{
			flag = 1;
		}
	}
	else if(flag == 1)
	{
		R += MotorA.LineLen/1000;
		if(R >= MotorA.LineLen)
		{
			flag = 0;
		}
	}
	
	
	
	A = atan((R/88.0))*57.2958f;//
	SetX = A * sin(Omega);
	SetY = A * cos(Omega);
	
	
	MotorA.CurAngle = gRoll;
	MotorA.SetAngle = SetX;
	MotorA_Calc();
	MotorA_Move();
	
	
	MotorB.CurAngle = gPitch;
	MotorB.SetAngle = SetY;
	MotorB_Calc();
	MotorB_Move();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MotorA_Init()
{
    MotorA.CurAngle = 0;
    MotorA.SetAngle = 0;
    MotorA.Kp = MotorA.Ki = MotorA.Kp = 0;
    MotorA.ErrSum = 0;
    MotorA.ErrLast = 0;
    MotorA.PWM = 0;
		MotorA.LineLen = 0;
	
	  M1_SetForward();
    M2_SetBackward();
}
void MotorB_Init()
{
    MotorB.CurAngle = 0;
    MotorB.SetAngle = 0;
    MotorB.Kp = MotorA.Ki = MotorA.Kp = 0;
    MotorB.ErrSum = 0;
    MotorB.ErrLast = 0;
    MotorB.PWM = 0;
		MotorB.LineLen = 0;
	  M3_SetForward();
    M4_SetBackward();
}

void MotorA_Calc()
{
    float Err = MotorA.SetAngle - MotorA.CurAngle;
    static int x = 0;
	

	//SendDebug(50);  
	//SendDebug2(50,20);
    MotorA.ErrSum += Err;
    //
    if(MotorA.ErrSum >= 75) MotorA.ErrSum = 75;
    
    MotorA.PWM = MotorA.Kp * Err + MotorA.Ki * MotorA.ErrSum + MotorA.Kd * ( Err - MotorA.ErrLast);
		if(MotorA.ErrSum >= 300) MotorA.ErrSum = 300;
		if(MotorA.ErrSum <= -300) MotorA.ErrSum = -300;
    if(MotorA.PWM >= 75) MotorA.PWM = 75;
    if(MotorA.PWM <= -75) MotorA.PWM = -75;
    
    MotorA.ErrLast = Err;
    
}

void MotorB_Calc()
{
    float Err = MotorB.SetAngle - MotorB.CurAngle;
    
    MotorB.ErrSum += Err;
    //
    if(MotorB.ErrSum >= 75) MotorB.ErrSum = 75;
    
    MotorB.PWM = MotorB.Kp * Err + MotorB.Ki * MotorB.ErrSum + MotorB.Kd * ( Err - MotorB.ErrLast);
    if(MotorB.PWM >= 100) MotorB.PWM = 100;
    if(MotorB.PWM <= -100) MotorB.PWM = -100;
    
    MotorB.ErrLast = Err;
    
}


void MotorA_Move()
{
	if(MotorA.PWM >= 0)
	{
		uint16_t temp = (uint16_t)(MotorA.PWM);
		TIM_SetCompare1(TIM3,temp);
		TIM_SetCompare2(TIM3,0);
	}
	else if(MotorA.PWM <=0)
	{
		uint16_t temp = (uint16_t)(-MotorA.PWM);
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,temp);
	}
}

void MotorB_Move()
{
    if(MotorB.PWM >= 0)
    {
        uint16_t temp = (uint16_t)(MotorB.PWM);
        TIM_SetCompare3(TIM3,temp);
        TIM_SetCompare4(TIM3,0);
    }
    else if(MotorB.PWM <=0)
    {
				uint16_t temp = (uint16_t)(-MotorB.PWM);
        TIM_SetCompare3(TIM3,0);
        TIM_SetCompare4(TIM3,temp);
    }
}




void Motor_Config(void) 
{
    PWM_GPIO_Config();
    PWM_Mode_Config();
    MOTOR_DIR_GPIO_Config();         
}

static void PWM_GPIO_Config(void)     
{
     GPIO_InitTypeDef GPIO_InitStructure;         
     
     
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    
    
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 ;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*------------------------------------------
 º¯Êý¹¦ÄÜ:ÅäÖÃTIM2Êä³öµÄPWMÐÅºÅµÄÄ£Ê½
 º¯ÊýËµÃ÷:- TIM2Í¨µÀ4Êä³öPWM
          - PWMÄ£Ê½1
          - ¼«ÐÔµÍµçÆ½
          - PWMÆµÂÊ = 24kHz             
------------------------------------------*/
static void PWM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period=(100-1);                                       /* ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ(¼ÆÊýÖµ) */
    /* ÀÛ¼Æ TIM_Period¸öÆµÂÊºó²úÉúÒ»¸ö¸üÐÂ»òÕßÖÐ¶Ï */
    TIM_TimeBaseStructure.TIM_Prescaler= (7200-1);                  /* Ê±ÖÓÔ¤·ÖÆµÊý 72M/7200 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;       /* ²ÉÑù·ÖÆµ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ÏòÉÏ¼ÆÊýÄ£Ê½ */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;         
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;     
    TIM_OC1Init(TIM3,&TIM_OCInitStructure);
    
    TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;         
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;     
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);                     
    
    TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;           
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;     
    TIM_OC3Init(TIM3,&TIM_OCInitStructure); 
    
    TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;           
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;     
    TIM_OC4Init(TIM3,&TIM_OCInitStructure);                  
    
    TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIM3ÔÚCCR3ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable); //Ê¹ÄÜTIM3ÔÚCCR4ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

    TIM_SetCompare1(TIM3,0);
    TIM_SetCompare2(TIM3,0);
    TIM_SetCompare3(TIM3,0);
    TIM_SetCompare4(TIM3,0);

    TIM_Cmd(TIM3,ENABLE);   //Ê¹ÄÜTIM3
}




static void MOTOR_DIR_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // ÍÆÍìÊä³ö    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
}


 void M1_SetForward(void)
{
    GPIOE->BSRR = GPIO_Pin_9; 
    GPIOE->BRR  = GPIO_Pin_10;
}
 void M1_SetBackward(void)
{
    GPIOE->BSRR = GPIO_Pin_10; 
    GPIOE->BRR  = GPIO_Pin_9;
}

 void M2_SetForward(void)//7 8
{
   GPIOE->BSRR = GPIO_Pin_7; 
     GPIOE->BRR  = GPIO_Pin_8;
}

void M2_SetBackward(void)//
{
    GPIOE->BSRR = GPIO_Pin_8; 
  GPIOE->BRR  = GPIO_Pin_7;
}

 void M3_SetForward(void)//
{
    
    GPIOE->BSRR = GPIO_Pin_11; 
    GPIOE->BRR  = GPIO_Pin_12;
    
}
 void M3_SetBackward(void)
{
    GPIOE->BSRR = GPIO_Pin_12; 
    GPIOE->BRR  = GPIO_Pin_11;
}

 void M4_SetForward(void)
{
    GPIOE->BSRR = GPIO_Pin_13; 
    GPIOE->BRR  = GPIO_Pin_14;
}
 void M4_SetBackward(void)
{
    GPIOE->BSRR = GPIO_Pin_14; 
    GPIOE->BRR  = GPIO_Pin_13;
}
