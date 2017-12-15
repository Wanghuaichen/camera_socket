#ifndef __RTC_H
#define __RTC_H

#include "stm32f10x.h"
#include "stm32f103.h"

typedef struct{
	uint16_t Year;
	uint8_t Month;
	uint8_t Date;
	uint8_t DProperty;
}Date_TypeDef;

typedef struct{
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
	uint8_t TProperty;
}Time_TypeDef;

typedef enum{
	Time_Legal = 0,
	Time_Illegal,
	Year_Illegal,
	Month_Illegal,
	Date_Illegal,
	Hour_Illegal,
	Minute_Illegal,
	Second_Illegal,
	Leap_Year,
	Nonleap_Year
}Time_Return;


void RTC_Init(void);
//RTC����
void RTC_Config(void);

//����RTC����ֵ
void Adjust_RTCCounter(void);

//�ж����ڲ����Ƿ�Ϸ�
static Time_Return IS_DateParameter(Date_TypeDef YTD);
//�ж�ʱ������Ƿ�Ϸ�
static Time_Return IS_TimeParameter(Time_TypeDef Time);

//�ж��Ƿ�Ϊ����
static Time_Return IS_LeapYear(uint16_t);

//��������õ�32λRTC������ֵ
Time_Return DateGetRTC_Sec(Date_TypeDef);
//��ʱ����õ�32λRTC������ֵ
Time_Return TimeGetRTC_Sec(Time_TypeDef);

//�õ�RTC������
Date_TypeDef GetRTC_Date(void);
//�õ�RTC��ʱ��
Time_TypeDef GetRTC_Time(void);

//end

#endif
