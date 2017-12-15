/*-------------------------------------------------------------------------------------------
        		   			�����ڿ���ϵͳ(2015-8-12)

 Ӳ��ƽ̨:
 			������: STM32F103VET6 64K RAM 512K ROM
			������: LMD18200T 
		    ��Դ:   DC +12V

 ���ƽ̨:
 			��������: RealView MDK-ARM uVision4.10
			C������ : ARMCC
			ASM������:ARMASM
			������:   ARMLINK
			�ײ�����: ����������������       
 
 ʱ��: 2015��8��12��       
 
 ����: BoX
-------------------------------------------------------------------------------------------*/
#ifndef __MOTOR__PWM__H__
#define __MOTOR__PWM__H__	

#include "stm32f10x.h"


typedef struct motorstatus
{
	int PWM;
	
	float Kp;
	float Ki;
	float Kd;
	
	float SetAngle;
	float CurAngle;
	
	float ErrLast;
	float ErrSum;
	
}MotorStatus;

void Motor_Config(void); 


void MotorA_Move(void);
void MotorAMove(int Dir,uint16_t val);

void MotorBMove(int Dir,uint16_t val);


static void PWM_GPIO_Config(void);

static void PWM_Mode_Config(void);

static void MOTOR_DIR_GPIO_Config(void);



void M1M2_SetDir(int d);

void M3M4_SetDir(int d);

void M1M2_SetPWM(uint16_t val);

void M3M4_SetPWM(uint16_t val);

 void M1_SetForward(void);

 void M1_SetBackward(void);

 void M2_SetForward(void);

 void M2_SetBackward(void);


 void M3_SetForward(void);

 void M3_SetBackward(void);


 void M4_SetForward(void);

 void M4_SetBackward(void);


#endif


