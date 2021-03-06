
#include "stm32f10x.h"
#include "mpu6050.h"
#include "usart.h"


float gRoll = 0;							//滚转角
float gPitch = 0;           	//俯仰角
float gYaw = 0;               //偏航角
float gSpeedX = 0;
float gSpeedY = 0;


/*
函数作用：配置6050通信，配置串口2
*/
void MPU6050_Config(void)
{
	USART2_Config();
}



/*
函数作用：接受串口中断中的数据，将实时角度放入全局变量gRoll,gPitch,gYaw
参数：Rev_Buf:数组名
参数：counter：数组长度
*/
void MPU6050_DataRecv(char* Rev_Buf,int* counter)
{
	if(*counter == 0 && (Rev_Buf[0] != 0x55)) return;              //第 0 号数据不是帧头，跳过
			 (*counter)++;
		if((*counter==11)&&(Rev_Buf[0]==0x55))		
		{
				 *counter = 0;
			   switch(Rev_Buf[1])
				 {
//				   case 0x51: 						//解析三轴加速度 
//							Acceleration[0] = ((short)(Rev_Buf[3]<<8 | Rev_Buf[2]))/32768.0*16;      //X轴加速度
//							Acceleration[1] = ((short)(Rev_Buf[5]<<8 | Rev_Buf[4]))/32768.0*16;      //Y轴加速度
//							Acceleration[2] = ((short)(Rev_Buf[7]<<8 | Rev_Buf[6]))/32768.0*16;      //Z轴加速度
//							Temp  = ((short)(Rev_Buf[9]<<8 | Rev_Buf[8]))/100;       		 						 //温度 
//							break;              
//					  
//				   case 0x52:             //解析三轴角速度
//							Angular[0] = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*2000;      		//X轴角速度
//							Angular[1] = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*2000;      		//Y轴角速度
//							Angular[2] = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*2000;      		//Z轴角速度
//							Temp = ((short)(Rev_Buf[9]<<8| Rev_Buf[8]))/100;       			 				 		//温度
//					   break;               
					
				   case 0x53:              //解析三轴角度
							gRoll = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*180 - 1.38;   							//滚转角
              gPitch = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*180 - 2.126;   						//秆鼋�
              gYaw = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*180;   							//偏航角
					if(fabs(gRoll)>= 40)
							while(1);
							break;               
				   
					 default:	break;				
				 }			      
			
		}	
}

