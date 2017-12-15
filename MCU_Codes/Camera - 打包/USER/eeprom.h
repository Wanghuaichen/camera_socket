#ifndef	__EEPROM_H
#define	__EEPROM_H

#include "stm32f103.h"
#include "usart.h"
//#include "Var_Def.h"

#define read_requ 0x03
#define write_requ 0x02
#define write_en_data 0x06

#define EEPROM_CS_H     GPIO_SetBits(EEPROM_SPI_CS_GPIO_PORT, EEPROM_SPI_CS_PIN)
#define EEPROM_CS_L     GPIO_ResetBits(EEPROM_SPI_CS_GPIO_PORT, EEPROM_SPI_CS_PIN)
#define EEPROM_MOSI_H   GPIO_SetBits(EEPROM_SPI_MOSI_GPIO_PORT, EEPROM_SPI_MOSI_PIN)
#define EEPROM_MOSI_L	  GPIO_ResetBits(EEPROM_SPI_MOSI_GPIO_PORT, EEPROM_SPI_MOSI_PIN)
#define EEPROM_SCK_H		GPIO_SetBits(EEPROM_SPI_SCK_GPIO_PORT, 	EEPROM_SPI_SCK_PIN)
#define EEPROM_SCK_L		GPIO_ResetBits(EEPROM_SPI_SCK_GPIO_PORT, 	EEPROM_SPI_SCK_PIN)
#define TER_NUMBER_BASE         0x0020          //�ն˺Ż���ַ
#define PARA_SZ_BASE            0x0100          //ͨ����ѹУ׼��������ַ
#define PARA_J_K_B_BASE         0x0300          //ͨ��������У׼��������ַ
#define CHANNEL_INFOR_BASE      0x0500          //ͨ����Ϣ(�Ƿ���������������͡����ź����͡��Ŵ���)����ַ
#define SAMPLE_SWITCH_OFFSET    0x0000
#define SENSOR_TYPE_OFFSET      0x0001
#define SIGNAL_TYPE_OFFSET      0x0006
#define GAIN_OFFSET             0x000A


void NO_ParaRead(void);
//void CPA_ParaRead(void);
void CSV_ParaRead(void);
void CSP_ParaRead(void);
void SNS_ParaRead(void);//������Ĳɼ�������
void ADS_ParaRead(void);//�ɼ�����ַ����ţ�

void PWS_ParaRead(void);//��վ����ϵͳ���� 
void FPS_ParaRead(void);//���Ʊ�Ƶ������
void FCM_ParaRead(void);//��վ���Ʒ�ʽ  �� ��ѹ\�Զ�
void WPS_ParaRead(void);//��ѹ��ˮ-ˮѹ����
void FQS_ParaRead(void);//��Ƶ��Ƶ��
void WSL_ParaRead(void);//ˮԴ��ˮλѡ��
void WF_ParaRead(void);//����-�ۻ���

void WLS_ParaRead(void);
void WLl_ParaRead(void);

#define HZGB15x16BaseAdd		0
#define HZGB11x12BaseAdd		0x3CF80
#define ZFGB08x16BaseAdd		0x3B7D0
#define ZFGB06x12BaseAdd		0x66D4C
#define ZFASC08x16BaseAdd		0x3B7C0
#define ZFASC06x12BaseAdd		0x66D40
#define ZFASC07x08BaseAdd		0x66C0
#define ZFASC05x07BaseAdd		0x3BFC0
#define ZFArial16BaseAdd		0x3C2C0
#define ZFArial12BaseAdd		0x67340
#define GBUnicodeBaseAdd		0x2F00
#define UnicodeGBBaseAdd		0x67D70

#define Read_Command				0x03
#define FAST_Read_Command		0x0B

void HZGB15x16(uint8_t *pBuffer, uint8_t *c);
void HZGB11x12(uint8_t *pBuffer, uint8_t *c);
void ZFGB08x16(uint8_t *pBuffer, uint8_t *c);
void ZFGB06x12(uint8_t *pBuffer, uint8_t *c);
void ZFASC08x16(uint8_t *pBuffer, uint8_t c);
void ZFASC06x12(uint8_t *pBuffer, uint8_t c);
void ZFASC07x08(uint8_t *pBuffer, uint8_t c);
void ZFASC05x07(uint8_t *pBuffer, uint8_t c);


#endif

