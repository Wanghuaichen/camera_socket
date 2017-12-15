#include "stm32f10x.h"
#include "usart.h"
#include "TIMx.h"
#include "CRC.h"
#include "delay.h"
#include "NVIC.h"
#include "string.h"




int main(void)
{	
//	TIM2_Config(); 							//���񣺹���ָʾ�ƣ��ⲿ���Ź�
//	TIM1_Config();              //��ʱ������ ����

//	USART1_Config();						//RF ����ƽ̨ͨ��
//	USART2_Config();            //GPS
//	USART3_Config();						//TFT
//	UART4_Config();							//������
//	UART5_Config();							//GPRS/���ص���
////  EXTI_Config();              //�ⲿ�жϳ�ʼ��
//	ADC_Config();							  //STM32�ڲ�ADC����	
//	 RTC_Init();  
     
     

	SystemInit();
    NVIC_Config();//�жϿ�����
	
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


