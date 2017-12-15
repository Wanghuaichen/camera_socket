
#include "usart.h"
#include "CRC.h"
#include "TLC5615.h"
#include "Var_Def.h"

//extern __IO uint8_t 	  Serial_Numb;
//extern __IO uint8_t 	   NO_Buffer[];	           //NO:终端号
//extern __IO	uint8_t			 CH_Sensor_Sel[16];      //传感器类型
//extern __IO uint8_t 	   Sensor_amount	;        //该终端下的采集器数量
//extern __IO uint8_t 	   Sensor_ADR[40];	       //采集器地址（编号）
//extern __IO uint8_t 	   Sensor_Sel[40];         //传感器类型
//extern __IO uint8_t      ReadSensorCount;        //传感器查询序号
//extern __IO	int16_t      LCD_Refresh_count;      //TFT数据刷新计数
// 
//extern __IO	int32_t      WaterLevel ;            //水位
//extern __IO	int32_t      WaterLevel_ZD;          //终端水位模拟通道获取水位
//extern __IO	int32_t      WaterFlowSpeed ;        //小时流量，****.*m3/H
//extern __IO	int32_t      WaterPressure  ;        //管道压力，******.*Kpa
//extern __IO	int32_t      WaterPressure_SET ;     //管道压力设置值，******.*Kpa   存储地址0X0520
//extern __IO	int32_t      WaterSourceLevel_S;     //水源地水位上限   ***.***
//extern __IO	int32_t      WaterSourceLevel_X;     //水源地水位下限   ***.***
//extern __IO	int8_t       water_Prohibition ;     // 0：水位正常 1：低于下限水位，自动模式下禁止提水
//extern __IO	int32_t      WaterSource_Level;      //水源地水位选择  1使用水位传感器，0无水位传感器

//extern __IO	int8_t       MUANUAL_AC_Contactor ;  //手动交流接触器状态 0：关 1：开
//extern __IO	int8_t       AUTO_AC_Contactor ;     //自动交流接触器状态 0：关 1：开
//extern __IO	int8_t       Transducer_ControlMode ;//变频器控制方式 0：恒压泵水 1：点频控制
//extern __IO	int8_t       ControlMode ;           //泵站控制方式 0：停止 1：自动 2：手动
//extern __IO	int8_t       AUTO_Control_ON_OFF;    //泵站自动控制 0 停止 1 启动
//extern __IO	int8_t       MUANUAL_Control_ON_OFF; //泵站手动控制 0 停止 1 启动
//extern __IO  uint16_t 	 RTC_1S_Count;           //系统启停后的秒计时
//extern __IO	int8_t       FreqConv_SET_OnOff ;    //控制变频器开关  0：关 1开   
//extern __IO	int16_t      FreqConv_SET_Freq ;     //控制变频器频率**.*Hz  存储地址？？？
//extern __IO	int16_t      FreqConv_Freq  ;        //变频器当前的频率 **.*Hz
//extern __IO	int16_t      FreqConv_Volt ;         //变频器当前的输出电压值***.*V
//extern __IO	int16_t      FreqConv_Imp  ;         //变频器当前的输出电流值***.*A
//extern __IO	int16_t      FreqConv_Pow  ;         //变频器当前的输出功率 ***.*
//extern __IO	int16_t      FreqConv_Volt_In ;      //变频器当前的输入电压***.*V
//extern __IO	int16_t      FreqConv_Err  ;         //变频器故障状态
//extern __IO	int16_t      FreqConv_SET_Freq_t ;   //控制变频器自动模式频率
//extern __IO	int32_t			 CH_Sample[16];
//extern __IO	int32_t			 CH_Phy_Value[16];
//extern __IO	int16_t      FreqConv_SET_Freq_t ;   //控制变频器自动模式频率
//extern __IO  int8_t       LcdReFlag; 
//extern __IO	 Time_TypeDef	System_Time	;			     //系统时间
//extern __IO  uint8_t 			WorkStatusLEDSpeed;		 //通信状态灯的速度标志 1为快，0为慢
//extern __IO	uint8_t       RS485_COM_Status  ;    //=1，485通信正常，=0，485通信故障
//extern __IO	uint8_t       RF_COM_Status    ;     //=1，RF通信正常，=0，RF通信故障
//extern __IO uint8_t       UART1_Rece_ByteNum;
//extern __IO	uint8_t 			UART1_Receive[45];
//extern __IO uint8_t       UART2_Rece_ByteNum;
//extern __IO	uint8_t 			UART2_Receive[45];
//extern __IO uint8_t       UART3_Rece_ByteNum;
//extern __IO	uint8_t 			UART3_Receive[45];
//extern __IO uint8_t       UART4_Rece_ByteNum;
//extern __IO	uint8_t 			UART4_Receive[45];
//extern __IO uint8_t 	    UART5_Rece_ByteNum;
//extern __IO	uint8_t 			UART5_Receive[80];

//extern __IO int32_t				CH0_Sample; 			  //通道0 电池电压采样值
//extern __IO	int32_t				CH1_Sample;		    	//通道1  水压 
//extern __IO	int32_t				CH2_Sample;			    //通道2  流量
//extern __IO	int32_t				CH3_Sample;				  //通道3    地下水位 
//extern __IO	int32_t				CH4_Sample;			    //通道4  back  up 1

//extern __IO int32_t		    CH0_Phy_Value;			//通道0 电池电压值

