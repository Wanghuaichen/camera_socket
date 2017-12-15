
#include "OLED.h"
#include "OLEDfont.h"
#include "bsp_i2c.h"
#include "stdlib.h"
#include "bsp_SysTick.h"

#define I2C1_OWN_ADDRESS7  0x0A
#define OLED_Address  		 0x78


//���I2Cд����
void Write_OLED_Command(uint8_t Command)
{
	I2C_Start();
	I2C_SendByte(OLED_Address);
	I2C_WaitAck();
	I2C_SendByte(0x00);
	I2C_WaitAck();
	I2C_SendByte(Command);
	I2C_WaitAck();
	I2C_Stop();
}


//���I2Cд����
void Write_OLED_Data(uint8_t Data)
{
	I2C_Start();
	I2C_SendByte(OLED_Address);
	I2C_WaitAck();
	I2C_SendByte(0x40);
	I2C_WaitAck();
	I2C_SendByte(Data);
	I2C_WaitAck();
	I2C_Stop();
}

void Write_OLED_Byte(uint8_t Data,uint8_t Cmd)
{
	
	if(Cmd)
	{Write_OLED_Data(Data);}
	else
	{Write_OLED_Command(Data);}

}


//��������
void OLED_Set_Position(uint8_t x,uint8_t y)
{
	Write_OLED_Byte(0xb0+y,OLED_CMD);
	Write_OLED_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	Write_OLED_Byte((x&0x0f),OLED_CMD);
}

//����OLED��ʾ    
void OLED_Display_On(void)
{
	Write_OLED_Byte(0X8D,OLED_CMD);  //SET DCDC����
	Write_OLED_Byte(0X14,OLED_CMD);  //DCDC ON
	Write_OLED_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	Write_OLED_Byte(0X8D,OLED_CMD);  //SET DCDC����
	Write_OLED_Byte(0X10,OLED_CMD);  //DCDC OFF
	Write_OLED_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}	
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!	  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_OLED_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		Write_OLED_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		Write_OLED_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		Write_OLED_Byte(0,OLED_DATA); 
	} //������ʾ
}
void OLED_On(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_OLED_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		Write_OLED_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		Write_OLED_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		Write_OLED_Byte(1,OLED_DATA); 
	} //������ʾ
}


/*��ָ��λ����ʾһ���ַ�,���������ַ�
 *x:0~127
 *y:0~63
 *mode:0,������ʾ;1,������ʾ				 
 *size:ѡ������ 16/12     */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	uint8_t c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Position(x,y);	
			for(i=0;i<8;i++)
			Write_OLED_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Position(x,y+1);
			for(i=0;i<8;i++)
			Write_OLED_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Position(x,y);
				for(i=0;i<6;i++)
				Write_OLED_Byte(F6x8[c][i],OLED_DATA);				
			}
}
//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
	result*=m;    
	return result;
}	
/*��ʾ2������
 *x,y :�������	 
 *len :���ֵ�λ��
 *size:�����С
 *mode:ģʽ	0,���ģʽ;1,����ģʽ
 *num:��ֵ(0~4294967295)*/ 		  
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	uint8_t j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Position(x,y);	
    for(t=0;t<16;t++)
		{
				Write_OLED_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Position(x,y+1);	
    for(t=0;t<16;t++)
			{	
				Write_OLED_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[])
{ 	
 uint16_t j=0;
 uint8_t x,y;
	
 if(y1%8==0)
	 y=y1/8;      
 else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Position(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	Write_OLED_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
}

void Fill_picture(uint8_t fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		Write_OLED_Byte(0xb0+m,0);		//page0-page1
		Write_OLED_Byte(0x00,0);			//low column start address
		Write_OLED_Byte(0x10,0);			//high column start address
		for(n=0;n<128;n++)
			{
				Write_OLED_Byte(fill_Data,1);
			}
	}
}

//��ʼ��OLED
void OLED_Init(void)
{
//	I2C1_GPIO_Config();
//	I2C1_Mode_Config();		

	Write_OLED_Byte(0xAE,OLED_CMD);//--display off
	Write_OLED_Byte(0x00,OLED_CMD);//---set low column address
	Write_OLED_Byte(0x10,OLED_CMD);//---set high column address
	Write_OLED_Byte(0x40,OLED_CMD);//--set start line address  
	Write_OLED_Byte(0xB0,OLED_CMD);//--set page address
	Write_OLED_Byte(0x81,OLED_CMD); // contract control
	Write_OLED_Byte(0xFF,OLED_CMD);//--128   
	Write_OLED_Byte(0xA1,OLED_CMD);//set segment remap 
	Write_OLED_Byte(0xA6,OLED_CMD);//--normal / reverse
	Write_OLED_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	Write_OLED_Byte(0x3F,OLED_CMD);//--1/32 duty
	Write_OLED_Byte(0xC8,OLED_CMD);//Com scan direction
	Write_OLED_Byte(0xD3,OLED_CMD);//-set display offset
	Write_OLED_Byte(0x00,OLED_CMD);//
	Write_OLED_Byte(0xD5,OLED_CMD);//set osc division
	Write_OLED_Byte(0x80,OLED_CMD);//
	Write_OLED_Byte(0xD8,OLED_CMD);//set area color mode off
	Write_OLED_Byte(0x05,OLED_CMD);//
	Write_OLED_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	Write_OLED_Byte(0xF1,OLED_CMD);//
	Write_OLED_Byte(0xDA,OLED_CMD);//set com pin configuartion
	Write_OLED_Byte(0x12,OLED_CMD);//
	Write_OLED_Byte(0xDB,OLED_CMD);//set Vcomh
	Write_OLED_Byte(0x30,OLED_CMD);//
	Write_OLED_Byte(0x8D,OLED_CMD);//set charge pump enable
	Write_OLED_Byte(0x14,OLED_CMD);//
	Write_OLED_Byte(0xAF,OLED_CMD);//--turn on oled panel
}
