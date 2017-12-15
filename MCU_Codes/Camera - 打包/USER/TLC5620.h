
#ifndef __TLC5620_H
#define __TLC5620_H

#include "cpld.h"

#define LTC5620_CHANNEL_A		0
#define LTC5620_CHANNEL_B		1
#define LTC5620_CHANNEL_C		2
#define LTC5620_CHANNEL_D		3

#define Conductivity_CH			0


uint16_t V_conductivity(uint16_t);

void LTC5620_DAC_OUTPUT(uint8_t,uint16_t);

#endif
