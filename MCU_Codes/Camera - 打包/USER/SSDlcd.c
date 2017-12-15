#include "SSDlcd.h"
#include "soft_spi.h"

static uint16_t inc = 0;
static const uint8_t Celsius[]={
	0x00,0x00,0x00,0x00,0x30,0xC0,0x4B,0xF4,
	0x4E,0x1C,0x36,0x0C,0x0C,0x0C,0x0C,0x00,
	0x0C,0x00,0x0C,0x00,0x0C,0x00,0x06,0x0C,
	0x07,0x18,0x03,0xF0,0x00,0x00,0x00,0x00};

extern __IO  Date_TypeDef  System_Date;
extern __IO  Time_TypeDef  System_Time;
extern __IO	int16_t       Local_Battery_Volt; 
extern __IO	int32_t				CH_Phy_Value[16];
extern __IO uint16_t     CH_Type[16];

extern __IO  int8_t        DisplayBuf[32];
extern __IO  uint16_t      Time_POSX;
extern __IO  uint16_t      Time_POSY;
extern __IO  uint16_t      CH_POSX;
extern __IO  uint16_t      CH_Sensor_CHPOSX;
extern __IO  uint16_t      CH_Data_POSX;
extern __IO  uint16_t 		 CH_Unit_POSX;
extern __IO  uint16_t      H_Line_POSY;
extern __IO  uint16_t 		 CH_POSY[16];
extern __IO  uint16_t      L_Line_POSY;
extern __IO  uint16_t      Current_POSY1;
extern __IO  uint16_t      Current_POSY2;
extern __IO  uint16_t      NO_POSX;
extern __IO  uint16_t      NO_POSY;
	
extern __IO	uint16_t			S2_title_X;
extern __IO	uint16_t			S2_title0_Y;
extern __IO	uint16_t			S2_title1_Y;
extern __IO	uint16_t			S2_title2_Y;

extern __IO	uint16_t			S2_item_X;

extern __IO	uint16_t			S2_data_X1;
extern __IO	uint16_t			S2_Y1;
extern __IO	uint16_t			S2_data_X2;
extern __IO	uint16_t			S2_Y2;
extern __IO	uint16_t			S2_data_X3;
extern __IO	uint16_t			S2_Y3;
extern __IO	uint16_t			S2_data_X4;
extern __IO	uint16_t			S2_Y4;
extern __IO	uint16_t			S2_data_X5;
extern __IO	uint16_t			S2_Y5;
extern __IO	uint16_t			S2_data_X6;
extern __IO	uint16_t			S2_Y6;
extern __IO	uint16_t			S2_data_X7;
extern __IO	uint16_t			S2_Y7;
extern __IO	uint16_t			S2_data_X8;
extern __IO	uint16_t			S2_Y8;						

extern __IO uint8_t				CH_Sensor_Sel[16];
extern __IO uint8_t				CH_Sampling[16];
extern __IO	int32_t				CH_Sample[16];
extern __IO	int32_t				CH_Phy_Value[16];

extern __IO	int32_t				Para_J[16];
extern __IO	int32_t				Para_K[16];
extern __IO	int32_t				Para_B[16];
extern __IO	int32_t				 CH_Volt_slope[16];
extern __IO	int32_t				 CH_Volt_zero[16];

extern __IO  uint8_t    	 NO_Buffer[];

extern void FloatChar(uint8_t CountNumb,uint8_t DocNumb,int32_t CovData,uint8_t unint_int_SEL);
	

uint8_t Pre_Page = 0;

