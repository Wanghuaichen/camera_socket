
#include "stm32f10x.h"
#include "mpu6050.h"
#include "usart.h"


float gRoll = 0;							//��ת��
float gPitch = 0;           	//������
float gYaw = 0;               //ƫ����
float gSpeedX = 0;
float gSpeedY = 0;


/*
�������ã�����6050ͨ�ţ����ô���2
*/
void MPU6050_Config(void)
{
	USART2_Config();
}



/*
�������ã����ܴ����ж��е����ݣ���ʵʱ�Ƕȷ���ȫ�ֱ���gRoll,gPitch,gYaw
������Rev_Buf:������
������counter�����鳤��
*/
void MPU6050_DataRecv(char* Rev_Buf,int* counter)
{
	if(*counter == 0 && (Rev_Buf[0] != 0x55)) return;              //�� 0 �����ݲ���֡ͷ������
			 (*counter)++;
		if((*counter==11)&&(Rev_Buf[0]==0x55))		
		{
				 *counter = 0;
			   switch(Rev_Buf[1])
				 {
//				   case 0x51: 						//����������ٶ� 
//							Acceleration[0] = ((short)(Rev_Buf[3]<<8 | Rev_Buf[2]))/32768.0*16;      //X����ٶ�
//							Acceleration[1] = ((short)(Rev_Buf[5]<<8 | Rev_Buf[4]))/32768.0*16;      //Y����ٶ�
//							Acceleration[2] = ((short)(Rev_Buf[7]<<8 | Rev_Buf[6]))/32768.0*16;      //Z����ٶ�
//							Temp  = ((short)(Rev_Buf[9]<<8 | Rev_Buf[8]))/100;       		 						 //�¶� 
//							break;              
//					  
//				   case 0x52:             //����������ٶ�
//							Angular[0] = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*2000;      		//X����ٶ�
//							Angular[1] = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*2000;      		//Y����ٶ�
//							Angular[2] = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*2000;      		//Z����ٶ�
//							Temp = ((short)(Rev_Buf[9]<<8| Rev_Buf[8]))/100;       			 				 		//�¶�
//					   break;               
					
				   case 0x53:              //��������Ƕ�
							gRoll = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*180 - 1.38;   							//��ת��
              gPitch = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*180 - 2.126;   						//�����
              gYaw = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*180;   							//ƫ����
					if(fabs(gRoll)>= 40)
							while(1);
							break;               
				   
					 default:	break;				
				 }			      
			
		}	
}

