#include "key_new.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "OLED.h"

const uint8_t KeyData[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
extern uint8_t Key_Num;
	
static void Key_Delay()					                                 //简单延时函数，用于键盘消抖							
{
	__IO uint32_t nCount = 150000;
	while(nCount)
	{
		nCount--;
	}
}
static void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin = Key_Row ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 							
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Key_Port, &GPIO_InitStructure);
	GPIO_ResetBits(Key_Port,Key_Line);														//初始行全部置0
	
	GPIO_InitStructure.GPIO_Pin  = Key_Line;											
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(Key_Port, &GPIO_InitStructure);
}

static void Key_Interruput_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(Key_EXTI_PortSource,Key_EXTI_PinSource1);
	EXTI_ClearITPendingBit(Key_EXTI_Line1);
	EXTI_InitStructure.EXTI_Line = Key_EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(Key_EXTI_PortSource,Key_EXTI_PinSource2);
	EXTI_ClearITPendingBit(Key_EXTI_Line2);
	EXTI_InitStructure.EXTI_Line = Key_EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(Key_EXTI_PortSource,Key_EXTI_PinSource3);
	EXTI_ClearITPendingBit(Key_EXTI_Line3);
	EXTI_InitStructure.EXTI_Line = Key_EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(Key_EXTI_PortSource,Key_EXTI_PinSource4);
	EXTI_ClearITPendingBit(Key_EXTI_Line4);
	EXTI_InitStructure.EXTI_Line = Key_EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}



uint8_t Key_Check(void)
{
	uint8_t  i = 0;
	uint8_t  KeyVal = 0;
	uint32_t tmpFlag = 0;
	uint32_t ReadValue = 0;
	ReadValue=GPIO_ReadInputData(Key_Port);
	tmpFlag=(ReadValue&0x000F);							//判断第几列有键按下

	switch(tmpFlag)
	{
		case 0x000E:										      //第1列有键按下
		{
			for(i = 0;i<4;i++)
			{
				GPIO_SetBits(Key_Port,Key_Row);     //全行置1
				GPIO_ResetBits(Key_Port,(Key_Row_1<<i)); 											//第i行置0
				if(GPIO_ReadInputDataBit(Key_Port,Key_Line_1) == 0)           //有键按下   
				{
					Key_Delay();														                    //延时消抖
					while(GPIO_ReadInputDataBit(Key_Port,Key_Line_1) == 0);		  //等待按键被松开
					KeyVal = KeyData[i][0];
					break;
				}
			}
			GPIO_ResetBits(Key_Port ,Key_Row);					                    //全行置0，等待下次按键	
		  break;
		}
		
		case 0x000D:
		{
			for(i = 0;i<4;i++)
			{
				GPIO_SetBits(Key_Port,Key_Row);
				GPIO_ResetBits(Key_Port,(Key_Row_1<<i));
				if(GPIO_ReadInputDataBit(Key_Port,Key_Line_2) == 0)
				{
          Key_Delay();
					while(GPIO_ReadInputDataBit(Key_Port,Key_Line_2) == 0);
					KeyVal = KeyData[i][1];
					break;
				}
			}
			GPIO_ResetBits(Key_Port ,Key_Row);
		  break;
		}
		
		case 0x000B:
		{
			for(i = 0;i<4;i++)
			{
				GPIO_SetBits(Key_Port,Key_Row);
				GPIO_ResetBits(Key_Port,(Key_Row_1<<i));
				if(GPIO_ReadInputDataBit(Key_Port,Key_Line_3) == 0)
				{
//					delay_ms(10);
					Key_Delay();
					while(GPIO_ReadInputDataBit(Key_Port,Key_Line_3) == 0);
					KeyVal = KeyData[i][2];
					break;
				}
			}
			GPIO_ResetBits(Key_Port ,Key_Row);
		  break;
		}
		
		case 0x0007:
		{
			for(i = 0;i<4;i++)
			{
				GPIO_SetBits(Key_Port,Key_Row);
				GPIO_ResetBits(Key_Port,(Key_Row_1<<i));
				if(GPIO_ReadInputDataBit(Key_Port,Key_Line_4) == 0)
				{
//					delay_ms(10);
					Key_Delay();
					while(GPIO_ReadInputDataBit(Key_Port,Key_Line_4) == 0);
					KeyVal = KeyData[i][3];
					break;
				}
			}
			GPIO_ResetBits(Key_Port ,Key_Row);
		  break;
		}
		default: break;	
	}
	GPIO_ResetBits(Key_Port ,Key_Row);
	return KeyVal;															 //返回键值
}