static void LCD_Delay(uint32_t time)
{
	while(time>0)
	{
		--time;
	}
}
static void LCD_WR_REG(uint16_t reg)
{
	(*(__IO u16 *) (Bank1_LCD_C)) = ((uint16_t)(reg));
}
static void LCD_WR_DATA(uint16_t data)
{
	(*(__IO u16 *) (Bank1_LCD_D)) = ((uint16_t)(data));
}
static void LCD_WR_REG_DATA(uint16_t reg, uint16_t data)
{
	LCD_WR_REG(reg);
	LCD_WR_DATA(data);
}
void LCD_Init(uint16_t BkColor)
{
	uint32_t i = 0;
	LCD_GPIO_Config();
	LCD_FSMC_Config();
	LCD_RESET_L;
	LCD_Delay(14400);
	LCD_RESET_H;
	LCD_Delay(14400);
	
 	LCD_WR_REG_DATA(0x0000,0x0001);//打开晶振
  LCD_WR_REG_DATA(0x0003,0xA8A4);//0xA8A4
  LCD_WR_REG_DATA(0x000C,0x0000);
  LCD_WR_REG_DATA(0x000D,0x080C);
  LCD_WR_REG_DATA(0x000E,0x2B00);
  LCD_WR_REG_DATA(0x001E,0x00B0);
  LCD_WR_REG_DATA(0x0001,0x2B3F);//驱动输出控制320*240  0x6B3F
  LCD_WR_REG_DATA(0x0002,0x0600);
  LCD_WR_REG_DATA(0x0010,0x0000);
  LCD_WR_REG_DATA(0x0011,0x6070);//0x4030   //定义数据格式  16位色 
  LCD_WR_REG_DATA(0x0005,0x0000);
  LCD_WR_REG_DATA(0x0006,0x0000);
  LCD_WR_REG_DATA(0x0016,0xEF1C);
  LCD_WR_REG_DATA(0x0017,0x0003);
  LCD_WR_REG_DATA(0x0007,0x0233);//0x0233
  LCD_WR_REG_DATA(0x000B,0x5308);
  LCD_WR_REG_DATA(0x000F,0x0000);//扫描开始地址
  LCD_WR_REG_DATA(0x0041,0x0000);
  LCD_WR_REG_DATA(0x0042,0x0000);
  LCD_WR_REG_DATA(0x0048,0x0000);
  LCD_WR_REG_DATA(0x0049,0x013F);
  LCD_WR_REG_DATA(0x004A,0x0000);
  LCD_WR_REG_DATA(0x004B,0x0000);
  LCD_WR_REG_DATA(0x0044,0xEF00);
  LCD_WR_REG_DATA(0x0045,0x0000);
  LCD_WR_REG_DATA(0x0046,0x013F);
  LCD_WR_REG_DATA(0x0030,0x0707);
  LCD_WR_REG_DATA(0x0031,0x0204);
  LCD_WR_REG_DATA(0x0032,0x0204);
  LCD_WR_REG_DATA(0x0033,0x0502);
  LCD_WR_REG_DATA(0x0034,0x0507);
  LCD_WR_REG_DATA(0x0035,0x0204);
  LCD_WR_REG_DATA(0x0036,0x0204);
  LCD_WR_REG_DATA(0x0037,0x0502);
  LCD_WR_REG_DATA(0x003A,0x0302);
  LCD_WR_REG_DATA(0x003B,0x0302);
  LCD_WR_REG_DATA(0x0023,0x0000);
  LCD_WR_REG_DATA(0x0024,0x0000);
  LCD_WR_REG_DATA(0x0025,0x8000);
  LCD_WR_REG_DATA(0x004f,0);//行首址0
  LCD_WR_REG_DATA(0x004e,0);//列首址0
	LCD_WR_REG(0x0022);
	for(i=0; i<76800; i++)
	{
		LCD_WR_DATA(BkColor);
	}
	LCD_LED_ON;
	
	LCD_Show_Systemname();
	LCD_Char(128, 180, '.', DisplayColor, BkColor);
	LCD_Delay(3600000);
	LCD_Char(144, 180, '.', DisplayColor, BkColor);
	LCD_Delay(3600000);
	LCD_Char(160, 180, '.', DisplayColor, BkColor);
	LCD_Delay(1800000);
	
}
static void Set_Coordinate(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_WR_REG_DATA(0x0044, (x2<<8)+x1);
	LCD_WR_REG_DATA(0x0045, y1);
	LCD_WR_REG_DATA(0x0046, y2);
	LCD_WR_REG_DATA(0x004e, x1);
	LCD_WR_REG_DATA(0x004f, y1);
	LCD_WR_REG(0x0022);
}
static void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t x_length, uint16_t y_length, uint16_t BkColor)
{
	uint32_t i = 0;
	Set_Coordinate(x, y, (x + x_length-1), (y + y_length-1));
	for(i = 0; i < (x_length * y_length); i++)
	{
		LCD_WR_DATA(BkColor);
	}
}
void LCD_Num(uint16_t x, uint16_t y, int32_t num, uint16_t Color, uint16_t BkColor)
{
	int32_t res = 0;
	uint8_t t 	= 0;
	
	if(num > 0)
		res = num;
	else if(num < 0)
	{
		LCD_Char(x, y, '-', Color, BkColor);
		res = 0 - num;
		num = res;
		x = x + 8;
	}
	else if(num == 0)
	{
		LCD_Char(x, y, '0', Color, BkColor);
		return ;
	}
	while(res != 0)
	{
		res = res / 10;
		t++;
	}
	while(num != 0)
	{
		t--;		//先显示低位，再显示高位。ASCII码显示
		LCD_Char((x+(t*8)), y, ((num%10)+'0'), Color, BkColor);
		num = num / 10;
	}
}
void LCD_PointNum(uint16_t x, uint16_t y, int32_t num, uint16_t Color, uint16_t BkColor)
{//不得超过3位小数
	uint32_t L_Value = 0;
	uint8_t t = 0;
	
	LCD_Char(x, y, '.', Color, BkColor);
	x = x + 8;
	if((num > 99999999) || (num < -9999999))
	{
		for(t = 0; t < 3; t++)
			LCD_Char((x + t*8), y, '*', Color, BkColor);
		return ;
	}
	if(num < 0)
	{
		num = 0- num;
		L_Value = num % 1000;
	}
	if(num > 0)
		L_Value = num % 1000;
	
	if(L_Value == 0)
	{	
		LCD_Str_Char(x, y, "0", Color, BkColor);
		return;
	}
	if(L_Value < 10)
	{
		LCD_Str_Char(x, y, "00", Color, BkColor);
		LCD_Num(x + 16, y,(L_Value % 10), Color, BkColor);
		return;
	}
	if(L_Value < 100)
	{
		LCD_Str_Char(x, y, "0", Color, BkColor);
		if((L_Value % 10) != 0)
			LCD_Num(x + 16, y, (L_Value % 10), Color, BkColor);
		L_Value = L_Value / 10;
		LCD_Num(x + 8, y, (L_Value % 10), Color, BkColor);
		return;
	}
	if(L_Value < 1000)
	{
		if((L_Value % 10) != 0)
			LCD_Num(x + 16, y, (L_Value % 10), Color, BkColor);
		L_Value = L_Value / 10;
		if((L_Value % 10) != 0)
			LCD_Num(x + 8, y, (L_Value % 10), Color, BkColor);
		L_Value = L_Value / 10;
		LCD_Num(x, y, (L_Value % 10), Color, BkColor);
		return;
	}
	if(L_Value > 1000)
		return ;
}
void LCD_Num_Right(uint16_t x, uint16_t y, int32_t num, uint16_t Color, uint16_t BkColor)
{//正数不得超过5位，负数不得超过4位，超出部分影响数据显示
	uint8_t t = 5;
	uint32_t H_Value = 0;
	uint8_t value[5] = {'-'};
	uint8_t Zero_Count = 0;
	uint16_t tmp_x = x;
	if((num > 99999999) || (num < -9999999))
	{
		for(t = 0; t < 5; t++)
			LCD_Char((tmp_x + (t*8)), y, '*', Color, BkColor);
		return ;
	}
	if(num > 0)
	{
		H_Value = num / 1000;
		for(t = 0; t < 5; t++)
		{
			value[t] = H_Value % 10;
			H_Value /= 10;
		}
		for(t = 0; t < 5; t++)
		{
			if(value[(4 - t)] == 0)
				Zero_Count++;
			else
				break;
		}
		if(Zero_Count == 5)
		{
			LCD_Char(tmp_x + 32, y, '0', Color, BkColor);
			return;
		}
		for(t = 0; t < Zero_Count; t++)
		{
			LCD_Char(tmp_x, y, ' ', Color, BkColor);
			tmp_x = tmp_x + 8;
		}
		for(t = Zero_Count; t < 5; t++)
		{
			LCD_Num(tmp_x, y, value[(4 - t)], Color, BkColor);
			tmp_x = tmp_x + 8;
		}
	}
	if(num < 0)
	{
		H_Value = 0 - num;
		H_Value = H_Value / 1000;
		for(t = 0; t < 4; t++)
		{
			value[t] = H_Value % 10;
			H_Value /= 10;
		}
		value[4] = '-';
		for(t = 0; t < 4; t++)
		{
			if(value[(3 - t)] == 0)
				Zero_Count++;
			else
				break;
		}
		if(Zero_Count == 4)
		{
			LCD_Char(tmp_x + 24, y, '-', Color, BkColor);
			LCD_Char(tmp_x + 32, y, '0', Color, BkColor);
			return;
		}
		for(t = 0; t < Zero_Count; t++)
		{
			LCD_Char(tmp_x, y, ' ', Color, BkColor);
			tmp_x = tmp_x + 8;
		}
		LCD_Char(tmp_x, y, '-', Color, BkColor);
		tmp_x = tmp_x + 8;
		for(t = Zero_Count; t < 4; t++)
		{
			LCD_Num(tmp_x, y, value[(3 - t)], Color, BkColor);
			tmp_x = tmp_x + 8;
		}
	}
	if(num == 0)
	{
		LCD_Char(tmp_x + 32, y, '0', Color, BkColor);
	}
}
void LCD_Char(uint16_t x, uint16_t y, uint8_t ascii, uint16_t Color, uint16_t BkColor)
{
	uint8_t temp = 0, t = 0, pos = 0;
	if(x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
		return ;
	
	Set_Coordinate(x, y, x+7, y+15);
	
	for(pos = 0; pos < 16; pos++)
	{
		temp = ascii_8x16[((ascii-0x20)*16)+pos];
		
		for(t = 0; t < 8; t++)
		{
			if(temp&0x80)
				LCD_WR_DATA(Color);
			else
				LCD_WR_DATA(BkColor);
			temp = temp << 1;
		}
	}
}
void LCD_Str_Char(uint16_t x, uint16_t y, uint8_t *str, uint16_t Color, uint16_t BkColor)
{
	while(*str != '\0')
	{
		if(x > MAX_CHAR_POSX)
		{
			x = 0;
			y = y + 16;
		}
		if(y > MAX_CHAR_POSY)
		{
			x = 0;
			y = 0;
		}
		LCD_Char(x, y, *str, Color, BkColor);
		str++;
		x = x + 8;
	}
}
void LCD_CH(uint16_t x, uint16_t y, uint8_t *str, uint16_t Color, uint16_t BkColor)
{
	uint8_t i = 0, j = 0;
	uint8_t buffer[32] = {0};
	uint16_t temp = 0;
	
	HZGB15x16(buffer, str);
	//GetGBKCode_from_sd(buffer, str);

	Set_Coordinate(x, y, x+15, y+15);

	for(i = 0; i < 16; i++)
	{
		temp = buffer[i*2];
		temp = (temp<<8);
		temp |= buffer[(i*2)+1];
		for(j = 0; j < 16; j++)
		{
			if(temp&0x8000)
				LCD_WR_DATA(Color);
			else
				LCD_WR_DATA(BkColor);
			temp = temp << 1;
		}
	}
}
void LCD_Str_CH(uint16_t x, uint16_t y, uint8_t *str, uint16_t Color, uint16_t BkColor)
{
	while(*str != '\0')
	{
		if(x > MAX_CH_POSX)
		{
			x = 0;
			y = y + 16;
		}
		if(y > MAX_CH_POSY)
		{
			x = 0;
			y = 0;
		}
		LCD_CH(x, y, str, Color, BkColor);
		str = str + 2;
		x = x + 16;
	}
}
void LCD_Str_CHChar(uint16_t x, uint16_t y, uint8_t *str, uint16_t Color, uint16_t BkColor)
{
	uint16_t tmp_x = 0, tmp_y = 0 ,num = 0;
	tmp_x = x;
	tmp_y = y;
	while(*str != '\0')
	{
		num++;
		if(*str < 125)
		{
			if(tmp_x > MAX_CHAR_POSX)
			{
				tmp_x = 0;
				tmp_y = tmp_y + 16;
			}
			if(tmp_y > MAX_CHAR_POSY)
			{
				tmp_x = 0;
				tmp_y = 0;
			}
			LCD_Char(tmp_x, tmp_y, *str, Color, BkColor);
			str++;
			tmp_x = tmp_x + 8;
		}
		else
		{
			if(*str == 163)
			{
				LCD_Char(tmp_x, tmp_y, ' ', Color, BkColor);
				str = str + 2;
				tmp_x = tmp_x + 8;
			}
			if(tmp_x > MAX_CH_POSX)
			{
				tmp_x = 0;
				tmp_y = tmp_y + 16;
			}
			if(tmp_y > MAX_CH_POSY)
			{
				tmp_x = 0;
				tmp_y = 0;
			}
			LCD_CH(tmp_x, tmp_y, str, Color, BkColor);
			str = str + 2;
			tmp_x = tmp_x + 16;
		}
	}
}
void LCD_ShowDate(Date_TypeDef YTD, uint16_t Color, uint16_t BkColor)
{
	uint16_t x = Time_POSX, y = Time_POSY;
	LCD_Num(x, y, YTD.Year, Color, BkColor);
	inc = 32;	//4*8
	LCD_CH(x + inc, y, "年", Color, BkColor);
	inc += 16;
	//判断数字的位数
	if(YTD.Month < 10)
	{
		LCD_Rectangle(x + inc, y, 16, 8, BkColor);
		LCD_Num(x + inc, y, YTD.Month, Color, BkColor);
		inc += 8;
	}
	else
	{
		LCD_Rectangle(x + inc, y, 16, 16, BkColor);
		LCD_Num(x + inc, y, YTD.Month, Color, BkColor);
		inc += 16;
	}
	
	LCD_CH(x + inc, y, "月", Color, BkColor);
	inc += 16;
	
	if(YTD.Date < 10)
	{
		LCD_Rectangle(x + inc, y, 16, 8, BkColor);
		LCD_Num(x + inc, y, YTD.Date, Color, BkColor);
		inc += 8;
	}
	else
	{
		LCD_Rectangle(x + inc, y, 16, 16, BkColor);
		LCD_Num(x + inc, y, YTD.Date, Color, BkColor);
		inc += 16;
	}

	LCD_CH(x + inc, y, "日", Color, BkColor);
	inc += 16;
}
void LCD_ShowTime(Time_TypeDef Time, uint16_t Color, uint16_t BkColor)
{
	uint16_t x = Time_POSX, y = Time_POSY;
	uint16_t tmp_inc = inc;
	if(Time.Hour < 10)
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 8, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Hour, Color, BkColor);
		tmp_inc += 8;
	}
	else
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 16, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Hour, Color, BkColor);
		tmp_inc += 16;
	}

	LCD_CH(x + tmp_inc, y, "时", Color, BkColor);
	tmp_inc += 16;
	
	if(Time.Minute < 10)
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 8, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Minute, Color, BkColor);
		tmp_inc += 8;
	}
	else
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 16, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Minute, Color, BkColor);
		tmp_inc += 16;
	}

	LCD_CH(x + tmp_inc, y, "分", Color, BkColor);
	tmp_inc += 16;
	
	if(Time.Second < 10)
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 8, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Second, Color, BkColor);	
		tmp_inc += 8;
	}
	else
	{
		LCD_Rectangle(x + tmp_inc, y, 16, 16, BkColor);
		LCD_Num(x + tmp_inc, y, Time.Second, Color, BkColor);
		tmp_inc += 16;
	}
	
	LCD_CH(x + tmp_inc, y, "秒", Color, BkColor);
	tmp_inc += 16;
	LCD_Rectangle(x + tmp_inc, y, (208-tmp_inc), 16, BkColor);
}
static void LCD_ShowCelsius(uint16_t x, uint16_t y, uint16_t Color, uint16_t BkColor)
{
	uint8_t temp = 0, t = 0, pos = 0;
	if(x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
		return ;
	
	LCD_Rectangle(x, y, 40, 16, BkColor);
	Set_Coordinate(x, y, x+15, y+15);
	
	for(pos = 0; pos < 32; pos++)
	{
		temp = Celsius[pos];
		
		for(t = 0; t < 8; t++)
		{
			if(temp&0x80)
				LCD_WR_DATA(Color);
			else
				LCD_WR_DATA(BkColor);
			temp = temp << 1;
		}
	}
}
void LCD_Show_BkColor(uint16_t y1, uint16_t y2, uint16_t BkColor)
{
	uint16_t y_length = 0;
	y_length = y2 - y1 + 1;
	LCD_Rectangle(0, y1, 240, y_length, BkColor);
}
void LCD_Show_Start(uint16_t Color, uint16_t BkColor)
{
	uint8_t i	=	0;
	//uint8_t tmp_NO_Buffer[] = "0000-00-0000";
	//uint8_t tmp_CH_Buffer[] = "00000000000000000000000000000000";

	LCD_Show_Systemname();
	LCD_Str_CH(72, 180, "初始化", Color, BkColor);
	
	for(i=0; i<3; i++)
	{
		LCD_Rectangle(128, 180, 48, 16, BkColor);
		if(i == 0)//得到系统当前时间
		{
			System_Date = GetRTC_Date();
			System_Time = GetRTC_Time();
//			Update_Filename();
		}
		LCD_Char(128, 180, '.', Color, BkColor);
		LCD_Delay(3600000);
		LCD_Char(144, 180, '.', Color, BkColor);
		LCD_Delay(3600000);
		LCD_Char(160, 180, '.', Color, BkColor);
		LCD_Delay(1800000);
	}
}
void LCD_Show_Main_Screen(uint16_t Color, uint16_t BkColor)
{
	uint8_t ch = 0;
	uint8_t tmp_NO_Buffer[] = "NO:0000-00-0000";
	LCD_Rectangle(0, 0, 240, 320, BkColor);
	LCD_ShowDate(System_Date, Color, BkColor);
	LCD_ShowTime(System_Time, Color, BkColor);
	LCD_Char(Time_POSX + 217, Time_POSY, 'G', Color, BkColor);
	LCD_Rectangle(0, H_Line_POSY, 240, 2, Color);
	for(ch = 0; ch < 16; ch++)
	{
		LCD_Show_Channel_Info(ch, Color, BkColor);
	}
	LCD_Rectangle(0, L_Line_POSY, 240, 2, Color);
	
	strcopy(tmp_NO_Buffer, 0, NO_Buffer, str_length(NO_Buffer));
	LCD_Str_Char(NO_POSX, NO_POSY, tmp_NO_Buffer, Color, BkColor);
}
void LCD_Show_Detail_Data()
{
	
}
void LCD_Show_Channel_Info(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	LCD_ChannelNum(CHX, CH_POSX, CH_POSY[CHX], Color, BkColor);
	LCD_Char(CH_POSX+16, CH_POSY[CHX], ':', Color, BkColor);
	LCD_ChannelSensorCH(CHX, Color, BkColor);
	LCD_ChannelPara(CHX, Color, BkColor);
	LCD_ChannelUnit(CHX, CH_Unit_POSX, CH_POSY[CHX], Color, BkColor);
}
static void LCD_ChannelNum(uint8_t CHX, uint16_t x, uint16_t y, uint16_t Color, uint16_t BkColor)
{
	uint8_t CHX_Char_H = ((((CHX+1)/10)%10)+'0');
	uint8_t CHX_Char_L = (((CHX+1)%10)+'0');
	if(CHX_Char_H == '0')
		LCD_Char(x, y, ' ', Color, BkColor);
	else
		LCD_Char(x, y, CHX_Char_H, Color, BkColor);
	LCD_Char(x+8, y, CHX_Char_L, Color, BkColor);
}
void LCD_ChannelSensorCH(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	switch(CH_Sensor_Sel[CHX])
	{
		case 'L'://气压
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "气    压", Color, BkColor);
			break;
		case '6'://风速
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "风    速", Color, BkColor);
			break;
		case '7'://风向
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "风    向", Color, BkColor);
			break;
		case '4'://雨量
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "雨    量", Color, BkColor);
			break;
		case '9'://辐射
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "辐    射", Color, BkColor);
			break;
		case 'M'://湿度
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "湿    度", Color, BkColor);
			break;
		case '5'://气温
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "温    度", Color, BkColor);
			break;
		case 'G'://水温
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "水    温", Color, BkColor);
			break;
		case 'F'://溶解氧
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "溶 解 氧", Color, BkColor);
			break;
		case 'J'://余氯
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "余    氯", Color, BkColor);
			break;
		case 'E'://PH
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "酸 碱 度", Color, BkColor);
			break;
		case '3'://土壤墒情
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "土壤墒情", Color, BkColor);
			break;
		case '2'://流量
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "流    量", Color, BkColor);
			break;
		case '1'://水位
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "水    位", Color, BkColor);
			break;
		case 'I'://浊度
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "浊    度", Color, BkColor);
			break;
		case 'H'://电导率
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "电 导 率", Color, BkColor);
			break;
		default:
			LCD_Str_CHChar(CH_Sensor_CHPOSX, CH_POSY[CHX], "传 感 器", Color, BkColor);
			break;
	}
}
void LCD_ChannelPara(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	switch(CH_Sensor_Sel[CHX])
	{
// 		case 'L'://气压
// 		case '7'://风向
// 		case 'M'://湿度
// 		case 'J'://余氯
// 		case '3'://土壤墒情
// 		case '2'://流量
// 		break;
		case '6'://风速
			Sub_LCD_Para(CHX, 3, 1, Color, BkColor);
			break;
		case '4'://雨量
			Sub_LCD_Para(CHX, 2, 1, Color, BkColor);
			break;
		case '9'://辐射
			Sub_LCD_Para(CHX, 4, 0, Color, BkColor);
			break;
		case '5'://气温
			Sub_LCD_Para(CHX, 2, 0, Color, BkColor);
			break;
		case 'G'://水温
			Sub_LCD_Para(CHX, 2, 0, Color, BkColor);
			break;
		case 'F'://溶解氧
			Sub_LCD_Para(CHX, 2, 3, Color, BkColor);
			break;
		case 'E'://PH
			Sub_LCD_Para(CHX, 2, 2, Color, BkColor);
			break;
		case '1'://水位
			Sub_LCD_Para(CHX, 2, 3, Color, BkColor);
			break;
		case 'I'://浊度
			Sub_LCD_Para(CHX, 4, 0, Color, BkColor);
			break;
		case 'H'://电导率
			Sub_LCD_Para(CHX, 3, 2, Color, BkColor);
			break;
		default:
			Sub_LCD_Para(CHX, 0, 0, Color, BkColor);
			break;
	}
}

