#include "BZ.h"
#include "sys.h"
extern void BZ_GPIO_config(void);


void BZ_Init(void)
{
 BZ_GPIO_config();
 //BZ=0;
 BZ_OFF;

}