//extern __IO int32_t       Para_J[16];
//extern __IO int32_t       Para_K[16];
//extern __IO int32_t       Para_B[16];

//extern __IO int32_t       CH_Volt_slope[16];
//extern __IO	int32_t		    CH_Volt_zero[16];

//extern __IO uint16_t     CH_Type[16];
//extern __IO int16_t      CH_Gain[16];

//extern __IO uint16_t    EEPROM_SPI_Half_Cycle;
//extern __IO int16_t     Local_Battery_Volt;

//extern __IO	Date_TypeDef	System_Date;

//extern __IO uint16_t    NO_POSX;
//extern __IO uint16_t    NO_POSY;

//*****************************************************
//
//     外部中断  PA3  PB0 PB1 PE7
//****************************************************
void EXTI_Config(void)
{
	 
	EXTI_InitTypeDef EXTI_InitStructure;   //清空中断标志
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	EXTI_ClearITPendingBit(EXTI_Line12);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12); 
	EXTI_InitStructure.EXTI_Line = EXTI_Line12; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       //设置为下降沿中断，非事件请求
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿中断	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                 //外部中断使能
  EXTI_Init(&EXTI_InitStructure); 
	
}

/*****************************************************************************
                       UART_1  RF
******************************************************************************/

void USART1_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART1_GPIO_Config();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//USART1 9600 8 1 No None
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		//使能串口1接收中断
}


/*****************************************************************************
                       UART_2	   本地调试
******************************************************************************/

void USART2_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART2_GPIO_Config();

	RCC_APB1PeriphClockCmd(USART2_APB1_CLK, ENABLE);
	
	//USART2 9600 8 1 No None
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		//使能串口2接收中断
}


/*****************************************************************************
                               UART_3	TFT
******************************************************************************/

void USART3_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//FullRemap
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//open fullremap
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);  
	
	//USART3 
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART3,&USART_InitStructure);
	USART_Cmd(USART3,ENABLE);	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);		//使能串口3接收中断
	
	
}


/*****************************************************************************
                               UART_4	 485
******************************************************************************/

void UART4_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	UART4_GPIO_Config();
	
	RCC_APB1PeriphClockCmd(UART4_APB1_CLK, ENABLE);
	
	//USART4 9600 8 1 No None
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART4,&USART_InitStructure);	
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	USART_Cmd(UART4,ENABLE);
	//USART_SendData(UART4, 0xFF);//激活串口
}

//void RTC_Adj_Server(uint8_t T_Pos)
//{
//	uint8_t T_Position = 0;
//	T_Position = T_Pos;
//	T_Position += 5;
//	System_Date.Year   = (2000+(UART4_Receive[T_Position]-'0')*10+((UART4_Receive[T_Position+1])-'0'));
//	T_Position += 3;
//	System_Date.Month  = (UART4_Receive[T_Position]-'0')*10 + ((UART4_Receive[T_Position+1])-'0');
//	T_Position += 3;
//	System_Date.Date   = (UART4_Receive[T_Position]-'0')*10 + ((UART4_Receive[T_Position+1])-'0');
//	T_Position += 3;
//	System_Time.Hour   = (UART4_Receive[T_Position]-'0')*10 + ((UART4_Receive[T_Position+1])-'0');
//	T_Position += 3;
//	System_Time.Minute = (UART4_Receive[T_Position]-'0')*10 + ((UART4_Receive[T_Position+1])-'0');
//	T_Position += 3;
//	System_Time.Second = (UART4_Receive[T_Position]-'0')*10 + ((UART4_Receive[T_Position+1])-'0');
//	if(DateGetRTC_Sec(System_Date) == Time_Legal)
//	{
//		Adjust_RTCCounter();
//		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
//		System_Date = GetRTC_Date();
//	}
//	if(System_Date.DProperty == Time_Legal)
//	{
//		Update_Filename();
//		LCD_ShowDate(System_Date, DisplayColor, BackColor);
//	}
//	if(TimeGetRTC_Sec(System_Time) == Time_Legal)
//	{
//		Adjust_RTCCounter();
//		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
//		System_Time = GetRTC_Time();
//	}
//}

/*****************************************************************************
                               UART_5	 GPRS
******************************************************************************/
void UART5_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	UART5_GPIO_Config();
	
	RCC_APB1PeriphClockCmd(UART5_APB1_CLK, ENABLE);
	
	//USART5 9600 8 1 No None
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART5,&USART_InitStructure);
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

	USART_Cmd(UART5,ENABLE);
}



void Send_UART1(uint8_t *pos,uint8_t CharLength)
{
	uint8_t temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART1, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART1, USART_FLAG_TC) == RESET );		 				
	}       
}

void Send_UART2(uint8_t *pos,uint8_t CharLength)
{
	uint8_t temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART2, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART2, USART_FLAG_TC) == RESET );		 				
	}       
}





void Send_UART3(uint8_t *pos,int CharLength)
{
	
	int temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART3, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART3, USART_FLAG_TC) == RESET );		 				
	}       
	
}

void Send_UART4(uint8_t *pos,uint8_t CharLength)
{
	uint8_t temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART4, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );		 				
	}       
}

void Send_UART5(uint8_t *pos,uint8_t CharLength)
{
	unsigned char temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART5, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );		 				
	}       
}

