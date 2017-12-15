#ifndef __STM32F103_H
#define __STM32F103_H

#include "stm32f10x.h"
#include "stdint.h"
//USART/UART GPIO Definition

/*USART1  TXD0/RXD0  */
#define USART1_APB2_GPIO_CLK							RCC_APB2Periph_GPIOA

#define USART1_TX_PIN											GPIO_Pin_9
#define USART1_TX_GPIO_PORT								GPIOA
#define USART1_RX_PIN											GPIO_Pin_10
#define USART1_RX_GPIO_PORT								GPIOA

void USART1_GPIO_Config(void);

/*USART2*/
#define USART2_APB2_GPIO_CLK							RCC_APB2Periph_GPIOA

#define USART2_TX_PIN											GPIO_Pin_2
#define USART2_TX_GPIO_PORT								GPIOA
#define USART2_RX_PIN											GPIO_Pin_3
#define USART2_RX_GPIO_PORT								GPIOA

void USART2_GPIO_Config(void);

/*USART3  TXD1/RXD1  */
#define USART3_APB2_GPIO_CLK							RCC_APB2Periph_GPIOB

#define USART3_TX_PIN											GPIO_Pin_10
#define USART3_TX_GPIO_PORT								GPIOB
#define USART3_RX_PIN											GPIO_Pin_11
#define USART3_RX_GPIO_PORT								GPIOB

void USART3_GPIO_Config(void);

/*UART4  TXD2/RXD2  */
#define UART4_APB2_GPIO_CLK								RCC_APB2Periph_GPIOC

#define UART4_TX_PIN											GPIO_Pin_10
#define UART4_TX_GPIO_PORT								GPIOC
#define UART4_RX_PIN											GPIO_Pin_11
#define UART4_RX_GPIO_PORT								GPIOC
#define SEL485_PIN                                             GPIO_Pin_12
#define SEL485_GPIO_PORT								GPIOD

void UART4_GPIO_Config(void);

/*UART5  TXD3/RXD3  */
#define UART5_APB2_GPIO_CLK								RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD

#define UART5_TX_PIN											GPIO_Pin_12
#define UART5_TX_GPIO_PORT								GPIOC
#define UART5_RX_PIN											GPIO_Pin_2
#define UART5_RX_GPIO_PORT								GPIOD
#define GPRS_EN_PIN											  GPIO_Pin_3
#define GPRS_EN_GPIO_PORT								  GPIOD

void UART5_GPIO_Config(void);

//BZ GPIO Definition
#define BZ_GPIO_CLK                                      RCC_APB2Periph_GPIOE

#define BZ_PIN                                                 GPIO_Pin_0
#define BZ_GPIO_PORT                                     GPIOE    
void BZ_GPIO_config(void);

void Relay_GPIO_Config(void);

void Switch_GPIO_Config(void);


//TIM1 

#define TIM1_GPIO_CLK                                        RCC_APB2Periph_GPIOA            

#define TIM1_PIN                                                     GPIO_Pin_12  
#define TIM1_GPIO_PORT                                       GPIOA

void TIM1_GPIO_Config(void);


//

//
//EEPROM and Font SPI Interface pins
#define EEPROM_SPI_GPIO_CLK            			RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA

#define EEPROM_SPI_CS_PIN                  	GPIO_Pin_3
#define EEPROM_SPI_CS_GPIO_PORT             GPIOD
#define Font_SPI_CS_PIN                  	  GPIO_Pin_4
#define Font_SPI_CS_GPIO_PORT             	GPIOD
#define EEPROM_SPI_SCK_PIN             			GPIO_Pin_12
#define EEPROM_SPI_SCK_GPIO_PORT            GPIOA
#define EEPROM_SPI_MISO_PIN            			GPIO_Pin_8
#define EEPROM_SPI_MISO_GPIO_PORT          	GPIOA
#define EEPROM_SPI_MOSI_PIN            			GPIO_Pin_11
#define EEPROM_SPI_MOSI_GPIO_PORT           GPIOA


void EEPROM_SPI_GPIO_Config(void);

//Extern WatchDog GPIO Definition
void ExWatchdog(void);
#define ExWatchdog_GPIO_CLK                 RCC_APB2Periph_GPIOA
#define ExWatchdog_WDI_PIN                  GPIO_Pin_11
#define ExWatchdog_WDI_GPIO_PORT            GPIOA

//

#endif
