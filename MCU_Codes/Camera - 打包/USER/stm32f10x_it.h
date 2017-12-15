/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "math.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#include "soft_spi.h"
#include "Var_Def.h"
#include "usart.h"
#include "rtc.h"
#include "TIMx.h"
#include "EEPROM.h"
#include "CRC.h"
#include "key.h"

#define FreqConv_ADDRESS       0x01    //变频器
#define WaterFlow_ADDRESS      0x02    //流量表
#define Number_Buffer          0       //站点号
#define WaterPressureValue     1       //水压
#define WaterFlowSpeedValue    2       //流速
#define Waterlevelalue         3       //水位
#define WaterFlow_Value        4       //流量（累积量）
#define FreqConv_Out_Volt      5       //变频器输出电压
#define FreqConv_Out_Imp       6       //变频器输出电流
#define FreqConv_Out_Freq      7       //变频器输出频率
#define FreqConv_Error_Ststus  8       //变频器故障状态
#define FreqConv_Out_Power     9       //变频器输出功率
#define FreqConv_Set_Freq      19      //变频器当前设置频率
#define Networkstatus          11      //GPRS网络状况
#define RF_COM                 12      //RF通信状态
#define BP_START               13      //变频器启动
#define BP_STOP                14      //变频器停止

#define FreqConv_set_Freq_N       19     //变频器当前设置频率
#define WaterPressure_SET_N       20     //当前水压设定值
#define Transducer_ControlMode_N  21     //当前工作方式
#define FreqConv_Set_Freq_t       23     //变频器自动模式设置频率-DA
#define RS485_COM                 24     //485通信状态
#define MUANUAL_Mode              25     //手动模式
#define MUANUAL_Control_onoff     26     //手动方式启动
#define MUANUAL_AC_Contactor_t    27     //手动交流接触器
#define AUTO_Mode                 28     //自动模式
#define AUTO_Control_onoff        29     //自动方式启动
#define AUTO_AC_Contactor_t       30     //自动交流接触器
#define waterlevel_s              31     //水位上限
#define waterlevel_x              32     //水位下限
#define waterlevel_warning        33     //水位报警
#define waterlevel_status         34     //是否使用水位数据进行水位报警


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
	 
void RTC_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);


void EXTI0_IRQHandler(void);  //PB0 
void EXTI1_IRQHandler(void);  //PB1
void EXTI3_IRQHandler(void);  //PA3
void EXTI9_5_IRQHandler( void);//PE7

void Waterlevel(void);  //水位物理量获取

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
