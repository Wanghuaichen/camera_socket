#ifndef __BZ_H
#define __BZ_H

#include "stm32f10x_gpio.h"
#include "stm32f103.h"
#include "sys.h"

#define BZ PEout(0)
#define BZ_ON    GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define BZ_OFF   GPIO_ResetBits(GPIOE,GPIO_Pin_0)
void BZ_Init(void);		   

#endif
