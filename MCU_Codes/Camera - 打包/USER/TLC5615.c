#include "TLC5615.h"


void Soft_delay(uint32_t time)
{
	while(time)
		--time;
} 

static void delay(uint16_t count)
{
	while(count)
		count--;
}
/*
void TLC5615_Init(uint16_t tmpdata)
{
	MISO_L;
	SCK_L;
	TLC5615_CS_L;
	Soft_SPI_Transfer(tmpdata);
	TLC5615_CS_H;
	Soft_delay(20);
	
//	while((tmpcount--) != 0);
}

*/

/*
void DAC5615(double out)//��ѹ��0.780-4.2v
{
	
	 float temp=out*1000;
    temp/=1000;
    temp=temp*4096/3.3;
    DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12??????????DAC?
	
	
	uint16_t t = (uint16_t)(201.06*out+16.556);
	t <<= 2;
	TLC5615_Init(t);
	
}

*/






static void TLV5618_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}




void ShipDACInit(void)
{
	TLV5618_GPIO_Init();
}



void Write_Data(uint16_t DigNum)
{
	uint8_t	i = 0;
	SCK_H;
	CS_L;														//Ƭѡ��Ч
	for(i = 0;i < 16;i++)
	{	
		if((DigNum << i)&0x8000)
		{
		  DIN_H;
		}		
		else
		{
		  DIN_L;
		}
		SCK_L;	
		delay(10);
		SCK_H;	
		delay(10);
	} 
	SCK_H;
	CS_H;													//Ƭѡ��Ч
}
//==============================================================================================
//�������ƣ�void DAC_Convert(uint16_t Data_A,uint16_t Data_B,uint8_t Channel,uint16_t Mode)
//�������ܣ�ģʽ��ͨ��ѡ�񲢽���DAת��
//��ڲ�����Data_A  Aͨ��ת���ĵ�ѹֵ
//					Data_B  Bͨ��ת���ĵ�ѹֵ
//					Channel ͨ��ѡ��,��ֵΪChannel_A/Channel_B/Channel_AB
//					Mode    �ٶȿ���  0:slow model  1��fast model
//ʹ��˵����Data_A  Data_B�ķ�Χ�ǣ�0x0000~0x0FFF
//					ʹ��һ��ͨ��ʱ������һ��ͨ����ֵ�������⣬������ȱʡ
//===============================================================================================

void DAC_Convert(uint16_t Data_A,uint16_t Data_B,uint8_t Channel,uint8_t Mode)
{
	uint16_t temp;
	if(Mode)
	{
		temp=0x4000;
	}
	else
	{
		temp=0x0000;
	}
	switch(Channel)
	{
		case Channel_A:
			Write_Data(temp|0x8000|(0x0FFF&Data_A));
			break;
		case Channel_B:
			Write_Data(temp|0x0000|(0x0FFF&Data_B));
			break;
		case Channel_AB:
			Write_Data(temp|0x8000|(0x0FFF&Data_A));
			Write_Data(temp|0x1000|(0x0FFF&Data_B));
			break;
		default:break;
	}
}

void ShipDACOutput(float v)
{
	long temp = 0;
	if(v>=3.5)
		v = 3.5;
	else if(v <= 0)
		v = 0;
	temp = (int)818 * v;
	DAC_Convert(0,temp,Channel_B,1);
}