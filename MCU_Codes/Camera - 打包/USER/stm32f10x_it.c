
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "TIMx.h"
#include "cam.h"
#include "string.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//extern __IO Date_TypeDef  System_Date;
//extern __IO Time_TypeDef  System_Time;

//extern __IO	int32_t				CH_Sample[16];

//extern __IO uint8_t       UART1_Rece_ByteNum;
//extern __IO	uint8_t 			UART1_Receive[45];
//extern __IO uint8_t       UART2_Rece_ByteNum;
//extern __IO	uint8_t 			UART2_Receive[45];
//extern __IO uint8_t       UART3_Rece_ByteNum;
//extern __IO	uint8_t 			UART3_Receive[45];
//extern __IO uint8_t       UART4_Rece_ByteNum;
//extern __IO	uint8_t 			UART4_Receive[45];
//extern __IO uint8_t 	    UART5_Rece_ByteNum;
//extern __IO	uint8_t 			UART5_Receive[80];


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	
}

__IO uint8_t 	    RTC_Temp_1;
__IO uint8_t 	    AUTO_START_Key_Temp=1;

__IO uint8_t 	    MUANUALControlModeTemp = 1; 
__IO uint8_t 	    MUANUALControl_ON_OFFTemp = 1;
__IO uint8_t 	    AUTOControlModeTemp = 1; 
__IO uint8_t 	    AUTOControl_ON_OFFTemp = 1;




void RTC_IRQHandler(void)
{
}
/*************************************************************************************/	

void EXTI9_5_IRQHandler(void)
{

}

void EXTI14IRQHandler(void)
{

}
		 
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(Key_EXTI_Line1) != RESET)
	{


		EXTI_ClearITPendingBit(Key_EXTI_Line);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(Key_EXTI_Line2) != RESET)
	{


		EXTI_ClearITPendingBit(Key_EXTI_Line);
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(Key_EXTI_Line3) != RESET)
	{


		EXTI_ClearITPendingBit(Key_EXTI_Line);
	}
}
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(Key_EXTI_Line4) != RESET)
	{

		EXTI_ClearITPendingBit(Key_EXTI_Line);
	}
}
		 




void USART2_IRQHandler(void)
{
	/*
	static unsigned char Rev_Buf[100]={0};
	static int counter = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET || USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART_ClearITPendingBit(USART2, USART_FLAG_ORE);
		Rev_Buf[counter] = USART_ReceiveData(USART2);
		
		
		
		
	}
	*/
 }
	
	










void UART4_IRQHandler(void)
{ 
/*
	static uint8_t  Rev_Buf[200]={0};
	static uint8_t UART4_Rece_ByteNum = 0;
	uint8_t   USART4_Receive_Byte = 0;
    char temp[20] = {0};
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET || USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		USART_ClearITPendingBit(UART4, USART_FLAG_ORE);
		
		USART4_Receive_Byte = USART_ReceiveData(UART4);
		Rev_Buf[UART4_Rece_ByteNum++] = USART4_Receive_Byte;
		
		if(USART4_Receive_Byte == 0x0A)
		{
			UART4_Rece_ByteNum = 0;
		}
    }
		*/
	
}

void UART5_IRQHandler(void)			 
{	
	
}
     




void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
        
    }
}


void TIM2_IRQHandler(void) //
{  
	
	

    static int num = 0;
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        num++;
        
    }
    
    if(TIM_GetITStatus(TIM2, TIM_IT_Trigger) != RESET)
    {   
       
        TIM_ClearITPendingBit(TIM2, TIM_IT_Trigger);
    }
    
   
}



void TIM3_IRQHandler(void)
{
     
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);
        
    }
}


void TIM5_IRQHandler(void) 
{

    if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM5,TIM_FLAG_Update);
        
    }
}
void TIM6_IRQHandler(void)//ms
{
    if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM6,TIM_FLAG_Update);
        
    }
}


#define BUFF_SIZE 500


int status = 1;
int count = 0;
int flag_reset = 0;
int flag_clear = 0;
int flag_capture = 0;
int flag_getsize = 0;
int flag_sendall = 0;

int fragment_num = 0;
const int fragment_length = 256;

int flag_request = 1;
int flag_send = 0;
int flag_recvfromcam = 0;
int flag_replyfromsock = 0;
int flag_end = 0;

int count_send = 0;
int count_request = 0;
int totalsize = 0;
int address = 0;

char recv_data[1024] = {0};
int recv_length = 0;
char send_data[1024] = {0};
int send_length = 0;


