#include "debug.h"
#include "usart.h"
#include "string.h"
void SendDebug(char val)
{
	char str[10] = {0};
  sprintf(str,"%c%c%c%c%c",0x03,0xFC,val,0xFC,0x03);
	Send_UART4((uint8_t*)str,strlen(str));
}

void SendDebug2(char val1,char val2)
{
	char str[10] = {0};
  sprintf(str,"%c%c%c%c%c%c",0x03,0xFC,val1,val2,0xFC,0x03);
	Send_UART4((uint8_t*)str,strlen(str));
}
void SendDebug3(char val1,char val2,char val3)
{
	char str[10] = {0};
  sprintf(str,"%c%c%c%c%c%c%c",0x03,0xFC,val1,val2,val3,0xFC,0x03);
	Send_UART4((uint8_t*)str,strlen(str));
}
void SendDebugInt(int val)
{
	char str[10] = {0};
	char th = (val&0xff00)>>8;
	char tl = (val&0x00ff);
  sprintf(str,"%c%c%c%c%c%c",0x03,0xFC,th,tl,0xFC,0x03);
	Send_UART4((uint8_t*)str,strlen(str));
}

void SendDebugInt2(int val1,int val2)
{
	char str[20] = {0};
	char th1 = (val1&0xff00)>>8;
	char tl1 = (val1&0x00ff);
	char th2 = (val2&0xff00)>>8;
	char tl2 = (val2&0x00ff);
  sprintf(str,"%c%c%c%c%c%c%c%c",0x03,0xFC,th1,tl1,th2,tl2,0xFC,0x03);
	Send_UART4((uint8_t*)str,strlen(str));
}

