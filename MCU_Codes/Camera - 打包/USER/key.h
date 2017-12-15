#ifndef  __KEY_H_
#define  __KEY_H_
#include <stm32f10x.h>

#define Key_Port    GPIOD									//键盘GPIO口
#define Key_Line_1  GPIO_Pin_0            //键盘第1列，接输入
#define Key_Line_2  GPIO_Pin_1
#define Key_Line_3  GPIO_Pin_2
#define Key_Line_4  GPIO_Pin_3						

#define Key_Row_1  GPIO_Pin_4            //键盘第1行，初始置0
#define Key_Row_2  GPIO_Pin_5
#define Key_Row_3  GPIO_Pin_6
#define Key_Row_4  GPIO_Pin_7

#define Key_Line  (Key_Line_1|Key_Line_2|Key_Line_3|Key_Line_4)         //键盘列
#define Key_Row   (Key_Row_1|Key_Row_2|Key_Row_3|Key_Row_4)							//键盘行

#define Key_EXTI_Line1   EXTI_Line0			  
#define Key_EXTI_Line2   EXTI_Line1
#define Key_EXTI_Line3   EXTI_Line2
#define Key_EXTI_Line4   EXTI_Line3
#define Key_EXTI_Line  (Key_EXTI_Line1 |Key_EXTI_Line2 |Key_EXTI_Line3 |Key_EXTI_Line4)

#define Key_EXTI_PortSource  GPIO_PortSourceGPIOD
#define Key_EXTI_PinSource1  GPIO_PinSource0
#define Key_EXTI_PinSource2  GPIO_PinSource1 
#define Key_EXTI_PinSource3  GPIO_PinSource2
#define Key_EXTI_PinSource4  GPIO_PinSource3



void     Key_Config(void);
uint8_t  Key_Check(void);
void     Key_Input(void);
void     Show_Input(void);
static int Key_Change(int key);

#endif