void LCD_ChannelUnit(uint8_t CHX, uint16_t x, uint16_t y, uint16_t Color, uint16_t BkColor)
{
	switch(CH_Sensor_Sel[CHX])
	{
		case 'L'://气压
			LCD_Str_Char(x, y, " Pa  ", Color, BkColor);
			break;
		case '6'://风速
			LCD_Str_Char(x, y, " m/s ", Color, BkColor);
			break;
		case '7'://风向
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case '4'://雨量
			LCD_Str_Char(x, y, " mm  ", Color, BkColor);
			break;
		case '9'://辐射
			LCD_Str_Char(x, y, " W/m2", Color, BkColor);
			break;
		case 'M'://湿度
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case '5'://气温
			LCD_ShowCelsius(x, y, Color, BkColor);
			break;
		case 'G'://水温
			LCD_ShowCelsius(x, y, Color, BkColor);
			break;
		case 'F'://溶解氧
			LCD_Str_Char(x, y, " mg/L", Color, BkColor);
			break;
		case 'J'://余氯
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case 'E'://PH
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case '3'://土壤墒情
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case '2'://流量
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
		case '1'://水位
			LCD_Str_Char(x, y, " m   ", Color, BkColor);
			break;
		case 'I'://浊度
			LCD_Str_Char(x, y, " NTU ", Color, BkColor);
			break;
		case 'H'://电导率
			LCD_Str_Char(x, y, " uS  ", Color, BkColor);
			break;
		default:
			LCD_Str_Char(x, y, "     ", Color, BkColor);
			break;
	}
}
static void Sub_LCD_Para(uint8_t CHX, uint8_t Inte_Num, uint8_t Deci_Num, uint16_t Color, uint16_t BkColor)
{
	uint8_t num = 0;
	uint8_t Zero_Count = 0;//'0'的个数
	uint8_t Minus_Sign_flag = 0;//负号标志
	uint8_t Pos = (5 - Inte_Num);
	uint8_t XPos = (CH_Data_POSX + (Pos*8));
	uint8_t Para[] = "12345.678";
	
	CH_Phy_Value_IntToAsc(CHX, Para);
	
	LCD_Rectangle(CH_Data_POSX, CH_POSY[CHX], 72, 16, BkColor);
	
	if(CH_Sampling[CHX] == '0')
	{
		LCD_Str_Char(CH_Data_POSX, CH_POSY[CHX], "*****.***", Color, BkColor);
		return;
	}

	for(num = 0; num < Inte_Num; num++)
	{
		if((Zero_Count == num)&&(Para[Pos] == '0'))
		{
			Zero_Count++;
			if(Zero_Count == Inte_Num)
			{
				LCD_Char(XPos, CH_POSY[CHX], '0', Color, BkColor);
				if((Minus_Sign_flag == 0)&&(Para[0] == '-'))
				{
					LCD_Char(XPos-8, CH_POSY[CHX], '-', Color, BkColor);
					Minus_Sign_flag = 1;
				}
			}
		}
		else
		{
			if((Minus_Sign_flag == 0)&&(Para[0] == '-'))
			{
				LCD_Char(XPos-8, CH_POSY[CHX], '-', Color, BkColor);
				Minus_Sign_flag = 1;
			}
			LCD_Char(XPos, CH_POSY[CHX], Para[Pos], Color, BkColor);
		}
		XPos += 8;
		++Pos;
	}

	if(Deci_Num != 0)
		LCD_Char(XPos, CH_POSY[CHX], Para[5], Color, BkColor);//'.'
	
	Zero_Count = 0;
	Pos = (5+Deci_Num);
	XPos += (8*Deci_Num);
	
	for(num = 0; num < Deci_Num; num++)
	{
		if((Zero_Count == num)&&(Para[Pos] == '0'))
		{
			Zero_Count++;
			if(Zero_Count == Deci_Num)
				LCD_Char(XPos, CH_POSY[CHX], '0', Color, BkColor);
		}
		else
			LCD_Char(XPos, CH_POSY[CHX], Para[Pos], Color, BkColor);
		XPos -= 8;
		--Pos;
	}
}

