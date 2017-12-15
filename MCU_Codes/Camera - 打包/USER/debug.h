#ifndef DEBUG_H
#define DEBUG_H
#include <stm32f10x.h>
void SendDebug(char val1);
void SendDebug2(char val1,char val2);
void SendDebug3(char val1,char val2,char val3);
void SendDebugInt(int val);
void SendDebugInt2(int val1,int val2);
#endif // DEBUG_H
