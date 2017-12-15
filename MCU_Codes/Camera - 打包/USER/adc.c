#include "adc.h"
 __IO uint16_t ADC_ConvertedValue;
 __IO 	uint16_t	 ADC_ConvValue[100][6];
 //__IO u16 ADC_ConvertedValueLocal;

/**************************************************************************************************/
void ADC_GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		//ADC��ӦGPIO���ÿ�����
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/**************************************************************************************************/
/*	function:		ADC_DMA_Config()											  																  				*/
/*	����		:		DMA��ʽ���ó���	 					  																											*/
/**************************************************************************************************/
void ADC_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
		//	DMA1����
		DMA_DeInit(DMA1_Channel1);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;   //ADC��ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &ADC_ConvValue; //�ڴ��ַ
		DMA_InitStructure.DMA_BufferSize = 6 * 100;	                     //DMA�����С
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	             //���ݴ��䷽��
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	   	//����
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_Init(DMA1_Channel1,&DMA_InitStructure);
			
}
/**************************************************************************************************/
/*	function:		ADC_Mode_Config()																															  				*/
/*	����		:		����ADCģʽ��ʹ��ADCת��																													*/
/**************************************************************************************************/
void ADC_Mode_Config(void)
{
		ADC_InitTypeDef ADC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 ,ENABLE);
		//ADC1����
		ADC_InitStructure.ADC_Mode =ADC_Mode_Independent;    //����ADCģʽ
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //ɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  //��������ת��ģʽ������ͣ�ؽ���ADCת��
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	   	//�ɼ������Ҷ���
		ADC_InitStructure.ADC_ExternalTrigConv =	ADC_ExternalTrigConv_None;	 	//��ʹ���ⲿ����ת��
		ADC_InitStructure.ADC_NbrOfChannel =6;				//Ҫת����ͨ����Ŀ6
		ADC_Init(ADC1,&ADC_InitStructure);		  

    /*����ADC1��ͨ��10Ϊ55.	5���������ڣ�����Ϊ1 */ 
		ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 1 ,ADC_SampleTime_55Cycles5);	   //waterfolw  ����
		/*����ADC1��ͨ��11Ϊ55.	5���������ڣ�����Ϊ2 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 2 ,ADC_SampleTime_55Cycles5);		//waterlevel  ˮλ
		/*����ADC1��ͨ��12Ϊ55.	5���������ڣ�����Ϊ3 */								    
		ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 3 ,ADC_SampleTime_55Cycles5);		//BAT_AD    ��ص�ѹ
		/*����ADC1��ͨ��13Ϊ55.	5���������ڣ�����Ϊ4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_13, 4 ,ADC_SampleTime_55Cycles5);	    //workstatus
		/*����ADC1��ͨ��13Ϊ55.	5���������ڣ�����Ϊ4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_14, 5 ,ADC_SampleTime_55Cycles5);	    //ˮѹ
		/*����ADC1��ͨ��13Ϊ55.	5���������ڣ�����Ϊ4 */
		ADC_RegularChannelConfig(ADC1,ADC_Channel_15, 6 ,ADC_SampleTime_55Cycles5);	    //BACK UP 1
				
	    /*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9MHz*/		
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);
		/* Enable ADC1 */
		ADC_Cmd(ADC1,ENABLE);
	   /* Enable ADC1 DMA */
		ADC_DMACmd(ADC1,ENABLE);
		/*��λУ׼�Ĵ��� */
		ADC_ResetCalibration(ADC1);
	   	/*�ȴ�У׼�Ĵ�����λ��� */
		while(ADC_GetResetCalibrationStatus(ADC1));
        /* ADCУ׼ */
		ADC_StartCalibration(ADC1);
		/* �ȴ�У׼���*/
		while(ADC_GetCalibrationStatus(ADC1));
}

/**************************************************************************************************/
/* ��������ADC_Config                                                                             */
/* ����  ����                                                                                     */
/* ����  ����                                                                                     */
/* ���  ����                                                                                     */
/* ����  ���ⲿ����                                                                               */
/**************************************************************************************************/
void ADC_Config(void)
{
		ADC_GPIO_Config();
		ADC_DMA_Config();
		ADC_Mode_Config();
}

/**************************************************************************************************/
/*	function:		ADC_StartConv()														        		        						  	  	*/
/*	����		:	  ����DMA��ADC������ݲ���																													*/
/**************************************************************************************************/
void	ADC_StartConv(void)
{
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		DMA_Cmd(DMA1_Channel1,ENABLE);
}

/**************************************************************************************************/
/*	function:		ADC_VlaueFilter()														        		        						 	  	*/
/*	����		:	  ��ADC�ɼ��ĵõ�������ƽ������,��ת������Ӧ�ĵ�ѹֵ																*/
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
					ADC_VoltageValue[countA] =(int32_t) ( Sum_Value / 100 );//��λ:uV
					Sum_Value = 0;
			}
	*/
	//ֻ�ɼ�4��ͨ���������˲�
	
	
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