//******************基本参数显示*****************************/
void LCD_Show_Config_Info(uint16_t Color, uint16_t BkColor)
{
	uint8_t tmp_NO_Buffer[] = "NO:0000-00-0000";	
	LCD_Rectangle(0, 0, 240, 320, BkColor);

	LCD_Rectangle(0, 0, 240, 20, BLUE);	
	LCD_Str_CHChar(96,2, "基本参数", Color, BLUE);

	LCD_Str_CHChar(0,42, "设备编号:", Color, BkColor);	
	strcopy(tmp_NO_Buffer, 0, NO_Buffer, str_length(NO_Buffer));
	LCD_Str_Char(80, 42, tmp_NO_Buffer, Color, BkColor);

	LCD_Str_CHChar(0, 62, "软件版本:", Color, BkColor);	
	LCD_Str_Char(80, 62, SoftWareVersion, Color, BkColor);	
}
//***********************************************************************************//

//*******************************通道参数显示****************************************//
void LCD_Show_Detail_Channel_Info(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	LCD_Rectangle(0, 0, 240, 320, BkColor);

	LCD_Rectangle(0, S2_title0_Y-2, 240, 20, BLUE);	
	LCD_Str_CHChar(80,2, "采集通道参数", Color, BLUE);	
	
	LCD_Rectangle(0, S2_title1_Y-2, 240, 20, xx);
	LCD_Str_CH(S2_title_X, S2_title1_Y, "配置参数", Color, xx);
	LCD_Str_CHChar(S2_item_X, S2_Y1, "1:通道号:", Color, BkColor);					LCD_ChannelNum(CHX, S2_data_X1, S2_Y1, Color, BkColor);
	LCD_Str_CHChar(S2_item_X, S2_Y2, "2:通道类型:", Color, BkColor);				LCD_Detail_ChannelType(CHX, S2_data_X2, S2_Y2, Color, BkColor);
	LCD_Str_CHChar(S2_item_X, S2_Y3, "3:传感器:", Color, BkColor);					LCD_Detail_Sensor(CHX, Color, BkColor);
	LCD_Str_CHChar(S2_item_X, S2_Y4, "4:电压校准参数:", Color, BkColor);	LCD_Detail_VoltageCalibration(CHX, Color, BkColor);
	LCD_Str_CHChar(S2_item_X, S2_Y5, "5:转换关系:", Color, BkColor);			LCD_Detail_ConversionRelation(CHX, Color, BkColor);
	LCD_Rectangle(0, S2_title2_Y-2, 240, 20, xx);
	LCD_Str_CH(S2_title_X, S2_title2_Y, "实时数据", Color, xx);
	LCD_Str_CHChar(S2_item_X, S2_Y6, "1:电信号:", Color, BkColor);					LCD_Detail_RT_ElectricSignal(CHX, Color, BkColor);
	LCD_Str_CHChar(S2_item_X, S2_Y7, "2:传感器:", Color, BkColor);					LCD_Detail_RT_PhysicalData(CHX, Color, BkColor);
	LCD_ChannelUnit(CHX, S2_data_X7+72, S2_Y7, Color, BkColor);
	LCD_Detail_ChannelType(CHX, S2_data_X6+64, S2_Y6, Color, BkColor);
	
	LCD_Str_CHChar(S2_item_X, S2_Y8, "3:外部电源:     V", Color, BkColor);
	
	FloatChar(4,2, Local_Battery_Volt,0);
	LCD_Str_Char(96, S2_Y8, DisplayBuf, Color, BkColor);	

}
//***********************************************************************************//

