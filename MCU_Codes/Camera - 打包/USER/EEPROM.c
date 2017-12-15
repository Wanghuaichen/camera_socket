#include "EEPROM.h"
#include "Var_Def.h"
#include "stmflash.h"
#include "usart.h"

 extern __IO	int32_t Para_K[16];
 extern __IO	int32_t Para_B[16];
// extern __IO uint8_t Serial_Numb;
 extern __IO  uint8_t 	 NO_Buffer[];	             //NO:ÖÕ¶ËºÅ
 extern __IO  uint8_t    Sensor_amount  ;          //²É¼¯Æ÷ÊıÁ¿
 extern __IO  uint8_t 	 Sensor_ADR[40];	         //²É¼¯Æ÷µØÖ·£¨±àºÅ£©
 extern __IO  uint8_t 	 Sensor_Sel[40];           //´«¸ĞÆ÷ÀàĞÍ
	
extern __IO  uint16_t 	 RTC_1S_Count;             //ÏµÍ³ÆôÍ£ºóµÄÃë¼ÆÊ±
extern __IO	int8_t       AUTO_Control_ON_OFF;      //±ÃÕ¾×Ô¶¯¿ØÖÆ 0 Í£Ö¹ 1 Æô¶¯
extern __IO	int8_t       MUANUAL_Control_ON_OFF;   //±ÃÕ¾ÊÖ¶¯¿ØÖÆ 0 Í£Ö¹ 1 Æô¶¯¯
extern __IO	int8_t       ControlMode ;             
extern __IO	int8_t       Transducer_ControlMode ;  //±äÆµÆ÷¿ØÖÆ·½Ê½ 0£ººãÑ¹±ÃË® 1£ºµãÆµ¿ØÖÆ
extern __IO	int32_t      WaterSource_Level;        //Ë®Ô´µØË®Î»Ñ¡Ôñ

extern __IO	int8_t       FreqConv_SET_OnOff ;      //¿ØÖÆ±äÆµÆ÷¿ª¹Ø0£º¹Ø 1¿ª   ´æ´¢µØÖ·£¿£¿£¿
extern __IO	int16_t      FreqConv_SET_Freq ;       //¿ØÖÆ±äÆµÆ÷ÆµÂÊ**.*Hz  ´æ´¢µØÖ·£¿£¿£¿
extern __IO	int32_t      WaterPressure_SET  ;      //¹ÜµÀÑ¹Á¦ÉèÖÃÖµ£¬******.*Kpa   ´æ´¢µØÖ·£¿£¿£¿
extern __IO	int32_t      WaterSourceLevel_S;       //Ë®Ô´µØË®Î»ÉÏÏŞ   **.*
extern __IO	int32_t      WaterSourceLevel_X;       //Ë®Ô´µØË®Î»ÏÂÏŞ   **.*
extern __IO	int32_t	     CH_Volt_slope[50];
extern __IO	int32_t    	 CH_Volt_zero[50];

extern __IO int16_t CH_Type[16];
extern __IO int16_t CH_Gain[16];
	

uint8_t EEPROM_Buffer[16];	

