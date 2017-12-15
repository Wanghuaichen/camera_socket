#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"
#include "Var_Def.h"

extern  __IO 	int32_t 	 ADC_VoltageValue[6];

void 		ADC_GPIO_Config(void);
void 		ADC_DMA_Config(void);
void 		ADC_Mode_Config(void);
void 		ADC_Config(void);
void		ADC_StartConv(void);
void		ADC_VlaueFilter(void);

#endif /* __ADC_H */

