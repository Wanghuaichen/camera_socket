#include "rtc.h"

extern __IO Date_TypeDef  System_Date;
extern __IO Time_TypeDef  System_Time;

static uint8_t const mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

static uint32_t 			SecCount 	= 0;

void RTC_Init(void)
{
 	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RTC_Config();	//将系统初始化的时间写入RTC
		DateGetRTC_Sec(System_Date);
		Adjust_RTCCounter();
		TimeGetRTC_Sec(System_Time);
		Adjust_RTCCounter();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
  else
 	{
 		/* Enable PWR and BKP clocks */
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		RTC_WaitForLastTask();
 	}
}
//RTC配置
void RTC_Config(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	/* Reset Backup Domain */
	BKP_DeInit();
// 	//使用外部高速晶振 128分频
 	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
	//使用外部32768晶振
// 	RCC_LSEConfig(RCC_LSE_ON);
// 	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
// 	{}
//  	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Set RTC prescaler: set RTC period to 1sec */
	/* RTC period = RTCCLK/RTC_PR = (8000000Hz)/128/(62499+1) */
	RTC_SetPrescaler(62499);
// 		RTC_SetPrescaler(32767);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}


//调整RTC计数值
void Adjust_RTCCounter()
{
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_SetCounter(SecCount);
	RTC_WaitForLastTask();
}
//判断日期参数是否合法
static Time_Return IS_DateParameter(Date_TypeDef YTD)
{
	if((YTD.Year<2000)||(YTD.Year>2099))		//2000-2099
		return Year_Illegal;
	if((YTD.Month<1)||(YTD.Month>12))		//1-12
		return Month_Illegal;
	if(YTD.Month != 2)					//非2月份
	{
		if((YTD.Date<1)||(YTD.Date>mon_table[YTD.Month-1]))
			return Date_Illegal;
	}
	else							//2月份
	{
		if(IS_LeapYear(YTD.Year)==Leap_Year)	//闰年
		{
			if((YTD.Date<1)||(YTD.Date>29))//1-29
				return Date_Illegal;
		}
		else						//非闰年
		{
			if((YTD.Date<1)||YTD.Date>28)	//1-28
				return Date_Illegal;
		}
	}
	
	return Time_Legal;
}
//判断时间参数是否合法
static Time_Return IS_TimeParameter(Time_TypeDef Time)
{
	if(Time.Hour>23)					//0-23
		return Hour_Illegal;
	if(Time.Minute>59)					//0-59
		return Minute_Illegal;
	if(Time.Second>59)					//0-59
		return Second_Illegal;
	
	return Time_Legal;
}

//判断是否为闰年
static Time_Return IS_LeapYear(uint16_t year)
{
	if(year%4==0) 					//必须能被4整除
	{
		if(year%100==0)
		{
			if(year%400==0)
				return Leap_Year;	//如果以00结尾,还要能被400整除          
			else return Nonleap_Year;
		}
		else return Leap_Year;
  	}
	else return Nonleap_Year;
}

//由日期类得到32位RTC计数器值
Time_Return DateGetRTC_Sec(Date_TypeDef YTD)
{
	uint16_t t = 0;
	Time_Return Time_Error;
	
	SecCount = RTC_GetCounter();
	//一天86400S，直接计算出当天已经走了多少秒，以保持时间值不变
	SecCount = SecCount%86400;	//时间值不变
	
	Time_Error = IS_DateParameter(YTD);
	if(Time_Error != Time_Legal)
		return Time_Error;
	for(t=2000; t<YTD.Year; t++)
	{
		if(IS_LeapYear(t) == Leap_Year)
			SecCount += 31622400;
		else	SecCount += 31536000;
	}
	for(t=1; t<YTD.Month; t++)
	{
		SecCount += 86400*mon_table[t-1];
		if((t == 2)&&(IS_LeapYear(YTD.Year) == Leap_Year))
			SecCount += 86400;
	}
	for(t=1 ;t<YTD.Date; t++)
		SecCount += 86400;
	
	return Time_Legal;
}
//由时间类得到32位RTC计数器值
Time_Return TimeGetRTC_Sec(Time_TypeDef Time)
{
	uint16_t t = 0;
	
	SecCount = RTC_GetCounter();
	//一天86400S，先计算出多少个整天数，然后换算成秒数，以保持日期值不变
	SecCount = SecCount/86400;	//日期值不变
	SecCount = SecCount*86400;	//换算成秒数
	if(IS_TimeParameter(Time) != Time_Legal)
		return Time_Illegal;
	
	for(t=0; t<Time.Hour; t++)
		SecCount += 3600;
	for(t=0; t<Time.Minute; t++)
		SecCount += 60;
	SecCount += Time.Second;
	
	return Time_Legal;
}

//得到RTC的日期
Date_TypeDef GetRTC_Date()
{
	uint32_t tmp = 0;
	Date_TypeDef YTD;
	YTD.Year = 2000;
	YTD.Month = 1;
	YTD.Date = 1;
	tmp = RTC_GetCounter();
	
	tmp = tmp/86400;
	
	while(tmp >= 365)
	{
		if(IS_LeapYear(YTD.Year) == Leap_Year)
		{
			if(tmp >= 366)
			{
				tmp -= 366;
				YTD.Year++;
			}
			else
			{
				break;//tmp -= 365;
			}
		}
		else
		{
			tmp -= 365;
			YTD.Year++;
		}
	}
	while(tmp >= 28)
	{
		if((YTD.Month == 2)&&(IS_LeapYear(YTD.Year) == Leap_Year))
		{
			if(tmp >= 29)
			{
				tmp -= 29;
				YTD.Month++;
			}
			else
			{
				break;//tmp -= 28;
			}
		}
		else
		{
			if(tmp >= mon_table[YTD.Month-1])
			{
				tmp -= mon_table[YTD.Month-1];
				YTD.Month++;
			}
			else
			{
				break;
			}
		}
	}
	YTD.Date += tmp;
	
	YTD.DProperty = IS_DateParameter(YTD);

	return YTD;
}
//得到RTC的时间
Time_TypeDef GetRTC_Time()
{
	uint32_t timecount = 0;
	Time_TypeDef Time;
	timecount = RTC_GetCounter();

	timecount		= timecount%86400;
	Time.Hour 	= timecount/3600;
	timecount		= timecount%3600;
	Time.Minute = timecount/60;
	Time.Second = timecount%60;

	Time.TProperty = IS_TimeParameter(Time);
	
	return Time;
}

