#ifndef __LCD_H
#define __LCD_H

#include "stm32f103.h"
#include "asc_font.h"
#include "sd_fs_app.h"
#include "rtc.h"
#include "Var_Def.h"
#include "AD7793.h"
#include "EEPROM.h"

#define Bank1_LCD_D    ((u32)0x60020000)
#define Bank1_LCD_C    ((u32)0x60000000)

#define LCD_RESET_H			GPIO_SetBits	(LCD_RESET_GPIO_PORT, LCD_RESET_PIN)
#define LCD_RESET_L			GPIO_ResetBits(LCD_RESET_GPIO_PORT, LCD_RESET_PIN)
#define LCD_LED_ON      GPIO_SetBits  (LCD_LED_CON_GPIO_PORT, LCD_LED_CON_PIN)
#define LCD_LED_OFF			GPIO_ResetBits(LCD_LED_CON_GPIO_PORT, LCD_LED_CON_PIN)
#define LCD_W           240
#define LCD_H						320

#define MAX_CHAR_POSX		232
#define MAX_CHAR_POSY		304
#define MAX_CH_POSX			224
#define MAX_CH_POSY			304

#define WHITE						0xFFFF
#define GRAY						0x69AD
#define BLACK						0x0000
#define RED							0xF800
#define GREEN						0x07E0
#define BLUE						0x001F
#define xx							0xFB00
#define DisplayColor		WHITE
#define BackColor			  BLACK

static void LCD_Delay				(uint32_t);

static void LCD_WR_REG			(uint16_t);
static void LCD_WR_DATA			(uint16_t);
static void LCD_WR_REG_DATA	(uint16_t, uint16_t);

			 void LCD_Init				(uint16_t);
			 
static void Set_Coordinate	(uint16_t, uint16_t, uint16_t, uint16_t);
			 
static void LCD_Rectangle		(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
			 
			 void LCD_Num					(uint16_t, uint16_t, int32_t, uint16_t, uint16_t);
			 void LCD_PointNum		(uint16_t, uint16_t, int32_t, uint16_t, uint16_t);
			 void LCD_Num_Right   (uint16_t, uint16_t, int32_t, uint16_t, uint16_t);
			 void LCD_Char				(uint16_t, uint16_t, uint8_t, uint16_t, uint16_t);
			 void LCD_Str_Char		(uint16_t, uint16_t, uint8_t *, uint16_t, uint16_t);
			 //不支持中文标点符号
			 void LCD_CH					(uint16_t, uint16_t, uint8_t *, uint16_t, uint16_t);
			 void LCD_Str_CH			(uint16_t, uint16_t, uint8_t *, uint16_t, uint16_t);
			 void LCD_Str_CHChar	(uint16_t, uint16_t, uint8_t *, uint16_t, uint16_t);
			 
			 void LCD_ShowDate    (Date_TypeDef, uint16_t, uint16_t);
			 void LCD_ShowTime		(Time_TypeDef, uint16_t, uint16_t);
static void LCD_ShowCelsius (uint16_t, uint16_t, uint16_t, uint16_t);
			 
			 void LCD_Show_BkColor        (uint16_t, uint16_t, uint16_t);
			 void LCD_Show_Start					(uint16_t, uint16_t);
			 void LCD_Show_Main_Screen		(uint16_t, uint16_t);
			 void LCD_Show_Channel_Info   (uint8_t, uint16_t, uint16_t);
			 void LCD_ChannelPara					(uint8_t, uint16_t, uint16_t);
			 void LCD_ChannelSensorCH			(uint8_t, uint16_t, uint16_t);
			 void LCD_ChannelUnit         (uint8_t, uint16_t, uint16_t, uint16_t, uint16_t);
static void Sub_LCD_Para						(uint8_t, uint8_t, uint8_t, uint16_t, uint16_t);


			 void LCD_Show_Config_Info						(uint16_t, uint16_t);
			 void LCD_Show_Detail_Channel_Info		(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_ChannelNum						(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_ChannelType					(uint8_t, uint16_t, uint16_t, uint16_t, uint16_t);
			 void LCD_Detail_Sensor								(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_VoltageCalibration		(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_ConversionRelation		(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_RT_ElectricSignal		(uint8_t, uint16_t, uint16_t);
			 void LCD_Detail_RT_PhysicalData			(uint8_t, uint16_t, uint16_t);
//显示通道号
static void LCD_ChannelNum	(uint8_t CHX, uint16_t x, uint16_t y, uint16_t Color, uint16_t BkColor);

void LCD_Update_Show(uint8_t PageNum, uint16_t Color, uint16_t BkColor);

void LCD_Show_Systemname(void);

#endif
