#include "Sd_bmp.h"
#include "stm32f10x.h"
#include "ff.h"


#define RGB24TORGB16(R,G,B) ((unsigned short int)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))
#define Set_Scan_Direction_for_bmp()  do{LCD_WR_REG(0x36); LCD_WR_Data(0x28);}while(0)  




void bmp_lcd(u16 x, u16 y, u16 width, u16 height)
{
	 Set_Scan_Direction_for_bmp();			/*ɨ�跽������Ϊ  ����--�����½�(���)�����Ͻ�(�յ�)---��ΪbmpͼƬ���ݴ����ֱ�����õ�Ե��*/
	 LCD_open_windows(x,y,width,height);
	 Lcd_data_start();
}

/*�ָ�LCD��ͨ����*/
void bmp_lcd_reset(void)
{
  LCD_ILI9341_CMD(0x36); 
	LCD_ILI9341_Parameter(0x48);	//���� 
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xEF);	

	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x01);
	LCD_ILI9341_Parameter(0x3F);
}



BYTE pColorData[960];
tagRGBQUAD dataOfBmp[17*19];
FATFS bmpfs[2]; 
FIL bmpfsrc, bmpfdst; 
FRESULT bmpres;



 /******************************************************
 * ��������Lcd_show_bmp
 * ����  ��LCD��ʾRGB888λͼͼƬ
 * ����  : x					--��ʾ������(0-319)
           y					--��ʾ������(0-239)   
 *				 pic_name		--ͼƬ����
 * ���  ����
 * ����  ��Lcd_show_bmp(0, 0,"/test.bmp");
 * ע��  ��ͼƬΪ24Ϊ���ɫλͼͼƬ
 					 ͼƬ��Ȳ��ܳ���320
					 ͼƬ��LCD�ϵ�ճ����ΧΪ:����:  [x,x+ͼ��߶�]   ���� [Y��Y+ͼ����]
					 ��ͼƬΪ320*240ʱ--����X����0  y����0
 *********************************************************/
void Lcd_show_bmp(unsigned short int x, unsigned short int y,unsigned char *pic_name)
{
    int i, j, k;
    int width, height, l_width;
		  
    BYTE red,green,blue;
    BITMAPFILEHEADER bitHead;
    BITMAPINFOHEADER bitInfoHead;
    WORD fileType;

    unsigned int read_num;
    unsigned char tmp_name[20];
    sprintf((char*)tmp_name,"0:%s",pic_name);
    f_mount(0, &bmpfs[0]);

	BMP_DEBUG_PRINTF("file mount ok \r\n");
    
    bmpres = f_open( &bmpfsrc , (char *)tmp_name, FA_OPEN_EXISTING | FA_READ);
    Set_direction(0);

    if(bmpres == FR_OK)
    {
        BMP_DEBUG_PRINTF("Open file success\r\n");
        
        //��ȡλͼ�ļ�ͷ��Ϣ        
        f_read(&bmpfsrc,&fileType,sizeof(WORD),&read_num);     
        
        if(fileType != 0x4d42)
        {
            BMP_DEBUG_PRINTF("file is not .bmp file!\r\n");
            return;
        }
        else
        {
            BMP_DEBUG_PRINTF("Ok this is .bmp file\r\n");	
        }        
        
        f_read(&bmpfsrc,&bitHead,sizeof(tagBITMAPFILEHEADER),&read_num);    
        
        showBmpHead(&bitHead);
        BMP_DEBUG_PRINTF("\r\n");
        
        //��ȡλͼ��Ϣͷ��Ϣ
        f_read(&bmpfsrc,&bitInfoHead,sizeof(BITMAPINFOHEADER),&read_num);        
        showBmpInforHead(&bitInfoHead);
        BMP_DEBUG_PRINTF("\r\n");
    }    
    else
    {
        BMP_DEBUG_PRINTF("file open fail!\r\n");
        return;
    }    
    
    width = bitInfoHead.biWidth;
    height = bitInfoHead.biHeight;
    
    l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);		//����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���	    
    
    if(l_width>960)
    {
        BMP_DEBUG_PRINTF("\nSORRY, PIC IS TOO BIG (<=320)\n");
        return;
    }
    
    if(bitInfoHead.biBitCount>=24)
    {

        bmp_lcd(x,240-y-height,width, height);																	//LCD�����������

        for(i=0;i<height+1; i++)
        {	
            
            for(j=0; j<l_width; j++)	 													//��һ������ȫ������
            {
                
                f_read(&bmpfsrc,pColorData+j,1,&read_num);
            }            
            
            for(j=0;j<width;j++) 																//һ����Ч��Ϣ
            {
                k = j*3;																				//һ���е�K�����ص����
                red = pColorData[k+2];
                green = pColorData[k+1];
                blue = 	pColorData[k];
                LCD_WR_Data(RGB24TORGB16(red,green,blue));		//д��LCD-GRAM
            }            
        }
        bmp_lcd_reset();		 																							//lcdɨ�跽��ԭ	        
    }    
    else 
    {        
        BMP_DEBUG_PRINTF("SORRY, THIS PIC IS NOT A 24BITS REAL COLOR");
        return ;
    }
    
    f_close(&bmpfsrc);    
}


