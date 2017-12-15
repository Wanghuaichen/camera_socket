/*-------------------------------------------------------------------------------------------
        		   			风力摆控制系统(2015-8-12)

 硬件平台:
 			主控器: STM32F103VET6 64K RAM 512K ROM
			驱动器: LMD18200T 
		    电源:   DC +12V

 软件平台:
 			开发环境: RealView MDK-ARM uVision4.10
			C编译器 : ARMCC
			ASM编译器:ARMASM
			连接器:   ARMLINK
			底层驱动: 各个外设驱动程序       
 
 时间: 2015年8月12日       
 
 作者: BoX
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


