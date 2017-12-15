#ifndef __TLC5615_H
#define __TLC5615_H
#include "soft_spi.h"
#include "stm32f10x.h"



#define Channel_A  1					//通道A
#define Channel_B  2					//通道B
#define Channel_AB 3					//通道A&B

#define CS_L  	 GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define CS_H  	 GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define SCK_H	   GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define SCK_L    GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define DIN_H    GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define DIN_L    GPIO_ResetBits(GPIOB,GPIO_Pin_14)


typedef struct
{
	uint16_t Data;
}TLC5615_InitTypeDef;


#define IS_TLC5615_Code(Data)						(Data<0x80)

void TLC5615_Init(uint16_t tmpdata);

void DAC5615(double out);


void TLV5618_GPIO_Init(void);



void Write_Data(uint16_t DigNum);

void DAC_Convert(uint16_t Data_A,uint16_t Data_B,uint8_t Channel,uint8_t Mode);

void ShipDACInit(void);

void ShipDACOutput(float v);

#endif
