
#include "usart.h"
#include "CRC.h"
#include "TLC5615.h"
#include "Var_Def.h"

//extern __IO uint8_t 	  Serial_Numb;
//extern __IO uint8_t 	   NO_Buffer[];	           //NO:�ն˺�
//extern __IO	uint8_t			 CH_Sensor_Sel[16];      //����������
//extern __IO uint8_t 	   Sensor_amount	;        //���ն��µĲɼ�������
//extern __IO uint8_t 	   Sensor_ADR[40];	       //�ɼ�����ַ����ţ�
//extern __IO uint8_t 	   Sensor_Sel[40];         //����������
//extern __IO uint8_t      ReadSensorCount;        //��������ѯ���
//extern __IO	int16_t      LCD_Refresh_count;      //TFT����ˢ�¼���
// 
//extern __IO	int32_t      WaterLevel ;            //ˮλ
//extern __IO	int32_t      WaterLevel_ZD;          //�ն�ˮλģ��ͨ����ȡˮλ
//extern __IO	int32_t      WaterFlowSpeed ;        //Сʱ������****.*m3/H
//extern __IO	int32_t      WaterPressure  ;        //�ܵ�ѹ����******.*Kpa
//extern __IO	int32_t      WaterPressure_SET ;     //�ܵ�ѹ������ֵ��******.*Kpa   �洢��ַ0X0520
//extern __IO	int32_t      WaterSourceLevel_S;     //ˮԴ��ˮλ����   ***.***
//extern __IO	int32_t      WaterSourceLevel_X;     //ˮԴ��ˮλ����   ***.***
//extern __IO	int8_t       water_Prohibition ;     // 0��ˮλ���� 1����������ˮλ���Զ�ģʽ�½�ֹ��ˮ
//extern __IO	int32_t      WaterSource_Level;      //ˮԴ��ˮλѡ��  1ʹ��ˮλ��������0��ˮλ������

//extern __IO	int8_t       MUANUAL_AC_Contactor ;  //�ֶ������Ӵ���״̬ 0���� 1����
//extern __IO	int8_t       AUTO_AC_Contactor ;     //�Զ������Ӵ���״̬ 0���� 1����
//extern __IO	int8_t       Transducer_ControlMode ;//��Ƶ�����Ʒ�ʽ 0����ѹ��ˮ 1����Ƶ����
//extern __IO	int8_t       ControlMode ;           //��վ���Ʒ�ʽ 0��ֹͣ 1���Զ� 2���ֶ�
//extern __IO	int8_t       AUTO_Control_ON_OFF;    //��վ�Զ����� 0 ֹͣ 1 ����
//extern __IO	int8_t       MUANUAL_Control_ON_OFF; //��վ�ֶ����� 0 ֹͣ 1 ����
//extern __IO  uint16_t 	 RTC_1S_Count;           //ϵͳ��ͣ������ʱ
//extern __IO	int8_t       FreqConv_SET_OnOff ;    //���Ʊ�Ƶ������  0���� 1��   
//extern __IO	int16_t      FreqConv_SET_Freq ;     //���Ʊ�Ƶ��Ƶ��**.*Hz  �洢��ַ������
//extern __IO	int16_t      FreqConv_Freq  ;        //��Ƶ����ǰ��Ƶ�� **.*Hz
//extern __IO	int16_t      FreqConv_Volt ;         //��Ƶ����ǰ�������ѹֵ***.*V
//extern __IO	int16_t      FreqConv_Imp  ;         //��Ƶ����ǰ���������ֵ***.*A
//extern __IO	int16_t      FreqConv_Pow  ;         //��Ƶ����ǰ��������� ***.*
//extern __IO	int16_t      FreqConv_Volt_In ;      //��Ƶ����ǰ�������ѹ***.*V
//extern __IO	int16_t      FreqConv_Err  ;         //��Ƶ������״̬
//extern __IO	int16_t      FreqConv_SET_Freq_t ;   //���Ʊ�Ƶ���Զ�ģʽƵ��
//extern __IO	int32_t			 CH_Sample[16];
//extern __IO	int32_t			 CH_Phy_Value[16];
//extern __IO	int16_t      FreqConv_SET_Freq_t ;   //���Ʊ�Ƶ���Զ�ģʽƵ��
//extern __IO  int8_t       LcdReFlag; 
//extern __IO	 Time_TypeDef	System_Time	;			     //ϵͳʱ��
//extern __IO  uint8_t 			WorkStatusLEDSpeed;		 //ͨ��״̬�Ƶ��ٶȱ�־ 1Ϊ�죬0Ϊ��
//extern __IO	uint8_t       RS485_COM_Status  ;    //=1��485ͨ��������=0��485ͨ�Ź���
//extern __IO	uint8_t       RF_COM_Status    ;     //=1��RFͨ��������=0��RFͨ�Ź���
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

//extern __IO int32_t				CH0_Sample; 			  //ͨ��0 ��ص�ѹ����ֵ
//extern __IO	int32_t				CH1_Sample;		    	//ͨ��1  ˮѹ 
//extern __IO	int32_t				CH2_Sample;			    //ͨ��2  ����
//extern __IO	int32_t				CH3_Sample;				  //ͨ��3    ����ˮλ 
//extern __IO	int32_t				CH4_Sample;			    //ͨ��4  back  up 1

//extern __IO int32_t		    CH0_Phy_Value;			//ͨ��0 ��ص�ѹֵ

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
//     �ⲿ�ж�  PA3  PB0 PB1 PE7
//****************************************************
void EXTI_Config(void)
{
	 
	EXTI_InitTypeDef EXTI_InitStructure;   //����жϱ�־
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	EXTI_ClearITPendingBit(EXTI_Line12);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12); 
	EXTI_InitStructure.EXTI_Line = EXTI_Line12; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       //����Ϊ�½����жϣ����¼�����
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //�½����ж�	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                 //�ⲿ�ж�ʹ��
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
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		//ʹ�ܴ���1�����ж�
}


/*****************************************************************************
                       UART_2	   ���ص���
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
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		//ʹ�ܴ���2�����ж�
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
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);		//ʹ�ܴ���3�����ж�
	
	
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
	//USART_SendData(UART4, 0xFF);//�����
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