void TIM4_IRQHandler(void)
{
	 
    if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);
		
		switch(status)
		{
			case 1:
				//wait for 2.5s
				count = count + 1;
				if(count >= 25)
				{
					count = 0;
					status = 2;
				}
				break;
			
			case 2:
				//send reset signal
				//flag_reset will be changed in USART1 IT
				if(!flag_reset)
				{
					count = count + 1;
					if(count % 10 == 1)
					{
						CamReset();
					}
					else if(count == 100)
					{
						count = 0;
						status = 1;
						flag_reset = 0;
					}
				}
				else if(flag_reset)
				{
					count = 0;
					status = 3;
					flag_reset = 0;
				}
				
				break;
			case 3:
				//send the clear signal
				//flag_clear can be changed in USART1 IT
				if(!flag_clear)
				{
					count = count + 1;
					if(count % 10 == 1)
					{
						CamClearPic();
					}
					else if(count == 100)
					{
						count = 0;
						status = 1;
						flag_clear = 0;
					}
				}
				else if(flag_clear)
				{
					count = 0;
					status = 4;
					flag_clear = 0;
				}
				break;
			case 4:
				//take a picture 
				//flag_capture can be changed in USART1 IT
				if(!flag_capture)
				{
					count = count + 1;
					if(count % 20 == 1)
					{
						CamTakeOnePic();
					}
					else if(count == 100)
					{
						count = 0;
						status = 1;
						flag_capture = 0;
					}
				}
				else if(flag_capture)
				{
					count = 0;
					status = 5;
					flag_capture = 0;
				}
				break;
			case 5:
				//get the size
				//flag_getsize can be changed in USART1 IT
				if(!flag_getsize)
				{
					count = count + 1;
					if(count % 10 == 1)
					{
						CamGetPicSize();
					}
					else if(count == 100)
					{
						count = 0;
						status = 1;
						flag_getsize = 0;
					}
				}
				else if(flag_getsize)
				{
					count = 0;
					status = 6;
					flag_getsize = 0;
				}
				break;
			case 6:
				//send the fragments of pic
			
				if(address >= totalsize)
				{
					static int count_end = 0;
					if(count_end++ % 10 == 0)
					{
						Send_UART3((uint8_t*)"ST:END",strlen("ST:END"));
					}
					else if(count_end >= 300)
					{
						flag_end = 1;
					}
					
					
				}
				if(flag_end)
				{
					status = 1; 
					flag_request = 1;
					flag_send = 0;
					flag_recvfromcam = 0;
					flag_replyfromsock = 0;
					flag_end = 0;

					count_send = 0;
					count_request = 0;
					totalsize = 0;
					address = 0;
					memset((char*)recv_data,0,1024);
					memset((char*)send_data,0,1024);
					recv_length = 0;
					send_length = 0;
					break;
				}
				
				if(flag_request)
				{
					if(count_request++ % 10 == 0)
					{
						CamReadPicBySize(address,fragment_length,totalsize);
					}
					else
					{
						if(flag_recvfromcam)
						{
							count_request = 0;
							flag_recvfromcam = 0;
							if(CamCheckout(recv_data,recv_length))
							{
								flag_request = 0;
								flag_send = 1;
							}
						}
					}
				}
				else if(flag_send)
				{
					if(count_send++ % 20 == 0)
					{
						int send_len = 0;
						GenerateData(recv_data,recv_length,address,send_data,&send_len);
						SendToSocket(send_data,send_len);
					}
					else
					{
						if(flag_replyfromsock)
						{
							flag_send = 0;
							flag_request = 1;
							flag_replyfromsock = 0;
							address += fragment_length;
							if(address >= totalsize)
							{
								Send_UART3((uint8_t*)"ST:END",strlen("ST:END"));
							}
						}
					}
					
				}
				
				
				
				break;
			
		}
		
		
    }
}




