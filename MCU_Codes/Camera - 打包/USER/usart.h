#ifndef __USART_H
#define __USART_H

#include "stm32f103.h"
#include "Var_Def.h"

#include "EEPROM.h"
#include "stmflash.h"
#include "sys.h"
#include "stm32f10x_it.h"


#define USART1_APB2_CLK			RCC_APB2Periph_USART1
#define USART2_APB1_CLK     RCC_APB1Periph_USART2
#define USART3_APB1_CLK     RCC_APB1Periph_USART3
#define UART4_APB1_CLK     	RCC_APB1Periph_UART4
#define UART5_APB1_CLK     	RCC_APB1Periph_UART5




void EXTI_Config(void);

void USART1_Config	(void);
void USART2_Config	(void);
void USART3_Config	(void);
void UART4_Config		(void);
void UART5_Config		(void);


//void JKB_To_ASIC(int32_t JKB[],uint8_t ASIC[]);
//void Slope_To_ASIC(int32_t Slope,uint8_t ASIC[]);
//void Zero_To_ASIC(int32_t Zero,uint8_t ASIC[]);
//void Sys_DATE_To_ASIC(Date_TypeDef YMD,uint8_t DATE_ASIC[]);
//void Sys_TIME_To_ASIC(Time_TypeDef HMS,uint8_t TIME_ASIC[]);

//void CSV_Server(void);
//void CSP_Server(void);
//void CRV_Server(void);
//void CRP_Server(void);
//void TNS_Server(void);
//void CPA_Server(void);
//void SNS_Server(void);//����Ĵ���������
//void ADS_Server(void);//��������ַ

//void RIC_Server(void); //Remote Intelligent Control
//void PWS_Server(void);//��վ����ϵͳ���� 
//void FPS_Server(void);//���Ʊ�Ƶ������
//void FCM_Server(void);//��վ���Ʒ�ʽ 
//void WPS_Server(void);//ˮѹ����
//void FQS_Server(void);//��Ƶ��Ƶ������
//void Relay_Server(uint8_t ADR,uint8_t SEL); //���߼̵�������


//void FPS_TFT_Server(void);//��Ƶ����������----�ر�/��ˮ
//void FCM_TFT_Server(void);//��վ���Ʒ�ʽ :��Ƶ/��ѹ
//void FQS_TFT_Server(void);//��Ƶ��Ƶ��
//void WPS_TFT_Server(void);//ˮѹ����
////void Master_switch_Server(void ); //��վϵͳ����
//void TFT_tips(uint8_t Tips);//TFT��ʾ����
//void Water_Source_Level(void);  //ˮԴ��ˮλѡ��    TFT
//void WaterSource_Level_S(void );//ˮԴ��ˮλ����    TFT
//void WaterSource_Level_L(void );//ˮԴ��ˮλ����    TFT
//void WaterSourceLevel_warning(void);//ˮԴ��ˮλ����

//void  WaterSource_Level_GPRS_S(void ) ;   //ˮλ��������
//void  WaterSource_Level_GPRS_L(void ) ;   //ˮλ��������
//void Water_Source_Level_GPRS(void);       //ˮԴ��ˮλѡ���Ƿ�ʹ��ˮλ������	
//void Ter_To_GPRS(void);//�ն�GPRS���������ķ�������
//void DAU_Read(void); //�ն˲�ѯ ����������
////void Command_Show(uint8_t UART_N0);//���ڽ���������ʾ
////void UART1_command_Show(uint8_t count);//����1����������ʾ---RF
////void UART4_command_Show(uint8_t count);//����4����������ʾ---485
////void UART5_command_Show(uint8_t count);//����5����������ʾ---GPRS

//void ModbusServer(uint8_t time);//485-modbus
//void ModBus_RTU_Read(uint8_t Address, uint8_t datatype);
//void ModBus_RTU_Control(uint8_t Address,uint8_t datatype);

//void Transducer_Control(uint8_t Address,uint8_t datatype);

//void RTC_Adj_Server(uint8_t T_Pos);

void Send_UART1(uint8_t *pos,uint8_t CharLength);
void Send_UART2(uint8_t *pos,uint8_t CharLength);
void Send_UART3(uint8_t *pos,int CharLength);
void Send_UART4(uint8_t *pos,uint8_t CharLength);
void Send_UART5(uint8_t *pos,uint8_t CharLength);

void SampleDataSend_UART1(void);  //RF��������
void SampleDataSend_UART5(void);  //GPRS��������
void SampleDataSend_UART3(void);	//������
void delay(uint32_t time);

//void FreqConv_SET_Freq_send(void);//�����ã��۲��ѹ�����ʵʱ�仯��Ƶ��


#endif



