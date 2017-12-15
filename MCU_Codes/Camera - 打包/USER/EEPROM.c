#include "EEPROM.h"
#include "Var_Def.h"
#include "stmflash.h"
#include "usart.h"

 extern __IO	int32_t Para_K[16];
 extern __IO	int32_t Para_B[16];
// extern __IO uint8_t Serial_Numb;
 extern __IO  uint8_t 	 NO_Buffer[];	             //NO:�ն˺�
 extern __IO  uint8_t    Sensor_amount  ;          //�ɼ�������
 extern __IO  uint8_t 	 Sensor_ADR[40];	         //�ɼ�����ַ����ţ�
 extern __IO  uint8_t 	 Sensor_Sel[40];           //����������
	
extern __IO  uint16_t 	 RTC_1S_Count;             //ϵͳ��ͣ������ʱ
extern __IO	int8_t       AUTO_Control_ON_OFF;      //��վ�Զ����� 0 ֹͣ 1 ����
extern __IO	int8_t       MUANUAL_Control_ON_OFF;   //��վ�ֶ����� 0 ֹͣ 1 �����
extern __IO	int8_t       ControlMode ;             
extern __IO	int8_t       Transducer_ControlMode ;  //��Ƶ�����Ʒ�ʽ 0����ѹ��ˮ 1����Ƶ����
extern __IO	int32_t      WaterSource_Level;        //ˮԴ��ˮλѡ��

extern __IO	int8_t       FreqConv_SET_OnOff ;      //���Ʊ�Ƶ������0���� 1��   �洢��ַ������
extern __IO	int16_t      FreqConv_SET_Freq ;       //���Ʊ�Ƶ��Ƶ��**.*Hz  �洢��ַ������
extern __IO	int32_t      WaterPressure_SET  ;      //�ܵ�ѹ������ֵ��******.*Kpa   �洢��ַ������
extern __IO	int32_t      WaterSourceLevel_S;       //ˮԴ��ˮλ����   **.*
extern __IO	int32_t      WaterSourceLevel_X;       //ˮԴ��ˮλ����   **.*
extern __IO	int32_t	     CH_Volt_slope[50];
extern __IO	int32_t    	 CH_Volt_zero[50];

extern __IO int16_t CH_Type[16];
extern __IO int16_t CH_Gain[16];
	

uint8_t EEPROM_Buffer[16];	

void NO_ParaRead(void)
{
	uint32_t EEPROM_Address; //  TNS 0531-LC-5A01
	uint8_t  Temp_i;	
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0020;//�ն˺Ŷ�ȡ
  STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,12);	

	for(Temp_i=0; Temp_i<12; Temp_i++)
	{
	  NO_Buffer[Temp_i+3] = EEPROM_Buffer[Temp_i];
	}
}


