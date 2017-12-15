#ifndef MOTOR_H
#define MOTOR_H
#include "stm32f10x.h"
typedef struct 
{
    float PWM;

    float Kp;
    float Ki;
    float Kd;
    
    float SetAngle;
    float CurAngle;
    
    float ErrLast;
    float ErrSum;
		
		float LineLen;
}MotorStatus;




void Motor_Config(void); 
static void PWM_GPIO_Config(void);
static void PWM_Mode_Config(void);
static void MOTOR_DIR_GPIO_Config(void);

void MotorA_Init(void);
void MotorA_Calc(void);
void MotorA_Move(void);

void MotorB_Init(void);
void MotorB_Calc(void);
void MotorB_Move(void);

/*
static void M1M2_SetDir(int d);
static void M3M4_SetDir(int d);
static void M1M2_SetPWM(uint16_t val);
static void M3M4_SetPWM(uint16_t val);


*/

static void M1_SetForward(void);
static void M1_SetBackward(void);
static void M2_SetForward(void);
static void M2_SetBackward(void);
static void M3_SetForward(void);
static void M3_SetBackward(void);
static void M4_SetForward(void);
static void M4_SetBackward(void);

void Mode_0(void);
void Mode_1(void);
void Mode_2(void);
void Mode_3(void);
void Mode_4(void);
void Mode_5(void);
void Mode_6(void);

#endif // MOTOR_H
