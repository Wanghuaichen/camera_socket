#include "soft_spi.h"
/*
extern __IO 	uint8_t  MSPChannel[16];
extern __IO   uint8_t      MSP_CS[16];

uint16_t Half_cycle = 400;

static void Soft_SPI_delay(uint32_t time)
{
	while(time)
		--time;
}
void Soft_SPI_Init()
{
	SOFT_SPI_GPIO_Config();
//	CPLD_Init();
}


void SPI_Rece(uint8_t *Data)
{ //SCK空闲状态为高电平
	uint8_t i = 0;
	uint8_t returnValue = 0;
	for(; i < 8; i++)
	{
		SCK_L;
		Soft_SPI_delay(Half_cycle);
		returnValue <<= 1;
		returnValue += GPIO_ReadInputDataBit(SOFT_SPI_MISO_GPIO_PORT, SOFT_SPI_MISO_PIN);
		SCK_H;
		Soft_SPI_delay(Half_cycle);
	}
	*Data = returnValue;
}
void SPI_Send(uint8_t Data)
{	//SCK空闲状态为高电平
	uint8_t i = 0;
	for(; i < 8; i++)
	{
		if(((Data<<i) & 0x80) == 0x80)//MSB
			
		  MOSI_H;
		else
			MOSI_L;
		SCK_L;
		Soft_SPI_delay(Half_cycle);//SCLK low pulse width
		SCK_H;
		Soft_SPI_delay(Half_cycle);//SCLK high pulse width
	}
}

void Soft_SPI_Transfer(uint16_t Send_Data)
{
	uint8_t	i = 0;
	for(i = 0 ; i < 16 ; i++)
	{	
		if( ((Send_Data << i) & 0x8000) == 0x8000 )
		{
		  MISO_H;
		}		
		else
		{
		  MISO_L;
		}
		SCK_H;	
		Soft_SPI_delay(20);	
		SCK_L;	
		Soft_SPI_delay(20);
	}
}


*/