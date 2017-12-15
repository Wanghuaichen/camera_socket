#include "stm32f103.h"


void USART1_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin 	= USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	

}

void USART2_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART2_APB2_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin 	= USART2_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= USART2_RX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
}

void USART3_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART3_APB2_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin 	= USART3_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= USART3_RX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
}

void UART4_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(UART4_APB2_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin 	= UART4_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(UART4_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= UART4_RX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART4_RX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	=SEL485_PIN ;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_Init(SEL485_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(SEL485_GPIO_PORT,SEL485_PIN);//接收状态 ，控制引脚拉低
	//GPIO_SetBits(SEL485_GPIO_PORT,SEL485_PIN);// 发送状态，控制引脚置高

}

void UART5_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(UART5_APB2_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin 	= UART5_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(UART5_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= UART5_RX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART5_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPRS_EN_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_Init(GPRS_EN_GPIO_PORT, &GPIO_InitStructure);	
	GPIO_SetBits(GPRS_EN_GPIO_PORT,GPRS_EN_PIN);
}




void EEPROM_SPI_GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(EEPROM_SPI_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
  GPIO_InitStructure.GPIO_Pin = EEPROM_SPI_CS_PIN;
	GPIO_Init(EEPROM_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(EEPROM_SPI_CS_GPIO_PORT, EEPROM_SPI_CS_PIN);
  
	GPIO_InitStructure.GPIO_Pin = Font_SPI_CS_PIN;
	GPIO_Init(Font_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(Font_SPI_CS_GPIO_PORT, Font_SPI_CS_PIN);
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_SPI_MOSI_PIN;
	GPIO_Init(EEPROM_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(EEPROM_SPI_MOSI_GPIO_PORT, EEPROM_SPI_MOSI_PIN);

	GPIO_InitStructure.GPIO_Pin = EEPROM_SPI_SCK_PIN;
	GPIO_Init(EEPROM_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(EEPROM_SPI_SCK_GPIO_PORT, EEPROM_SPI_SCK_PIN);

	GPIO_InitStructure.GPIO_Pin = EEPROM_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//悬浮输入模式
	GPIO_Init(EEPROM_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
}






void TIM1_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(TIM1_GPIO_CLK , ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = TIM1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //
  GPIO_Init(TIM1_GPIO_PORT, &GPIO_InitStructure);
	
}




void ExWatchdog_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ExWatchdog_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = ExWatchdog_WDI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ExWatchdog_WDI_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(ExWatchdog_WDI_GPIO_PORT, ExWatchdog_WDI_PIN);
}
