#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"

#define WIDTHBYTES(bits) (((bits)+31)/32*4)		//����24λ���ɫ ÿһ�е����ؿ�ȱ���ʱ4�ı���  ����0����

//λͼ�ļ�ͷ��Ϣ�ṹ����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
typedef struct tagBITMAPFILEHEADER 
{
  uint32_t bfSize; 															//�ļ���С																				4
  uint16_t bfReserved1; 													//�����֣�������		 															2
  uint16_t bfReserved2; 													//�����֣�ͬ��			 															2
  uint32_t bfOffBits; 														//ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��	4
}BITMAPFILEHEADER,tagBITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    uint32_t biSize; 														//ָ���˽ṹ��ĳ��ȣ�Ϊ40		 												4
    int32_t biWidth; 														//λͼ��											 												4
    int32_t biHeight; 														//λͼ��											 												4
    uint16_t biPlanes; 														//ƽ������Ϊ1								 													2
    uint16_t biBitCount; 													//������ɫλ����������1��2��4��8��16��24�µĿ�����32	2
    uint32_t biCompression; 											//ѹ����ʽ��������0��1��2������0��ʾ��ѹ��						4
    uint32_t biSizeImage; 												//ʵ��λͼ����ռ�õ��ֽ���														4
    int32_t biXPelsPerMeter; 										//X����ֱ���																					4
    int32_t biYPelsPerMeter; 										//Y����ֱ���																					4
    uint32_t biClrUsed; 													//ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)			4
    uint32_t biClrImportant; 										//��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��				4
} BITMAPINFOHEADER,tagBITMAPINFOHEADER;


typedef struct tagRGBQUAD 
{
    uint8_t rgbBlue; 													//����ɫ����ɫ����
    uint8_t rgbGreen; 													//����ɫ����ɫ����
    uint8_t rgbRed; 														//����ɫ�ĺ�ɫ����
    uint8_t rgbReserved;											 	//����ֵ
} RGBQUAD,tagRGBQUAD;


typedef struct RGB_PIXEL
{      //���ص���������
    unsigned char   rgbBlue;
    unsigned char   rgbGreen;
    unsigned char   rgbRed;
}RGB_PIXEL;


#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//����8λ R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//����8λ G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//����8λ B
#pragma diag_suppress 870 	//ʹ������֧�ֶ��ֽ��ַ�,�������invalid multibyte character sequence���� 



void Lcd_show_bmp(unsigned short int x, unsigned short int y,unsigned char *pic_name);


