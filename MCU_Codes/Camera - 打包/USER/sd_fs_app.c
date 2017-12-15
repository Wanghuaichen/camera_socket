 #include "sd_fs_app.h"


FATFS myfs[2];                 // Work area (file system object) for logical drive
FIL myfsrc, myfdst;            // file objects
FRESULT myres;                 // FatFs function common result code
uint8_t mybuffer[512];            // file copy buffer
uint8_t my_latest_buffer[512];
uint32_t mybr, mybw;               // File R/W count
uint16_t mya = 0;



/*******************************************************************************
* Function Name  : Sdfs_create
* Description    : 新建一个文件
* Input          : new_file_name--新建文件的名称 
* Output         : None
* Return         : 0(success)  1(file existed )  -1(fail)
* Attention		 : None
*******************************************************************************/           
int8_t Sdfs_create(char *new_file_name)
{
  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, new_file_name, FA_CREATE_NEW);

	if(myres == FR_OK)
	{
		f_close(&myfsrc);
		return 0;      
	}
	else if ( myres == FR_EXIST )  //如果文件已经存在
		return FR_EXIST;
	else
		return -1;
}

/*******************************************************************************
* Function Name  : Sdfs_new
* Description    : 兴建一个文件并写入数据  
* Input          : new_file_name--兴建文件的名称  
*				   write_buffer--写入文件的数据缓冲区地址  
*				   buffer_size--缓冲区大小
* Output         : None
* Return         : 0(success)  1(file existed )  -1(fail)
* Attention		 : None
*******************************************************************************/           
int8_t Sdfs_new(char *new_file_name, uint8_t *write_buffer, uint8_t buffer_size)
{
  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, new_file_name, FA_CREATE_NEW | FA_WRITE);

	if(myres == FR_OK)
	{     
		myres = f_write(&myfsrc, write_buffer, buffer_size, &mybr); //写入数据   
		f_close(&myfsrc);
		return 0;      
	}
	else if ( myres == FR_EXIST )  //如果文件已经存在
		return FR_EXIST;
	else
		return -1;
}


/*******************************************************************************
* Function Name  : Sdfs_write
* Description    : 对文件写入数据  
* Input          : new_file_name--下入数据文件的名称  
*				   write_buffer--写入文件的数据缓冲区地址  
*				   buffer_size--缓冲区大小
* Output         : None
* Return         : 0(success)   -1(fail)
* Attention		 : None
*******************************************************************************/            
int8_t Sdfs_write(char *write_file_name, uint8_t *write_buffer, uint8_t buffer_size)
{
  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, write_file_name, FA_WRITE);

  if ( myres == FR_OK )
	{
		//将指针指向文件末
		myres = f_lseek(&myfsrc, myfsrc.fsize);
		/* Write buffer to file */
		myres = f_write(&myfsrc, write_buffer, buffer_size, &mybr); //写入数据
		f_close(&myfsrc);
		return 0;      
	}
	else if(myres == FR_NO_FILE)	 //如果没有该文件
		return FR_NO_FILE;
	else
		return -1;
}



/*******************************************************************************
* Function Name  : Sdfs_read
* Description    : 从一个文件读出数据到缓冲区 
* Input          : read_file_name--文件的名称  
*				   				save_buffer--数据需要保存的地址 
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		   : None
* Example        : Sdfs_read("0:Config.txt", Buffer);
*******************************************************************************/ 
int8_t Sdfs_read(char *read_file_name, uint8_t *save_buffer)
{
  int16_t count=0, i=0;

  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, read_file_name, FA_OPEN_EXISTING | FA_READ);
	if ( myres == FR_OK ) 
	{
		for(;;)
		{
			for(mya=0; mya<512; mya++) 	/* 清缓冲区 */
				mybuffer[mya]=0;
			
			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* 将文件里面的内容以512字节为单位读到本地缓冲区 */
			
			//打印到用户指定的缓冲区缓冲区
			for(mya = count*512, i = 0; i < 512; i++, mya++)
				save_buffer[mya] = mybuffer[i];
			
			count++;
			if(myres || mybr == 0) 
			{
				f_close(&myfsrc);
				break;   // error or eof
			}
		}
		return 0;
	}
	else
		return -1;
}