void CSV_ParaRead(void)
{
	uint32_t EEPROM_Address;
	int32_t  Para_Slope,Para_Zero,Middle_Tmp;
	uint8_t i = 0;	
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0100;//ͨ������
	for(i=0; i<5; i++)     //4��ͨ��
	{
		STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,5);
		if(EEPROM_Buffer[0]==0x55)
		{
			Para_Slope = EEPROM_Buffer[2];
			Middle_Tmp = EEPROM_Buffer[3];
			Para_Slope += (Middle_Tmp<<8);
			Middle_Tmp = EEPROM_Buffer[4];
			Para_Slope += (Middle_Tmp<<16);
			Middle_Tmp = EEPROM_Buffer[5];
			Para_Slope += (Middle_Tmp<<24);
			CH_Volt_slope[i] = Para_Slope;
				
			Para_Zero = EEPROM_Buffer[6];
			Middle_Tmp = EEPROM_Buffer[7];
			Para_Zero += (Middle_Tmp<<8);
			Middle_Tmp = EEPROM_Buffer[8];
			Para_Zero += (Middle_Tmp<<16);
			Middle_Tmp = EEPROM_Buffer[9];
			Para_Zero += (Middle_Tmp<<24);
			CH_Volt_zero[i] = Para_Zero;
		}
		else
		{
        switch(i)
        {
					case 0:
						CH_Volt_slope[0] = 10000;	//��ѹУ׼K:��**.****
						CH_Volt_zero[0] = 0;//��ѹУ׼B����*******uV						
						break;
					case 1:
						CH_Volt_slope[1] = 10000;	//����У׼K:��**.****
						CH_Volt_zero[1] = 0;//����У׼B����*******uA							
						break;
					case 2:
						CH_Volt_slope[2] = 10000;	//����У׼K:��**.****
						CH_Volt_zero[2] = 0;//����У׼B����*******uA								
						break;
					case 3:
						CH_Volt_slope[3] = 10000;	//��ѹУ׼K:��**.****
						CH_Volt_zero[3] = 0;//��ѹУ׼B����*******uV							
						break;	
					case 4:
						CH_Volt_slope[4] = 10000;	//����У׼K:��**.****
						CH_Volt_zero[4] = 0;//����У׼B����*******uA						
						break;
					default:				
						break;	
				}
			}
		EEPROM_Address += 0x10;
	}
	Delayms(20);
}

 void CSP_ParaRead(void)    //
{
 	uint32_t EEPROM_Address;
 	int32_t  Para_JKB[3],Middle_Tmp;
 	uint8_t Pos_i,Pos_j;
 	
 	EEPROM_Address = FLASH_SAVE_ADDR + 0x0300;//ͨ������
 	for(Pos_i=0; Pos_i<5; Pos_i++)
 	{
 		STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,5);
 		if(EEPROM_Buffer[8]==0x55)
		{
			for(Pos_j=0; Pos_j<2; Pos_j++)
			{
				Para_JKB[Pos_j] = EEPROM_Buffer[4*Pos_j];
				Middle_Tmp = EEPROM_Buffer[4*Pos_j+1];
				Para_JKB[Pos_j] += (Middle_Tmp<<8);
				Middle_Tmp = EEPROM_Buffer[4*Pos_j+2];
				Para_JKB[Pos_j] += (Middle_Tmp<<16);
				Middle_Tmp = EEPROM_Buffer[4*Pos_j+3];
				Para_JKB[Pos_j] += (Middle_Tmp<<24);
			}
			//Para_J[Pos_i] = Para_JKB[0];             //���²���
			Para_K[Pos_i] = Para_JKB[0];
			Para_B[Pos_i] = Para_JKB[1];
		}
		else
		{
       switch(Pos_i)
        {
					case 0://��ص�ѹ		            
								Para_K[0] = 100000;
								Para_B[0] = 0;					
								break;
					case 1://ˮѹ������
								Para_K[1] = 6250;
								Para_B[1] = -250000;							
								break;
					case 2://����
								Para_K[2] = 18750;
								Para_B[2] = -750000;									
								break;
					case 3://ˮλ
								Para_K[3] = 10;
								Para_B[3] = 0;								
								break;	
					case 4://����
								Para_K[4] = 100000;
								Para_B[4] = 0;						
								break;
					default:				
						break;	
				}
	  }
 		EEPROM_Address += 0x10;
	}
}


