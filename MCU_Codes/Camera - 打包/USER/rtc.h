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
//RTC配置
void RTC_Config(void);

//调整RTC计数值
void Adjust_RTCCounter(void);

//判断日期参数是否合法
static Time_Return IS_DateParameter(Date_TypeDef YTD);
//判断时间参数是否合法
static Time_Return IS_TimeParameter(Time_TypeDef Time);

//判断是否为闰年
static Time_Return IS_LeapYear(uint16_t);

//由日期类得到32位RTC计数器值
Time_Return DateGetRTC_Sec(Date_TypeDef);
//由时间类得到32位RTC计数器值
Time_Return TimeGetRTC_Sec(Time_TypeDef);

//得到RTC的日期
Date_TypeDef GetRTC_Date(void);
//得到RTC的时间
Time_TypeDef GetRTC_Time(void);

//end

#endif
