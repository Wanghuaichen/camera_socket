#include "stm32f10x.h"
#include "usart.h"
#include "TIMx.h"
#include "CRC.h"
#include "delay.h"
#include "NVIC.h"
#include "string.h"




int main(void)
{	
//	TIM2_Config(); 							//服务：工作指示灯，外部看门狗
//	TIM1_Config();              //定时计数器 脉冲

//	USART1_Config();						//RF 控制平台通信
//	USART2_Config();            //GPS
//	USART3_Config();						//TFT
//	UART4_Config();							//陀螺仪
//	UART5_Config();							//GPRS/本地调试
////  EXTI_Config();              //外部中断初始化
//	ADC_Config();							  //STM32内部ADC配置	
//	 RTC_Init();  
     
     

	SystemInit();
    NVIC_Config();//中断控制器
	
	USART1_Config();//Camera
	USART3_Config();//GPRS DTU
	TIM4_Config();//100ms
	

//	TIM1_Config();
	

//	USART1_Config();
//	UART4_Config();
//	Menu_Config();
//	Encoder_Init();
//	TIM6_Config();
//	PWM_Init();
     
//	 MPU6050_Config();
//	 Motor_Config();
//	 MotorA_Init();
//	 MotorB_Init();
//     
//	PWM_SetPeriod(1000);
//	PWM_SetDuty(3,50);
     
    


    while(1)
    {
		
	}
  
}