//****************************************通道类型*************************************//
void LCD_Detail_ChannelType(uint8_t CHX, uint16_t x, uint16_t y, uint16_t Color, uint16_t BkColor)
{
	switch(CH_Type[CHX])
	{
		case 0:
			LCD_Str_CHChar(x, y, " --", Color, BkColor);
			break;
		case 1:
			LCD_Str_CHChar(x, y, " uV", Color, BkColor);
			break;
		case 2:
			LCD_Str_CHChar(x, y, " mV", Color, BkColor);
		break;
		case 3:
			LCD_Str_CHChar(x, y, " mO", Color, BkColor);
		break;
		case 4:
			LCD_Str_CHChar(x, y, " uA", Color, BkColor);
		break;
		case 5:
			LCD_Str_CHChar(x, y, " SP", Color, BkColor);
			break;
		case 6:
			LCD_Str_CHChar(x, y, " MP", Color, BkColor);
		break;
		case 7:
			LCD_Str_CHChar(x, y, " OM", Color, BkColor);
			break;
		default:
			LCD_Str_CHChar(x, y, " **", Color, BkColor);
			break;
	}
}
//***********************************************************************************//

//*******************************传感器类型******************************************//
void LCD_Detail_Sensor(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	switch(CH_Sensor_Sel[CHX])
	{
		case 'L'://气压
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "气压    ", Color, BkColor);
			break;
		case '6'://风速
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "风速    ", Color, BkColor);
			break;
		case '7'://风向
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "风向    ", Color, BkColor);
			break;
		case '4'://雨量
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "雨量    ", Color, BkColor);
			break;
		case '9'://辐射
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "辐射    ", Color, BkColor);
			break;
		case 'M'://湿度
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "湿度    ", Color, BkColor);
			break;
		case '5'://气温
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "温度    ", Color, BkColor);
			break;
		case 'G'://水温
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "水温    ", Color, BkColor);
			break;
		case 'F'://溶解氧
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "溶解氧  ", Color, BkColor);
			break;
		case 'J'://余氯
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "余氯    ", Color, BkColor);
			break;
		case 'E'://PH
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "酸碱度  ", Color, BkColor);
			break;
		case '3'://土壤墒情
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "土壤墒情", Color, BkColor);
			break;
		case '2'://流量
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "流量    ", Color, BkColor);
			break;
		case '1'://水位
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "水位    ", Color, BkColor);
			break;
		case 'I'://浊度
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "浊度    ", Color, BkColor);
			break;
		case 'H'://电导率
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "电导率  ", Color, BkColor);
			break;
		default:
			LCD_Str_CHChar(S2_data_X3, S2_Y3, "传感器  ", Color, BkColor);
			break;
	}
}
//***********************************************************************************//

