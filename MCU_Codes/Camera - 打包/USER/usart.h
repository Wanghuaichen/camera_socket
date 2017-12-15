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
//void SNS_Server(void);//管理的传感器数量
//void ADS_Server(void);//传感器地址

//void RIC_Server(void); //Remote Intelligent Control
//void PWS_Server(void);//泵站供电系统开关 
//void FPS_Server(void);//控制变频器开关
//void FCM_Server(void);//泵站控制方式 
//void WPS_Server(void);//水压设置
//void FQS_Server(void);//变频器频率设置
//void Relay_Server(uint8_t ADR,uint8_t SEL); //无线继电器控制


//void FPS_TFT_Server(void);//变频器开关设置----关闭/提水
//void FCM_TFT_Server(void);//泵站控制方式 :点频/恒压
//void FQS_TFT_Server(void);//变频器频率
//void WPS_TFT_Server(void);//水压设置
////void Master_switch_Server(void ); //泵站系统开关
//void TFT_tips(uint8_t Tips);//TFT提示界面
//void Water_Source_Level(void);  //水源地水位选择    TFT
//void WaterSource_Level_S(void );//水源地水位上限    TFT
//void WaterSource_Level_L(void );//水源地水位下限    TFT
//void WaterSourceLevel_warning(void);//水源地水位报警

//void  WaterSource_Level_GPRS_S(void ) ;   //水位上限设置
//void  WaterSource_Level_GPRS_L(void ) ;   //水位下限设置
//void Water_Source_Level_GPRS(void);       //水源地水位选择是否使用水位传感器	
//void Ter_To_GPRS(void);//终端GPRS给数据中心发送数据
//void DAU_Read(void); //终端查询 传感器数据
////void Command_Show(uint8_t UART_N0);//串口接收命令显示
////void UART1_command_Show(uint8_t count);//串口1接收命令显示---RF
////void UART4_command_Show(uint8_t count);//串口4接收命令显示---485
////void UART5_command_Show(uint8_t count);//串口5接收命令显示---GPRS

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

void SampleDataSend_UART1(void);  //RF发送数据
void SampleDataSend_UART5(void);  //GPRS发送数据
void SampleDataSend_UART3(void);	//测试用
void delay(uint32_t time);

//void FreqConv_SET_Freq_send(void);//测试用，观测恒压情况下实时变化的频率


#endif



