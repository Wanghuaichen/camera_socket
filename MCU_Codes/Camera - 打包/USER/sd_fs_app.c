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
* Description    : �½�һ���ļ�
* Input          : new_file_name--�½��ļ������� 
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
	else if ( myres == FR_EXIST )  //����ļ��Ѿ�����
		return FR_EXIST;
	else
		return -1;
}

/*******************************************************************************
* Function Name  : Sdfs_new
* Description    : �˽�һ���ļ���д������  
* Input          : new_file_name--�˽��ļ�������  
*				   write_buffer--д���ļ������ݻ�������ַ  
*				   buffer_size--��������С
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
		myres = f_write(&myfsrc, write_buffer, buffer_size, &mybr); //д������   
		f_close(&myfsrc);
		return 0;      
	}
	else if ( myres == FR_EXIST )  //����ļ��Ѿ�����
		return FR_EXIST;
	else
		return -1;
}


/*******************************************************************************
* Function Name  : Sdfs_write
* Description    : ���ļ�д������  
* Input          : new_file_name--���������ļ�������  
*				   write_buffer--д���ļ������ݻ�������ַ  
*				   buffer_size--��������С
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
		//��ָ��ָ���ļ�ĩ
		myres = f_lseek(&myfsrc, myfsrc.fsize);
		/* Write buffer to file */
		myres = f_write(&myfsrc, write_buffer, buffer_size, &mybr); //д������
		f_close(&myfsrc);
		return 0;      
	}
	else if(myres == FR_NO_FILE)	 //���û�и��ļ�
		return FR_NO_FILE;
	else
		return -1;
}



/*******************************************************************************
* Function Name  : Sdfs_read
* Description    : ��һ���ļ��������ݵ������� 
* Input          : read_file_name--�ļ�������  
*				   				save_buffer--������Ҫ����ĵ�ַ 
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
			for(mya=0; mya<512; mya++) 	/* �建���� */
				mybuffer[mya]=0;
			
			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* ���ļ������������512�ֽ�Ϊ��λ�������ػ����� */
			
			//��ӡ���û�ָ���Ļ�����������
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
* Description    : ��SD���ֿ��ж�ȡ�ն˺ŵ�ָ���Ļ����� 
* Input          : save_buffer---���ݱ����ַ
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
			for(mya=0; mya<512; mya++) 	/* �建���� */
				mybuffer[mya]=0;

			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* ���ļ������������512�ֽ�Ϊ��λ�������ػ����� */
			i = 0;	//����㿪ʼ����
			while(i < 512)
			{	//<2> NO: 0538-DY-2A01
				if((mybuffer[i] == 'N')&&(mybuffer[i+1] == 'O')&&(mybuffer[i+2] == ':'))//NO:
				{
					while((mybuffer[i] < '0')||(mybuffer[i] > '9'))	i++;	//��������
					
					for(j = 0; j < 12; j++)
					{
						if(mybuffer[i] != 0x0D)//0538-DY-2A01
						{
							save_buffer[j] = mybuffer[i];
							i++;
						}
					}
					i = 512;	//���ҿ���������
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
* Description    : ��SD���ֿ��ж�ȡ�ն˺ŵ�ָ���Ļ����� 
* Input          : save_buffer---���ݱ����ַ
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
			for(mya=0; mya<512; mya++) 	/* �建���� */
				mybuffer[mya]=0;
			
			myres = f_read( &myfsrc, mybuffer, sizeof(mybuffer), &mybr ); /* ���ļ������������512�ֽ�Ϊ��λ�������ػ����� */
			i = 0;
			while(i < 512)
			{
				if((mybuffer[i] == 'S')&&(mybuffer[i+1] == 'C')&&(mybuffer[i+2] == 'S'))
				{
					while(mybuffer[i] != ':')//�ҵ�':'
						i++;
					i = i + 2; 		//�����ո�
					save_buffer[j] = mybuffer[i];
					j++;
					i = i + 2;	//�����ո�
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
* Description    : ��SD���ֿ��ж�ȡ�������ݵ�ָ���Ļ����� 
* Input          : pBuffer---���ݱ����ַ  
*				   					c--�����ַ����ֽ��� 
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/ 
int8_t GetGBKCode_from_sd(uint8_t* pBuffer,const uint8_t * c)
{ 
  uint8_t High8bit,Low8bit;
  int32_t pos;
	High8bit=*c;     /* ȡ��8λ���� */
	Low8bit=*(c+1);  /* ȡ��8λ���� */

	pos = ((High8bit-0xb0)*94+Low8bit-0xa1)*2*16;
	f_mount(0, &myfs[0]);
	myres = f_open(&myfsrc , "0:/HZLIB.bin", FA_OPEN_EXISTING | FA_READ);

	if ( myres == FR_OK )
	{
		f_lseek (&myfsrc, pos);														 //ָ��ƫ��
		myres = f_read( &myfsrc, pBuffer, 32, &mybr );		 //16*16��С�ĺ��� ����ģ ռ��16*2���ֽ�
		f_close(&myfsrc);
		return 0;
	}
	else
		return -1;
}



