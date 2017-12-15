#include "Sd_bmp.h"
#include "stm32f10x.h"
#include "ff.h"


#define RGB24TORGB16(R,G,B) ((unsigned short int)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))
#define Set_Scan_Direction_for_bmp()  do{LCD_WR_REG(0x36); LCD_WR_Data(0x28);}while(0)  




void bmp_lcd(u16 x, u16 y, u16 width, u16 height)
{
	 Set_Scan_Direction_for_bmp();			/*扫描方向设置为  横屏--从左下角(起点)到右上角(终点)---因为bmp图片数据存放竖直方向倒置的缘故*/
	 LCD_open_windows(x,y,width,height);
	 Lcd_data_start();
}

/*恢复LCD普通设置*/
void bmp_lcd_reset(void)
{
  LCD_ILI9341_CMD(0x36); 
	LCD_ILI9341_Parameter(0x48);	//竖屏 
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
 * 函数名：Lcd_show_bmp
 * 描述  ：LCD显示RGB888位图图片
 * 输入  : x					--显示横坐标(0-319)
           y					--显示纵坐标(0-239)   
 *				 pic_name		--图片名称
 * 输出  ：无
 * 举例  ：Lcd_show_bmp(0, 0,"/test.bmp");
 * 注意  ：图片为24为真彩色位图图片
 					 图片宽度不能超过320
					 图片在LCD上的粘贴范围为:纵向:  [x,x+图像高度]   横向 [Y，Y+图像宽度]
					 当图片为320*240时--建议X输入0  y输入0
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
        
        //读取位图文件头信息        
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
        
        //读取位图信息头信息
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
    
    l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);		//计算位图的实际宽度并确保它为32的倍数	    
    
    if(l_width>960)
    {
        BMP_DEBUG_PRINTF("\nSORRY, PIC IS TOO BIG (<=320)\n");
        return;
    }
    
    if(bitInfoHead.biBitCount>=24)
    {

        bmp_lcd(x,240-y-height,width, height);																	//LCD参数相关设置

        for(i=0;i<height+1; i++)
        {	
            
            for(j=0; j<l_width; j++)	 													//将一行数据全部读入
            {
                
                f_read(&bmpfsrc,pColorData+j,1,&read_num);
            }            
            
            for(j=0;j<width;j++) 																//一行有效信息
            {
                k = j*3;																				//一行中第K个像素的起点
                red = pColorData[k+2];
                green = pColorData[k+1];
                blue = 	pColorData[k];
                LCD_WR_Data(RGB24TORGB16(red,green,blue));		//写入LCD-GRAM
            }            
        }
        bmp_lcd_reset();		 																							//lcd扫描方向复原	        
    }    
    else 
    {        
        BMP_DEBUG_PRINTF("SORRY, THIS PIC IS NOT A 24BITS REAL COLOR");
        return ;
    }
    
    f_close(&bmpfsrc);    
}


