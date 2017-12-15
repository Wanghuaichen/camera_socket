#ifndef	__SOFT_SPI_H
#define	__SOFT_SPI_H
/*
#include "stm32f103.h"
#include "cpld.h"
#include "Var_Def.h"

#define MOSI_H	 GPIO_SetBits		(SOFT_SPI_MOSI_GPIO_PORT, SOFT_SPI_MOSI_PIN)
#define MOSI_L	 GPIO_ResetBits (SOFT_SPI_MOSI_GPIO_PORT, SOFT_SPI_MOSI_PIN)
#define SCK_H		 GPIO_SetBits		(SOFT_SPI_SCK_GPIO_PORT, 	SOFT_SPI_SCK_PIN)
#define SCK_L		 GPIO_ResetBits (SOFT_SPI_SCK_GPIO_PORT, 	SOFT_SPI_SCK_PIN)
#define MISO_H	 GPIO_SetBits		(SOFT_SPI_MISO_GPIO_PORT, SOFT_SPI_MISO_PIN)
#define MISO_L	 GPIO_ResetBits (SOFT_SPI_MISO_GPIO_PORT, SOFT_SPI_MISO_PIN)

#define AD7793_CS_H  GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define AD7793_CS_L  GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define AD7793_CS1_H  GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define AD7793_CS1_L  GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define TLC5615_CS_H  GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define TLC5615_CS_L  GPIO_ResetBits(GPIOB, GPIO_Pin_12)

static void 		Soft_SPI_delay (uint32_t);
			 void 		Soft_SPI_Init	 (void);

void Soft_SPI_Transfer(uint16_t Send_Data);


// int8_t 	Soft_SPI_Write (uint8_t *Data, uint8_t bytesNumber);
// int8_t 	Soft_SPI_Read	 (uint8_t *Data, uint8_t bytesNumber);
			 
void SPI_Send(uint8_t 	Data);
void SPI_Rece(uint8_t *Data);
			 
//        int32_t   	Soft_SPI_Comm		(uint8_t, uint8_t, int16_t);
// 			 void 			Trans_temperature_PARA(int32_t);
*/
#endif
