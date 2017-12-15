
#include "stm32f10x.h"
#include "mpu6050.h"
#include "usart.h"


float gRoll = 0;							//¹ö×ª½Ç
float gPitch = 0;           	//¸©Ñö½Ç
float gYaw = 0;               //Æ«º½½Ç
float gSpeedX = 0;
float gSpeedY = 0;


/*
º¯Êı×÷ÓÃ£ºÅäÖÃ6050Í¨ĞÅ£¬ÅäÖÃ´®¿Ú2
*/
void MPU6050_Config(void)
{
	USART2_Config();
}



/*
º¯Êı×÷ÓÃ£º½ÓÊÜ´®¿ÚÖĞ¶ÏÖĞµÄÊı¾İ£¬½«ÊµÊ±½Ç¶È·ÅÈëÈ«¾Ö±äÁ¿gRoll,gPitch,gYaw
²ÎÊı£ºRev_Buf:Êı×éÃû
²ÎÊı£ºcounter£ºÊı×é³¤¶È
*/
void MPU6050_DataRecv(char* Rev_Buf,int* counter)
{
	if(*counter == 0 && (Rev_Buf[0] != 0x55)) return;              //µÚ 0 ºÅÊı¾İ²»ÊÇÖ¡Í·£¬Ìø¹ı
			 (*counter)++;
		if((*counter==11)&&(Rev_Buf[0]==0x55))		
		{
				 *counter = 0;
			   switch(Rev_Buf[1])
				 {
//				   case 0x51: 						//½âÎöÈıÖá¼ÓËÙ¶È 
//							Acceleration[0] = ((short)(Rev_Buf[3]<<8 | Rev_Buf[2]))/32768.0*16;      //XÖá¼ÓËÙ¶È
//							Acceleration[1] = ((short)(Rev_Buf[5]<<8 | Rev_Buf[4]))/32768.0*16;      //YÖá¼ÓËÙ¶È
//							Acceleration[2] = ((short)(Rev_Buf[7]<<8 | Rev_Buf[6]))/32768.0*16;      //ZÖá¼ÓËÙ¶È
//							Temp  = ((short)(Rev_Buf[9]<<8 | Rev_Buf[8]))/100;       		 						 //ÎÂ¶È 
//							break;              
//					  
//				   case 0x52:             //½âÎöÈıÖá½ÇËÙ¶È
//							Angular[0] = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*2000;      		//XÖá½ÇËÙ¶È
//							Angular[1] = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*2000;      		//YÖá½ÇËÙ¶È
//							Angular[2] = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*2000;      		//ZÖá½ÇËÙ¶È
//							Temp = ((short)(Rev_Buf[9]<<8| Rev_Buf[8]))/100;       			 				 		//ÎÂ¶È
//					   break;               
					
				   case 0x53:              //½âÎöÈıÖá½Ç¶È
							gRoll = ((short)(Rev_Buf[3]<<8| Rev_Buf[2]))/32768.0*180 - 1.38;   							//¹ö×ª½Ç
              gPitch = ((short)(Rev_Buf[5]<<8| Rev_Buf[4]))/32768.0*180 - 2.126;   						//¸Ñö½Ç
              gYaw = ((short)(Rev_Buf[7]<<8| Rev_Buf[6]))/32768.0*180;   							//Æ«º½½Ç
					if(fabs(gRoll)>= 40)
							while(1);
							break;               
				   
					 default:	break;				
				 }			      
			
		}	
}

