#include <stdio.h>
#include "cam.h"
#include "usart.h"
#include "string.h"

void SendChars(char* s, int len)
{
	Send_UART1((uint8_t*)s,len);
}

void CamInit()
{
    CamReset();
    CamClearPic();

}

void CamReset(void)
{
    char aReset[4] = {0x56,0x00,0x26,00};
    SendChars(aReset,4);
}

void CamClearPic(void)
{
    char aClear[5] = {0x56,0x00,0x36,0x01,0x03};
    SendChars(aClear,5);
}

void CamTakeOnePic(void)
{
    char aTake[5]={0x56,0x00,0x36,0x01,0x00};
    SendChars(aTake,5);
}

void CamGetPicSize(void)
{
    char aGet[5]={0x56,0x00,0x34,0x01,0x00};
    SendChars(aGet,5);
}

void CamReadPicBySize(int addr, int len,int total)
{
    char aInstruct[16]={0x56,0x00,0x32,0x0C,0x00,0x0A,0x00,0x00,'X','X',0x00,0x00,'Y','Y',0x00,0xFF};
	if(addr+len > total)
	{
		len = total - addr;
	}
    aInstruct[8] = (addr >> 8) & 0xff;
    aInstruct[9] = addr & 0x00ff;
    aInstruct[12] = (len >> 8) & 0xff;
    aInstruct[13] = len & 0x00ff;
    SendChars(aInstruct,16);

}

int CamCheckout(char* data,int len)
{	
	return 1;
}


void GenerateData(char* recv,int recv_len,int address,char* send,int* send_len)
{
	int i = 0;
	send[0] = 'S';
	send[1] = 'T';
	send[2] = ':';
	send[3] = (recv_len>>8)&0xff;
	send[4] = recv_len&0xff;
	send[5] = (address>>8)&0xff;
	send[6] = address & 0xff;
	for(i=0;i<recv_len;i++)
		send[i+7] = recv[i];
	*send_len = i+7;

}

/*
void Send_UART5(uint8_t *pos,uint8_t CharLength)
{
	unsigned char temp;
   
	for(temp=0;temp<CharLength;temp++)
	{
		USART_SendData(UART5, *pos);		
		pos++;
		while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );		 				
	}    
*/
void SendToSocket(char* send,int send_len)
{
	Send_UART3((uint8_t*)send,send_len);
}
