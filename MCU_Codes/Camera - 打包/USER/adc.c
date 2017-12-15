#include "adc.h"
 __IO uint16_t ADC_ConvertedValue;
 __IO 	uint16_t	 ADC_ConvValue[100][6];
 //__IO u16 ADC_ConvertedValueLocal;

/**************************************************************************************************/
void ADC_GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		//ADC对应GPIO复用口配置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/**************************************************************************************************/
/*	function:		ADC_DMA_Config()											  																  				*/
/*	功能		:		DMA方式配置程序	 					  																											*/
/**************************************************************************************************/
void ADC_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
		//	DMA1配置
		DMA_DeInit(DMA1_Channel1);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;   //ADC地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &ADC_ConvValue; //内存地址
		DMA_InitStructure.DMA_BufferSize = 6 * 100;	                     //DMA缓存大小
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	             //数据传输方向
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	   	//半字
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//半字
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_Init(DMA1_Channel1,&DMA_InitStructure);
			
}
/**************************************************************************************************/
/*	function:		ADC_Mode_Config()																															  				*/
/*	功能		:		配置ADC模式与使能ADC转换																													*/
/**************************************************************************************************/
void ADC_Mode_Config(void)
{
		ADC_InitTypeDef ADC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 ,ENABLE);
		//ADC1配置
		ADC_InitStructure.ADC_Mode =ADC_Mode_Independent;    //独立ADC模式
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //扫描模式，扫描模式用于多通道采集
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  //开启连续转换模式，即不停地进行ADC转换
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   	//采集数据右对齐
		ADC_InitStructure.ADC_ExternalTrigConv =	ADC_ExternalTrigConv_None;	 	//不使用外部触发转换
		ADC_InitStructure.ADC_NbrOfChannel =6;				//要转换的通道数目6
		ADC_Init(ADC1,&ADC_InitStructure);		  

    /*配置ADC1的通道10为55.	5个采样周期，序列为1 */ 
		ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 1 ,ADC_SampleTime_55Cycles5);	   //waterfolw  流速
		/*配置ADC1的通道11为55.	5个采样周期，序列为2 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 2 ,ADC_SampleTime_55Cycles5);		//waterlevel  水位
		/*配置ADC1的通道12为55.	5个采样周期，序列为3 */								    
		ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 3 ,ADC_SampleTime_55Cycles5);		//BAT_AD    电池电压
		/*配置ADC1的通道13为55.	5个采样周期，序列为4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_13, 4 ,ADC_SampleTime_55Cycles5);	    //workstatus
		/*配置ADC1的通道13为55.	5个采样周期，序列为4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_14, 5 ,ADC_SampleTime_55Cycles5);	    //水压
		/*配置ADC1的通道13为55.	5个采样周期，序列为4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_15, 6 ,ADC_SampleTime_55Cycles5);	    //BACK UP 1
				
	    /*配置ADC时钟，为PCLK2的8分频，即9MHz*/		
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);
		/* Enable ADC1 */
		ADC_Cmd(ADC1,ENABLE);
	   /* Enable ADC1 DMA */
		ADC_DMACmd(ADC1,ENABLE);
		/*复位校准寄存器 */
		ADC_ResetCalibration(ADC1);
	   	/*等待校准寄存器复位完成 */
		while(ADC_GetResetCalibrationStatus(ADC1));
        /* ADC校准 */
		ADC_StartCalibration(ADC1);
		/* 等待校准完成*/
		while(ADC_GetCalibrationStatus(ADC1));
}

/**************************************************************************************************/
/* 函数名：ADC_Config                                                                             */
/* 描述  ：无                                                                                     */
/* 输入  ：无                                                                                     */
/* 输出  ：无                                                                                     */
/* 调用  ：外部调用                                                                               */
/**************************************************************************************************/
void ADC_Config(void)
{
		ADC_GPIO_Config();
		ADC_DMA_Config();
		ADC_Mode_Config();
}

/**************************************************************************************************/
/*	function:		ADC_StartConv()														        		        						  	  	*/
/*	功能		:	  启动DMA与ADC多次数据采样																													*/
/**************************************************************************************************/
void	ADC_StartConv(void)
{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		DMA_Cmd(DMA1_Channel1,ENABLE);
}

/**************************************************************************************************/
/*	function:		ADC_VlaueFilter()														        		        						 	  	*/
/*	功能		:	  将ADC采集的得到的数据平均处理,并转换成相应的电压值																*/
/**************************************************************************************************/
void	ADC_VlaueFilter(void)
{
		uint32_t 	Sum_Value = 0;
		uint8_t  	countA 		= 0;
		uint8_t	 	countB 		= 0;
	/* 
		for(countA = 0; countA < 6 ; countA ++)
			{
					for(countB = 0; countB < 100 ; countB ++)
					{
							Sum_Value = Sum_Value + ADC_ConvValue[countB][countA];
					}
					ADC_VoltageValue[countA] =(int32_t) ( Sum_Value / 100 );//单位:uV
					Sum_Value = 0;
			}
	*/
	//只采集4号通道，进行滤波
	
	
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

