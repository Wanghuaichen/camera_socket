#include "NVIC.h"
#include <stm32f10x.h>

void NVIC_Config(void)
{
		NVIC_InitTypeDef    NVIC_InitStructure; 					   					
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);      					//中断优先级分组	
		
    
        //Config TIM1
        NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
        NVIC_Init(&NVIC_InitStructure); 
     
        //Config TIM4
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
    
        //Config TIM2
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        //Config TIM5
        NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        //Config TIM6
        NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;                             
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;              
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
		//配置UART1接收中断
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			  		 	//指定中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	  	//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //指定响应优先级别
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              //打开中断
		NVIC_Init(&NVIC_InitStructure);	
		//配置UART3接收中断
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			  		 	//指定中断源
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  	//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            //指定响应优先级别
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              //打开中断
		NVIC_Init(&NVIC_InitStructure);	

	
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  							
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  			
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure); 
		
//		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  							
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  			
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
////	
//		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  							
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  			
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure); 
		
		//配置外部键盘中断
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}