void ADS_ParaRead(void)
{
	uint32_t EEPROM_Address;
	uint8_t  i;	
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0600;//ͨ������   
		for(i=0; i<40;i++)//30��ͨ��
		{
			STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
      if(EEPROM_Buffer[0]==0x55)
			{				
				Sensor_ADR[i]=EEPROM_Buffer[3];	//���������
				Sensor_Sel[i]=EEPROM_Buffer[2]; //����������
			}
			else
			{
        switch(i)
        {
					case 0:
						Sensor_ADR[0]= 100;	//��������ַ
						Sensor_Sel[0]='B';//����������						
						break;
					case 1:
						Sensor_ADR[1]= 101;	//��������ַ
						Sensor_Sel[1]='M';//����������						
						break;
					case 2:
						Sensor_ADR[2]= 102;	//��������ַ
						Sensor_Sel[2]='2';//����������						
						break;
					case 3:
						Sensor_ADR[3]= 103;	//��������ַ
						Sensor_Sel[3]='1';//����������						
						break;	
					case 4:
						Sensor_ADR[4]= 0;	//��������ַ
						Sensor_Sel[4]= 0;//����������						
						break;
					case 5:
						Sensor_ADR[5]= 0;	//��������ַ
						Sensor_Sel[5]= 0;//����������						
						break;	
					case 6:
						Sensor_ADR[6]= 0;	//��������ַ
						Sensor_Sel[6]= 0;//����������						
						break;
					case 7:
						Sensor_ADR[7]= 107;	//��������ַ
						Sensor_Sel[7]= '8';//����������						
						break;	
					case 8:
						Sensor_ADR[8]= 108;	//��������ַ
						Sensor_Sel[8]= 'L';//����������						
						break;
					case 9:
						Sensor_ADR[9]= 109;	//��������ַ
						Sensor_Sel[9]= 'N';//����������						
						break;	
					case 10:
						Sensor_ADR[10]= 0;	//��������ַ
						Sensor_Sel[10]= 0;//����������						
						break;
					case 11:
						Sensor_ADR[11]= 0;	//��������ַ
						Sensor_Sel[11]= 0;//����������						
						break;
					case 12:
						Sensor_ADR[12]= 0;	//��������ַ
						Sensor_Sel[12]=0;//����������						
						break;
					case 13:
						Sensor_ADR[13]= 0;	//��������ַ
						Sensor_Sel[13]=0;//����������						
						break;	
					case 14:
						Sensor_ADR[14]= 0;	//��������ַ
						Sensor_Sel[14]= 0;//����������						
						break;
					case 15:
						Sensor_ADR[15]= 0;	//��������ַ
						Sensor_Sel[15]= 0;//����������						
						break;	
					case 16:
						Sensor_ADR[16]= 0;	//��������ַ
						Sensor_Sel[16]= 0;//����������						
						break;
					case 17:
						Sensor_ADR[17]= 0;	//��������ַ
						Sensor_Sel[17]= 0;//����������						
						break;	
					case 18:
						Sensor_ADR[18]= 0;	//��������ַ
						Sensor_Sel[18]= 0;//����������						
						break;
					case 19:
						Sensor_ADR[19]= 0;	//��������ַ
						Sensor_Sel[19]= 0;//����������						
						break;	
					case 20:
						Sensor_ADR[20]= 0;	//��������ַ
						Sensor_Sel[20]= 0;//����������						
						break;
					case 21:
						Sensor_ADR[21]= 2;	//��������ַ
						Sensor_Sel[21]= '2';//����������						
						break;
					case 22:
						Sensor_ADR[22]= 8;	//��������ַ
						Sensor_Sel[22]='1';//����������						
						break;
					case 23:
						Sensor_ADR[23]= 3;	//��������ַ
						Sensor_Sel[23]='3';//����������						
						break;	
					case 24:
						Sensor_ADR[24]= 4;	//��������ַ
						Sensor_Sel[24]='4';//����������						
						break;
					case 25:
						Sensor_ADR[25]= 0;	//��������ַ
						Sensor_Sel[25]= 0;//����������						
						break;	
					case 26:
						Sensor_ADR[26]= 0;	//��������ַ
						Sensor_Sel[26]= 0;//����������						
						break;
					case 27:
						Sensor_ADR[27]= 0;	//��������ַ
						Sensor_Sel[27]= 0;//����������						
						break;	
					case 28:
						Sensor_ADR[28]= 0;	//��������ַ
						Sensor_Sel[28]= 0;//����������						
						break;
					case 29:
						Sensor_ADR[29]= 0;	//��������ַ
						Sensor_Sel[29]= 0;//����������						
						break;						
					case 30:
						Sensor_ADR[30]= 0;	//��������ַ
						Sensor_Sel[30]= 0;//����������						
						break;
					case 31:
						Sensor_ADR[31]= 0;	//��������ַ
						Sensor_Sel[31]= 0;//����������						
						break;
					case 32:
						Sensor_ADR[32]= 0;	//��������ַ
						Sensor_Sel[32]= 0;//����������						
						break;
					case 33:
						Sensor_ADR[33]= 0;	//��������ַ
						Sensor_Sel[33]= 0;//����������						
						break;	
					case 34:
						Sensor_ADR[34]= 0;	//��������ַ
						Sensor_Sel[34]= 0;//����������						
						break;
					case 35:
						Sensor_ADR[35]= 0;	//��������ַ
						Sensor_Sel[35]= 0;//����������						
						break;	
					case 36:
						Sensor_ADR[36]= 0;	//��������ַ
						Sensor_Sel[36]= 0;//����������						
						break;
					case 37:
						Sensor_ADR[37]= 0;	//��������ַ
						Sensor_Sel[37]= 0;//����������						
						break;	
					case 38:
						Sensor_ADR[38]= 0;	//��������ַ
						Sensor_Sel[38]= 0;//����������						
						break;
					case 39:
						Sensor_ADR[39]= 0;	//��������ַ
						Sensor_Sel[39]= 0;//����������						
						break;						
					default:break;
				}
      }
			EEPROM_Address += 0x10;
		}			
}