uint8_t  Rev_Buf[BUFF_SIZE]={0};
void USART1_IRQHandler(void)
{
    
    static int count_ch = 0;
    uint8_t   ch = 0;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET || USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        USART_ClearITPendingBit(USART1, USART_FLAG_ORE);
        
        ch = USART_ReceiveData(USART1);

        switch(status)
        {
            case 1:
                break;
            case 2:
                if(ch == 0x76)
                {
                    count_ch = 0;
                    Rev_Buf[count_ch++] = ch;
                }
                else if( count_ch < 4)
                {
                    Rev_Buf[count_ch++] = ch;
					if(count_ch >= 4)
					{
						if(Rev_Buf[0]==0x76 && Rev_Buf[1] == 0x00 && Rev_Buf[2]==0x26 && Rev_Buf[3]==0x00)
						{
							flag_reset = 1;
							memset((char*)Rev_Buf,0,BUFF_SIZE);
							count_ch = 0;
						}
						count_ch = 0;
					}
                }
                
                
                break;
                
            case 3:
                if(ch == 0x76)
                {
                    count_ch = 0;
                    Rev_Buf[count_ch++] = ch;
                }
                else if( count_ch < 5 && Rev_Buf[0] == 0x76)
                {
                    Rev_Buf[count_ch++] = ch;
					if( count_ch == 5)
					{
						if(Rev_Buf[0]==0x76 && Rev_Buf[1] == 0x00 && Rev_Buf[2]==0x36 && Rev_Buf[3]==0x00 && Rev_Buf[4]==0x00)
						{
							flag_clear = 1;
							memset((char*)Rev_Buf,0,BUFF_SIZE);
							count_ch = 0;
						}
						count_ch = 0;
					}
					
					
                }
				
                
                break;
                
            case 4:
                if(ch == 0x76)
                {
                    count_ch = 0;
                    Rev_Buf[count_ch++] = ch;
                }
                else if( count_ch < 5 && Rev_Buf[0] == 0x76)
                {
                    Rev_Buf[count_ch++] = ch;
					if(count_ch >= 5)
					{
						if(Rev_Buf[0]==0x76 && Rev_Buf[1] == 0x00 && Rev_Buf[2]==0x36 && Rev_Buf[3]==0x00 && Rev_Buf[4]==0x00)
						{
							flag_capture = 1;
							memset((char*)Rev_Buf,0,BUFF_SIZE);
							count_ch = 0;
						}
						count_ch = 0;
					}
                }
                break;
            
            case 5:
                if(ch == 0x76)
                {
                    count_ch = 0;
                    Rev_Buf[count_ch++] = ch;
                }
                else if(count_ch < 9 && Rev_Buf[0] == 0x76)
                {
                    Rev_Buf[count_ch++] = ch;
					if(count_ch >= 9)
					{
						if(Rev_Buf[0]==0x76 && Rev_Buf[1] == 0x00 && Rev_Buf[2]==0x34 && Rev_Buf[3]==0x00 && Rev_Buf[4]==0x04)
						{
							flag_getsize = 1;
							totalsize = (Rev_Buf[7] << 8) + Rev_Buf[8];
							memset((char*)Rev_Buf,0,BUFF_SIZE);
							count_ch = 0;
						}
						count_ch = 0;
					}
                }
                
                break;
                
            case 6:
            {
				Rev_Buf[count_ch++] = ch;
				if(count_ch == 1 && ch != 0x76)
				{
					count_ch = 0;
					break;
				}
				
				if(count_ch == 5)
				{
					if(Rev_Buf[0] != 0x76 || Rev_Buf[1] != 0x00 || Rev_Buf[2] != 0x32 || Rev_Buf[3] != 0x00 || Rev_Buf[4] != 0x00)
					{
						count_ch = 0;
						break;
					}
				}
				
				if(count_ch > 5)
				{
					if(Rev_Buf[count_ch-1] == 0x00 && Rev_Buf[count_ch-2] == 0x00 && Rev_Buf[count_ch-3]==0x32 && Rev_Buf[count_ch-4] == 0x00 && Rev_Buf[count_ch-5] == 0x76)
					{
						int i = 0;
						
						for(i=5;i<count_ch-5;i++)
						{
							recv_data[i-5] = Rev_Buf[i]; 
						}
						
						recv_length = i-5;
						flag_recvfromcam = 1;
						count_ch = 0;
						memset(Rev_Buf,0,BUFF_SIZE);
					}
				}
				if(count_ch >= BUFF_SIZE -1)
				{
					count_ch = 0;
					memset(Rev_Buf,0,BUFF_SIZE);
				}
				
                
                break;
            }
              

			
        }
    }
        
    
}




void USART3_IRQHandler(void)
{
    static uint8_t  Rev_Buf3[100]={0};
    static uint8_t count_ch = 0;
    uint8_t   ch = 0;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET || USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
    {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        USART_ClearITPendingBit(USART3, USART_FLAG_ORE);
        
        ch = USART_ReceiveData(USART3);
		
        Rev_Buf3[count_ch++] = ch;
		
		if(Rev_Buf3[0] != 'O')
		{
			memset(Rev_Buf3,0,100);
			count_ch = 0;
		}
		else if(count_ch >7 && Rev_Buf[6] != 0x0A)
		{
			memset(Rev_Buf3,0,100);
			count_ch = 0;
		}
        else if(count_ch == 7 && ch == 0x0A)
        {
            int temp = 0;
			count_ch = 0;
			if(address >= totalsize)
			{
				if(Rev_Buf3[3] == 'E' && Rev_Buf3[4]=='N' && Rev_Buf3[5]=='D')
				{
					flag_end = 1;
					return;
				}
			}
			temp = (Rev_Buf3[3]<<8) + Rev_Buf3[4];
            if(temp == address)
            {
                flag_replyfromsock = 1;
				memset(Rev_Buf3,0,100);
            }
        }
		
		
        
    
}

    
}       