/*******************************************************************************
* Function Name  : GetNOInfo_fr_sd
* Description    : 从SD卡字库中读取终端号到指定的缓冲区 
* Input          : save_buffer---数据保存地址
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/ 
int8_t GetNOInfo_fr_sd(uint8_t *save_buffer)
{
  int16_t i=0, j = 0;
  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, "0:sysconfig.txt", FA_OPEN_EXISTING | FA_READ);
	if ( myres == FR_OK ) 
	{
		for(;;)
		{
			for(mya=0; mya<512; mya++) 	/* 清缓冲区 */
				mybuffer[mya]=0;

			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* 将文件里面的内容以512字节为单位读到本地缓冲区 */
			i = 0;	//从起点开始查找
			while(i < 512)
			{	//<2> NO: 0538-DY-2A01
				if((mybuffer[i] == 'N')&&(mybuffer[i+1] == 'O')&&(mybuffer[i+2] == ':'))//NO:
				{
					while((mybuffer[i] < '0')||(mybuffer[i] > '9'))	i++;	//不是数字
					
					for(j = 0; j < 12; j++)
					{
						if(mybuffer[i] != 0x0D)//0538-DY-2A01
						{
							save_buffer[j] = mybuffer[i];
							i++;
						}
					}
					i = 512;	//查找拷贝结束了
				}
				else
					i++;
			}
			if(myres || mybr == 0) 
			{
				f_close(&myfsrc);
				break;   // error or eof
			}
		}
		return 0;
	}
	else
		return -1;
}



/*******************************************************************************
* Function Name  : GetCHInfo_fr_sd
* Description    : 从SD卡字库中读取终端号到指定的缓冲区 
* Input          : save_buffer---数据保存地址
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/ 
int8_t GetCHInfo_fr_sd(uint8_t *save_buffer)
{
  int16_t i=0, j = 0;
  f_mount(0, &myfs[0]);
  myres = f_open(&myfsrc, "0:sysconfig.txt", FA_OPEN_EXISTING | FA_READ);
	if ( myres == FR_OK ) 
	{
		for(;;)
		{
			for(mya=0; mya<512; mya++) 	/* 清缓冲区 */
				mybuffer[mya]=0;
			
			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* 将文件里面的内容以512字节为单位读到本地缓冲区 */
			i = 0;
			while(i < 512)
			{
				if((mybuffer[i] == 'S')&&(mybuffer[i+1] == 'C')&&(mybuffer[i+2] == 'S'))
				{
					while(mybuffer[i] != ':')//找到':'
						i++;
					i = i + 2; 		//跳过空格
					save_buffer[j] = mybuffer[i];
					j++;
					i = i + 2;	//跳过空格
					save_buffer[j] = mybuffer[i];
					j++;
				}
				else
					i++;
			}
			if(myres || mybr == 0) 
			{
				f_close(&myfsrc);
				break;   // error or eof
			}
		}
		return 0;
	}
	else
		return -1;
}

/*******************************************************************************
* Function Name  : GetGBKCode_from_sd
* Description    : 从SD卡字库中读取自摸数据到指定的缓冲区 
* Input          : pBuffer---数据保存地址  
*				   					c--汉字字符低字节码 
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/ 
int8_t GetGBKCode_from_sd(uint8_t* pBuffer,const uint8_t * c)
{ 
  uint8_t High8bit,Low8bit;
  int32_t pos;
	High8bit=*c;     /* 取高8位数据 */
	Low8bit=*(c+1);  /* 取低8位数据 */

	pos = ((High8bit-0xb0)*94+Low8bit-0xa1)*2*16;
	f_mount(0, &myfs[0]);
	myres = f_open(&myfsrc , "0:/HZLIB.bin", FA_OPEN_EXISTING | FA_READ);

	if ( myres == FR_OK )
	{
		f_lseek (&myfsrc, pos);														 //指针偏移
		myres = f_read( &myfsrc, pBuffer, 32, &mybr );		 //16*16大小的汉字 其字模 占用16*2个字节
		f_close(&myfsrc);
		return 0;
	}
	else
		return -1;
}



