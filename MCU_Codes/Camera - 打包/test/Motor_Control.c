
#include "motor_control.h"
#include "motor_pwm.h"
#include "motor_pid.h"
#include "stdlib.h"
#include "stdio.h"
#include "delay.h"
#include "math.h"
#include "mpu6050.h"
#include "ahrs.h"
#include "usart.h"
#include "string.h"
#include "debug.h"
/*------------------------------------------
 				ȫ�ֱ���				
------------------------------------------*/



extern float gRoll;							//��ת��
extern float gPitch;           	//������

extern uint8_t gKeyNum;

extern MotorStatus MotorA;
extern MotorStatus MotorB;



void Mode_0(void)
{
	/*
	float Err = 0;
	static float ErrLast = 0;
	static float ErrNext = 0;
	float DeltaU = 0;
	static int count = 0;
	char str[50] ={0};
  static float U = 0;
	

//debug 
	count++;
	if(count >= 10)
	{
		uint16_t x = 0;
		x = gKeyNum << 8;
		x+= gKeyNum;
		//SendDebugInt(x);
		SendDebug(gKeyNum);
	}

	
	
	MotorA.CurAngle = gRoll;
	
	Err = MotorA.SetAngle - MotorA.CurAngle;
	
	DeltaU = MotorA.Kp*(Err-ErrLast);
	if(fabs(Err) <= 3)
		DeltaU += MotorA.Ki*(Err);
	DeltaU += MotorA.Kd*(Err+ErrNext-2*ErrLast);
	
	U += DeltaU;


	//MotorAMove(MotorA.Dir,MotorA.PWM);
	
	ErrNext = ErrLast;
	ErrLast = Err;
		*/
}
/*------------------------------------------
 ��������:��1��PID����
 ����˵��:
------------------------------------------*/
void MotorA_Init()
{
	MotorA.CurAngle = 0;
	MotorA.SetAngle = 0;
	MotorA.Kp = MotorA.Ki = MotorA.Kp = 0;
	MotorA.ErrSum = 0;
	MotorA.ErrLast = 0;
	MotorA.PWM = 0;
}
void MotorB_Init()
{
	MotorB.CurAngle = 0;
	MotorB.SetAngle = 0;
	MotorB.Kp = MotorA.Ki = MotorA.Kp = 0;
	MotorB.ErrSum = 0;
	MotorB.ErrLast = 0;
	MotorB.PWM = 0;
}

void MotorA_Calc()
{
	float Err = MotorA.SetAngle - MotorA.CurAngle;
	
	MotorA.ErrSum += Err;
	//
	if(MotorA.ErrSum >= 75) MotorA.ErrSum = 75;
	
	MotorA.PWM = MotorA.Kp * Err + MotorA.Ki * MotorA.ErrSum + MotorA.Kd * ( Err - MotorA.ErrLast);
	if(MotorA.PWM >= 100) MotorA.PWM = 100;
	if(MotorA.PWM <= -100) MotorA.PWM = -100;
	
	MotorA.ErrLast = Err;
	
}





void Mode_1(void)
{
	//�����˶����
	const float priod = 1410;
	static uint32_t MoveTimeCnt = 0;
	float SetX = 0.0;
	float A = 0.0;
	float Normalization = 0.0;
	float Omega = 0.0;
	MoveTimeCnt += 5;
	Normalization = (float)MoveTimeCnt /priod;
	Omega = 2*3.14159 * Normalization;
	A = atan((15/88.0))*57.2958f;//
	SetX = A * sin(Omega);
	MotorA.SetAngle = SetX;
	
	MotorA_Calc();
	MotorA_Move();
	
}
/*------------------------------------------
 ��������:��2��PID����
 ����˵��:
------------------------------------------*/
void Mode_2(void)
{
	
}
/*------------------------------------------
 ��������:��3��PID����
 ����˵��:
------------------------------------------*/ 
void Mode_3(void)
{
	
}
/*------------------------------------------
 ��������:��4��PID����
 ����˵��:
------------------------------------------*/ 
void Mode_4(void)
{	
	
}
/*------------------------------------------
 ��������:��5��PID����
 ����˵��:
------------------------------------------*/
void Mode_5(void)
{
	
	
}
/*------------------------------------------
 ��������:��6��PID����
 ����˵��:
------------------------------------------*/
void Mode_6(void)
{

}
/*------------------------------------------
 ��������:����ײ���������
 ����˵��:
------------------------------------------*/
void MotorMove(int32_t pwm1,int32_t pwm2)
{

}