void NO_ParaRead(void)
{
	uint32_t EEPROM_Address; //  TNS 0531-LC-5A01
	uint8_t  Temp_i;	
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0020;//ÖÕ¶ËºÅ¶ÁÈ¡
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
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0100;//Í¨µÀÅäÖÃ
	for(i=0; i<5; i++)     //4¸öÍ¨µÀ
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
						CH_Volt_slope[0] = 10000;	//µçÑ¹Ğ£×¼K:¡À**.****
						CH_Volt_zero[0] = 0;//µçÑ¹Ğ£×¼B£º¡À*******uV						
						break;
					case 1:
						CH_Volt_slope[1] = 10000;	//µçÁ÷Ğ£×¼K:¡À**.****
						CH_Volt_zero[1] = 0;//µçÁ÷Ğ£×¼B£º¡À*******uA							
						break;
					case 2:
						CH_Volt_slope[2] = 10000;	//µçÁ÷Ğ£×¼K:¡À**.****
						CH_Volt_zero[2] = 0;//µçÁ÷Ğ£×¼B£º¡À*******uA								
						break;
					case 3:
						CH_Volt_slope[3] = 10000;	//µçÑ¹Ğ£×¼K:¡À**.****
						CH_Volt_zero[3] = 0;//µçÑ¹Ğ£×¼B£º¡À*******uV							
						break;	
					case 4:
						CH_Volt_slope[4] = 10000;	//µçÁ÷Ğ£×¼K:¡À**.****
						CH_Volt_zero[4] = 0;//µçÁ÷Ğ£×¼B£º¡À*******uA						
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
 	
 	EEPROM_Address = FLASH_SAVE_ADDR + 0x0300;//Í¨µÀÅäÖÃ
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
			//Para_J[Pos_i] = Para_JKB[0];             //¸üĞÂ²ÎÊı
			Para_K[Pos_i] = Para_JKB[0];
			Para_B[Pos_i] = Para_JKB[1];
		}
		else
		{
       switch(Pos_i)
        {
					case 0://µç³ØµçÑ¹		            
								Para_K[0] = 100000;
								Para_B[0] = 0;					
								break;
					case 1://Ë®Ñ¹´«¸ĞÆ÷
								Para_K[1] = 6250;
								Para_B[1] = -250000;							
								break;
					case 2://Á÷ËÙ
								Para_K[2] = 18750;
								Para_B[2] = -750000;									
								break;
					case 3://Ë®Î»
								Para_K[3] = 10;
								Para_B[3] = 0;								
								break;	
					case 4://±¸ÓÃ
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
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0600;//Í¨µÀÅäÖÃ   
		for(i=0; i<40;i++)//30¸öÍ¨µÀ
		{
			STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
      if(EEPROM_Buffer[0]==0x55)
			{				
				Sensor_ADR[i]=EEPROM_Buffer[3];	//´«¸ĞÆ÷±àºÅ
				Sensor_Sel[i]=EEPROM_Buffer[2]; //´«¸ĞÆ÷ÀàĞÍ
			}
			else
			{
        switch(i)
        {
					case 0:
						Sensor_ADR[0]= 100;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[0]='B';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 1:
						Sensor_ADR[1]= 101;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[1]='M';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 2:
						Sensor_ADR[2]= 102;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[2]='2';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 3:
						Sensor_ADR[3]= 103;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[3]='1';//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 4:
						Sensor_ADR[4]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[4]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 5:
						Sensor_ADR[5]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[5]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 6:
						Sensor_ADR[6]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[6]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 7:
						Sensor_ADR[7]= 107;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[7]= '8';//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 8:
						Sensor_ADR[8]= 108;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[8]= 'L';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 9:
						Sensor_ADR[9]= 109;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[9]= 'N';//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 10:
						Sensor_ADR[10]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[10]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 11:
						Sensor_ADR[11]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[11]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 12:
						Sensor_ADR[12]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[12]=0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 13:
						Sensor_ADR[13]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[13]=0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 14:
						Sensor_ADR[14]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[14]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 15:
						Sensor_ADR[15]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[15]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 16:
						Sensor_ADR[16]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[16]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 17:
						Sensor_ADR[17]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[17]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 18:
						Sensor_ADR[18]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[18]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 19:
						Sensor_ADR[19]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[19]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 20:
						Sensor_ADR[20]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[20]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 21:
						Sensor_ADR[21]= 2;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[21]= '2';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 22:
						Sensor_ADR[22]= 8;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[22]='1';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 23:
						Sensor_ADR[23]= 3;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[23]='3';//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 24:
						Sensor_ADR[24]= 4;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[24]='4';//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 25:
						Sensor_ADR[25]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[25]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 26:
						Sensor_ADR[26]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[26]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 27:
						Sensor_ADR[27]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[27]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 28:
						Sensor_ADR[28]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[28]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 29:
						Sensor_ADR[29]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[29]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;						
					case 30:
						Sensor_ADR[30]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[30]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 31:
						Sensor_ADR[31]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[31]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 32:
						Sensor_ADR[32]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[32]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 33:
						Sensor_ADR[33]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[33]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 34:
						Sensor_ADR[34]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[34]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 35:
						Sensor_ADR[35]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[35]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 36:
						Sensor_ADR[36]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[36]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 37:
						Sensor_ADR[37]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[37]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;	
					case 38:
						Sensor_ADR[38]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[38]= 0;//´«¸ĞÆ÷ÀàĞÍ						
						break;
					case 39:
						Sensor_ADR[39]= 0;	//´«¸ĞÆ÷µØÖ·
						Sensor_Sel[39]= 0;//´«¸ĞÆ÷ÀàĞÍ						
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


void FPS_ParaRead(void)                     //¿ØÖÆ±äÆµÆ÷¿ª¹Ø
{
	uint32_t EEPROM_Address;
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0550;//Í¨µÀÅäÖÃ
	
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
//  FreqConv_SET_OnOff=EEPROM_Buffer[0];
//  RS485_Repeat_Operation=0;	
}

void WSL_ParaRead(void)   //Ë®Ô´µØË®Î»Ñ¡Ôñ
{
  uint32_t EEPROM_Address;	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0580;//Í¨µÀÅäÖÃ

  STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
	
	WaterSource_Level=EEPROM_Buffer[0];
}

void WLS_ParaRead(void)   //Ë®Ô´µØË®Î»ÉÏÏŞÉèÖÃ
{
   uint32_t EEPROM_Address;
	 int32_t  Middle_Tmp;
	
   EEPROM_Address = FLASH_SAVE_ADDR + 0x0590;//Í¨µÀÅäÖÃ
	 STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	
	 WaterSourceLevel_S=EEPROM_Buffer[0];
	 Middle_Tmp = EEPROM_Buffer[1];
	 WaterSourceLevel_S+=(Middle_Tmp<<8);
	 Middle_Tmp = EEPROM_Buffer[2];
	 WaterSourceLevel_S += (Middle_Tmp<<16);
	 Middle_Tmp = EEPROM_Buffer[3];
	 WaterSourceLevel_S += (Middle_Tmp<<24);	
}

void WLl_ParaRead(void)  //Ë®Ô´µØË®Î»ÏÂÏŞ
{
   uint32_t EEPROM_Address;
	 int32_t  Middle_Tmp;
	
   EEPROM_Address = FLASH_SAVE_ADDR + 0x05A0;//Í¨µÀÅäÖÃ
	 STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,2);
	
	 WaterSourceLevel_X=EEPROM_Buffer[0];
	 Middle_Tmp = EEPROM_Buffer[1];
	 WaterSourceLevel_X+=(Middle_Tmp<<8);
	 Middle_Tmp = EEPROM_Buffer[2];
	 WaterSourceLevel_X += (Middle_Tmp<<16);
	 Middle_Tmp = EEPROM_Buffer[3];
	 WaterSourceLevel_X += (Middle_Tmp<<24);
}


void FCM_ParaRead(void)                     //±ÃÕ¾¿ØÖÆ·½Ê½ 0£ººãÑ¹±ÃË® 1£ºµãÆµ¿ØÖÆ  
{
	uint32_t EEPROM_Address;
	
	EEPROM_Address = FLASH_SAVE_ADDR + 0x0560;//Í¨µÀÅäÖÃ
	
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
  Transducer_ControlMode = EEPROM_Buffer[0];

}

void WPS_ParaRead(void)                      //ºãÑ¹¹©Ë®-Ë®Ñ¹ÉèÖÃ
{
  uint32_t EEPROM_Address;
	int32_t  Middle_Tmp;
	
  EEPROM_Address = FLASH_SAVE_ADDR + 0x0520;;//Í¨µÀÅäÖÃ
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

void FQS_ParaRead(void)                     //¿ØÖÆ±äÆµÆ÷ÆµÂÊ
{
  uint32_t EEPROM_Address;
	int32_t  Middle_Tmp;
	
  EEPROM_Address = FLASH_SAVE_ADDR + 0x0540;;//Í¨µÀÅäÖÃ
	STMFLASH_Read(EEPROM_Address,(u16*)EEPROM_Buffer,1);
	
	FreqConv_SET_Freq=EEPROM_Buffer[0];
	Middle_Tmp = EEPROM_Buffer[1];
	FreqConv_SET_Freq+=(Middle_Tmp<<8);

	
}	