//*******************************电压校准******************************************//
void LCD_Detail_VoltageCalibration(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	FloatChar(7,2,CH_Volt_slope[CHX], 1);
	LCD_Str_CHChar(S2_data_X4, S2_Y4, "K:", Color, BkColor);	
	LCD_Str_CHChar(S2_data_X4+16, S2_Y4, DisplayBuf, Color, BkColor);
	FloatChar(7,0,CH_Volt_zero[CHX], 1);
	LCD_Str_CHChar(S2_data_X4, S2_Y4+16, "B:", Color, BkColor);	
	LCD_Str_CHChar(S2_data_X4+16, S2_Y4+16, DisplayBuf, Color, BkColor);
}

//*******************************电信号与物理量转换关系***************************//
void LCD_Detail_ConversionRelation(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	FloatChar(7,2,Para_J[CHX], 1);
	LCD_Str_CHChar(S2_data_X5, S2_Y5, "J:", Color, BkColor);
	LCD_Str_CHChar(S2_data_X5+16, S2_Y5, DisplayBuf, Color, BkColor);
	FloatChar(7,2,Para_K[CHX], 1);
	LCD_Str_CHChar(S2_data_X5, S2_Y5+16, "K:", Color, BkColor);
	LCD_Str_CHChar(S2_data_X5+16, S2_Y5+16, DisplayBuf, Color, BkColor);
	FloatChar(7,2,Para_B[CHX], 1);
	LCD_Str_CHChar(S2_data_X5, S2_Y5+32, "B:", Color, BkColor);
	LCD_Str_CHChar(S2_data_X5+16, S2_Y5+32, DisplayBuf, Color, BkColor);
	

}
void LCD_Detail_RT_ElectricSignal(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	uint8_t ElecASC[8], num;
	int32_t Sample_value = CH_Sample[CHX];
	if(Sample_value < 0)
	{
		ElecASC[0] = '-';
		Sample_value = 0 - Sample_value;
	}
	else	ElecASC[0] = '+';
	for(num = 0; num < 7; num++)
	{
		ElecASC[7-num] = ((Sample_value%10)+'0');Sample_value = Sample_value/10;
	}
	for(num = 0; num < 8; num++)LCD_Char((S2_data_X6+num*8), S2_Y6, ElecASC[num], Color, BkColor);
}
void LCD_Detail_RT_PhysicalData(uint8_t CHX, uint16_t Color, uint16_t BkColor)
{
	uint8_t PhyASC[9], num;
	CH_Phy_Value_IntToAsc(CHX, PhyASC);
	for(num = 0; num < 9; num++)LCD_Char((S2_data_X7+num*8), S2_Y7, PhyASC[num], Color, BkColor);
}
void LCD_Update_Show(uint8_t PageNum, uint16_t Color, uint16_t BkColor)
{
	uint8_t CHX = PageNum - 2;
	if((PageNum >= 2)&&(PageNum <= 17))
	{
		if(Pre_Page != PageNum)
		{
			Pre_Page = PageNum;
			LCD_ChannelNum(CHX, S2_data_X1, S2_Y1, Color, BkColor);
			LCD_Detail_ChannelType(CHX, S2_data_X2, S2_Y2, Color, BkColor);
			LCD_Detail_Sensor(CHX, Color, BkColor);
			LCD_Detail_VoltageCalibration(CHX, Color, BkColor);
			LCD_Detail_ConversionRelation(CHX, Color, BkColor);
			LCD_ChannelUnit(CHX, S2_data_X7+72, S2_Y7, Color, BkColor);
			LCD_Detail_ChannelType(CHX, S2_data_X6+64, S2_Y6, Color, BkColor);
		}
		LCD_Detail_RT_ElectricSignal(CHX, Color, BkColor);
		LCD_Detail_RT_PhysicalData(CHX, Color, BkColor);
	}
}
static void LCD_Show32x32Char(uint16_t x, uint16_t y, uint8_t pos, uint16_t Color, uint16_t BkColor)
{
	uint8_t i, j;
	uint32_t temp;
	Set_Coordinate(x, y, x+31, y+31);
	for(i = 0; i < 32; i++)
	{
		temp = System_name_char[(i*4+(pos*128))];
		temp = (temp<<8);
		temp |= System_name_char[((i*4)+1+(pos*128))];
		temp = (temp<<8);
		temp |= System_name_char[((i*4)+2+(pos*128))];
		temp = (temp<<8);
		temp |= System_name_char[((i*4)+3+(pos*128))];
		for(j = 0; j < 32; j++)
		{
			if(temp&0x80000000)
				LCD_WR_DATA(WHITE);
			else
				LCD_WR_DATA(BLACK);
			temp = temp << 1;
		}
	}
}
void LCD_Show_Systemname(void)
{
	uint16_t x1 = 72, x2 = 24, y = 96;
	LCD_Show32x32Char(x1,y,0,WHITE,BLACK);//多
	LCD_Show32x32Char(x1+32,y,1,WHITE,BLACK);//功
	LCD_Show32x32Char(x1+64,y,2,WHITE,BLACK);//能
	LCD_Show32x32Char(x2,y+32,3,WHITE,BLACK);//数
	LCD_Show32x32Char(x2+32,y+32,4,WHITE,BLACK);//据
	LCD_Show32x32Char(x2+64,y+32,5,WHITE,BLACK);//采
	LCD_Show32x32Char(x2+96,y+32,6,WHITE,BLACK);//集
	LCD_Show32x32Char(x2+128,y+32,7,WHITE,BLACK);//系
	LCD_Show32x32Char(x2+160,y+32,8,WHITE,BLACK);//统
}