void SNS_ParaRead(void)
{
	uint32_t EEPROM_Address;
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0500;
	
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	if(EEPROM_Buffer[3]==0x55) Sensor_amount=EEPROM_Buffer[0]*100+	EEPROM_Buffer[1]*10+EEPROM_Buffer[2];
  else 	Sensor_amount=4;  		
}


void FPS_ParaRead(void)                     //���Ʊ�Ƶ������
{
	uint32_t EEPROM_Address;
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0550;//ͨ������
	
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
//  FreqConv_SET_OnOff=EEPROM_Buffer[0];
//  RS485_Repeat_Operation=0;	
}

void WSL_ParaRead(void)   //ˮԴ��ˮλѡ��
{
  uint32_t EEPROM_Address;	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0580;//ͨ������

  STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
	
	WaterSource_Level=EEPROM_Buffer[0];
}

void WLS_ParaRead(void)   //ˮԴ��ˮλ��������
{
   uint32_t EEPROM_Address;
	 int32_t  Middle_Tmp;
	
   EEPROM_Address = FLASH_SAVE_ADDR + 0x0590;//ͨ������
	 STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	
	 WaterSourceLevel_S=EEPROM_Buffer[0];
	 Middle_Tmp = EEPROM_Buffer[1];
	 WaterSourceLevel_S+=(Middle_Tmp<<8);
	 Middle_Tmp = EEPROM_Buffer[2];
	 WaterSourceLevel_S += (Middle_Tmp<<16);
	 Middle_Tmp = EEPROM_Buffer[3];
	 WaterSourceLevel_S += (Middle_Tmp<<24);	
}

void WLl_ParaRead(void)  //ˮԴ��ˮλ����
{
   uint32_t EEPROM_Address;
	 int32_t  Middle_Tmp;
	
   EEPROM_Address = FLASH_SAVE_ADDR + 0x05A0;//ͨ������
	 STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	
	 WaterSourceLevel_X=EEPROM_Buffer[0];
	 Middle_Tmp = EEPROM_Buffer[1];
	 WaterSourceLevel_X+=(Middle_Tmp<<8);
	 Middle_Tmp = EEPROM_Buffer[2];
	 WaterSourceLevel_X += (Middle_Tmp<<16);
	 Middle_Tmp = EEPROM_Buffer[3];
	 WaterSourceLevel_X += (Middle_Tmp<<24);
}


void FCM_ParaRead(void)                     //��վ���Ʒ�ʽ 0����ѹ��ˮ 1����Ƶ����  
{
	uint32_t EEPROM_Address;
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0560;//ͨ������
	
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
  Transducer_ControlMode = EEPROM_Buffer[0];

}

void WPS_ParaRead(void)                      //��ѹ��ˮ-ˮѹ����
{
  uint32_t EEPROM_Address;
	int32_t  Middle_Tmp;
	
  EEPROM_Address = FLASH_SAVE_ADDR + 0x0520;;//ͨ������
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	
	 WaterPressure_SET=EEPROM_Buffer[0];
	 Middle_Tmp = EEPROM_Buffer[1];
	 WaterPressure_SET+=(Middle_Tmp<<8);
	 Middle_Tmp = EEPROM_Buffer[2];
	 WaterPressure_SET += (Middle_Tmp<<16);
	 Middle_Tmp = EEPROM_Buffer[3];
	 WaterPressure_SET += (Middle_Tmp<<24);
	
//	RS485_Repeat_Operation=0;
}

void FQS_ParaRead(void)                     //���Ʊ�Ƶ��Ƶ��
{
  uint32_t EEPROM_Address;
	int32_t  Middle_Tmp;
	
  EEPROM_Address = FLASH_SAVE_ADDR + 0x0540;;//ͨ������
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
	
	FreqConv_SET_Freq=EEPROM_Buffer[0];
	Middle_Tmp = EEPROM_Buffer[1];
	FreqConv_SET_Freq+=(Middle_Tmp<<8);

	
}	




