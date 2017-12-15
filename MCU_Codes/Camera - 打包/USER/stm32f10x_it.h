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

#define FreqConv_ADDRESS       0x01    //��Ƶ��
#define WaterFlow_ADDRESS      0x02    //������
#define Number_Buffer          0       //վ���
#define WaterPressureValue     1       //ˮѹ
#define WaterFlowSpeedValue    2       //����
#define Waterlevelalue         3       //ˮλ
#define WaterFlow_Value        4       //�������ۻ�����
#define FreqConv_Out_Volt      5       //��Ƶ�������ѹ
#define FreqConv_Out_Imp       6       //��Ƶ���������
#define FreqConv_Out_Freq      7       //��Ƶ�����Ƶ��
#define FreqConv_Error_Ststus  8       //��Ƶ������״̬
#define FreqConv_Out_Power     9       //��Ƶ���������
#define FreqConv_Set_Freq      19      //��Ƶ����ǰ����Ƶ��
#define Networkstatus          11      //GPRS����״��
#define RF_COM                 12      //RFͨ��״̬
#define BP_START               13      //��Ƶ������
#define BP_STOP                14      //��Ƶ��ֹͣ

#define FreqConv_set_Freq_N       19     //��Ƶ����ǰ����Ƶ��
#define WaterPressure_SET_N       20     //��ǰˮѹ�趨ֵ
#define Transducer_ControlMode_N  21     //��ǰ������ʽ
#define FreqConv_Set_Freq_t       23     //��Ƶ���Զ�ģʽ����Ƶ��-DA
#define RS485_COM                 24     //485ͨ��״̬
#define MUANUAL_Mode              25     //�ֶ�ģʽ
#define MUANUAL_Control_onoff     26     //�ֶ���ʽ����
#define MUANUAL_AC_Contactor_t    27     //�ֶ������Ӵ���
#define AUTO_Mode                 28     //�Զ�ģʽ
#define AUTO_Control_onoff        29     //�Զ���ʽ����
#define AUTO_AC_Contactor_t       30     //�Զ������Ӵ���
#define waterlevel_s              31     //ˮλ����
#define waterlevel_x              32     //ˮλ����
#define waterlevel_warning        33     //ˮλ����
#define waterlevel_status         34     //�Ƿ�ʹ��ˮλ���ݽ���ˮλ����


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

void Waterlevel(void);  //ˮλ��������ȡ

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
