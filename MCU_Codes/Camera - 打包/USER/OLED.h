#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define OLED_CMD  0			//写命令
#define OLED_DATA 1			//写数据

#ifdef	I2C1_OWN_ADDRESS7
I2C1_OWN_ADDRESS7 = 0x0A;
#endif

#ifdef  OLED_Address
OLED_Address = 0x78;
#endif

//OLED控制用函数
//void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
//void Delay_50ms(unsigned int Del_50ms);
//void Delay_1ms(unsigned int Del_1ms);
void Fill_picture(uint8_t fill_Data);
//void Picture();
void OLED_Init(void);
void Write_OLED_Command(uint8_t Command);							//给OLED写命令字
void Write_OLED_Data(uint8_t Data);										//给OLED写数据字
void Write_OLED_Byte(uint8_t Data,uint8_t Cmd);				//写一个字节到OLED；Cmd=1，写数据   Cmd=0，写命令
void OLED_Set_Position(uint8_t x,uint8_t y);					//坐标设置
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p,uint8_t Char_Size);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);


#endif

