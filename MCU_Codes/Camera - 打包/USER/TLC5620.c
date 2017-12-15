
#include "TLC5620.h"

/*==================================================================
//�������� LTC5620_DAC_OUTPUT
//���ߣ�
//���ڣ�
//���ܣ�   ����LTC5620 DA���
//���������channel LTC5620 ���ͨ����LTC5620_CHANNEL_A��Ӧͨ��A��
                                      LTC5620_CHANNEL_B��Ӧͨ��B��
                                      LTC5620_CHANNEL_C��Ӧͨ��C��
                                      LTC5620_CHANNEL_D��Ӧͨ��D;
//����ֵ��  ��
//�޸ļ�¼��
//==================================================================*/
void LTC5620_DAC_OUTPUT(uint8_t channel,uint16_t RNG_Data)
{
	uint8_t i;
	uint8_t tmp;
	uint16_t LTC5620_DATA = (((channel << 9)|(RNG_Data & 0x01FF))<<5);
	
	for(i = 0; i < 11; i++)
	{
		tmp = (((LTC5620_DATA << i) & 0x8000)>>8);
		switch(tmp)
		{
			case 0x80:
				write_CPLD(0x88, 0x01);//DATA_H
				write_CPLD(0x87, 0x01);//CLK_H
				write_CPLD(0x87, 0x00);//CLK_L
				break;
			case 0x00:
				write_CPLD(0x88, 0x00);//DATA_L
				write_CPLD(0x87, 0x01);//CLK_H
				write_CPLD(0x87, 0x00);//CLK_L
				break;
			default:break;
		}
	}
	write_CPLD(0x89, 0x00);//LOAD_L
	write_CPLD(0x89, 0x01);//LOAD_H
	write_CPLD(0x8A, 0x00);//LDAC_L
	write_CPLD(0x8A, 0x01);//LDAC_H
}
uint16_t V_conductivity(uint16_t Vmv)
{
	uint16_t RNG_Data;
	uint8_t  RNG;
	uint16_t Data;
	if(Vmv > 1250)
	{
		RNG = 1;
		Data = (uint16_t)((uint32_t)(Vmv + 1250)*128/2500);
		if(Data >= 256)
			Data = 255;
	}
	else
	{
		RNG = 0;
		Data = (uint16_t)((uint32_t)(Vmv + 1250)*256/2500);
		if(Data >= 256)
			Data = 255;
	}
	
	RNG_Data = ((RNG<<8)|(Data&0xFF));
	return (RNG_Data);
}