void Key_Config(void)
{
	Key_GPIO_Config();
	Key_Interruput_Config();
}




double   KeyInput_Val = 0.0;                                    //键盘输入值
uint32_t Input_Integer = 0;                                     //键盘输入整数部分
uint32_t Input_Decimal = 0;                                     //键盘输入小数部分
char     Input_Str[16] = {0};                                   //将输入数字转换成字符串显示在OLED上
uint8_t Point_Flag = 0;                                         //小数点输入标志位，有小数点输入为1，否则为0

void Key_Input(void)
{
	static uint8_t temp = 0;                                       //小数位数                                        
	switch(Key_Num)
	{
		case 1:             //数字1
		{
			if(Point_Flag == 0)
			{
				Input_Integer = 10 * Input_Integer + 1;
			}
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 1;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 2:             //数字2
		{
			if(Point_Flag == 0)
			{
				Input_Integer = 10 * Input_Integer + 2;
			}
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 2;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 3:             //数字3
		{
			if(Point_Flag == 0)
			{
				Input_Integer = 10 * Input_Integer + 3;
			}
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 3;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 5:             //数字4
		{
			if(Point_Flag == 0)
			{
				Input_Integer = 10 * Input_Integer + 4;
			}
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 4;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 6:             //数字5
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 5;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 5;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 7:             //数字6
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 6;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 6;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
    case 9:             //数字7
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 7;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 7;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 10:            //数字8
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 8;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 8;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 11:            //数字9
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 9;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 9;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 13:            //小数点.
		{
			Point_Flag = 1;
			Show_Input();
			break;
		}
		case 14:            //数字0
		{
			if(Point_Flag == 0)
			 {
				Input_Integer = 10 * Input_Integer + 0;
			 }
			else 
			{
				temp++;
				Input_Decimal = 10 * Input_Decimal + 0;
			}
			Key_Num = 0;
			Show_Input();
			break;
		}
		case 15:            //清零
		{
			Input_Integer = 0;
			Input_Decimal = 0;
			KeyInput_Val = 0.0;
			Point_Flag = 0;
		  temp = 0;  
			Key_Num = 0;
			memset(Input_Str,0,sizeof(Input_Str));
			OLED_ShowString(32,2,"0           ",16);             //12个空格清空	
			break;
		}
		case 16:             //后退，清除一个输入
		{
			if(Point_Flag == 0)
			{
				Input_Integer = Input_Integer/10;
				OLED_ShowString(32,2,"            ",16);             //12个空格清空
				sprintf(Input_Str,"%d",Input_Integer);
	      OLED_ShowString(32,2,Input_Str,16);
			}
			else
			{
				temp--;
				Input_Decimal = Input_Decimal/10;
				OLED_ShowString(32,2,"            ",16);
				sprintf(Input_Str,"%d.%d",Input_Integer,Input_Decimal);
		    OLED_ShowString(32,2,Input_Str,16);
				if(Input_Decimal == 0)                               //到小数点位
				{
					OLED_ShowString(32,2,"            ",16);            
					sprintf(Input_Str,"%d.%d",Input_Integer,Input_Decimal);
		      OLED_ShowString(32,2,Input_Str,16);
				}
				
				if(temp == 255)                                      //清除小数点
				{
					temp = 0;
					Point_Flag = 0;
					OLED_ShowString(32,2,"            ",16); 
					sprintf(Input_Str,"%d",Input_Integer);
	        OLED_ShowString(32,2,Input_Str,16);
				}
			}
			Key_Num = 0;
			break;
		}
		case 4:             //OK键,输入完成按OK键结束
		{
			KeyInput_Val = Input_Integer + Input_Decimal * pow(10,-temp);
			temp = 0;                            //小数位清零
			Input_Integer = 0;                   //整数部分清零，等待下一次输入
			Input_Decimal = 0;                   //小数部分清零，等待下一次输入
			Point_Flag = 0;                      //清除小数点标志位
			Key_Num = 0;
			memset(Input_Str,0,sizeof(Input_Str));
			break;
		}
		case 8:             //功能待定
			Key_Num = 0;break;
		case 12:            //功能待定
			Key_Num = 0;break;
		
    default:break;
			
	}	
}

//将目前输入值转换为字符串输出到OLED
void Show_Input(void)
{
	if(Point_Flag == 0)
	{
		sprintf(Input_Str,"%d",Input_Integer);
	  OLED_ShowString(32,2,Input_Str,16);
	}
	else
	{
	  sprintf(Input_Str,"%d.%d",Input_Integer,Input_Decimal);
		OLED_ShowString(32,2,Input_Str,16);
	}
}
