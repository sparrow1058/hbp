#ifndef __USER_VAL_H
#define __USER_VAL_H
#include "stm32f10x.h"
uint8_t getCmdType(uint8_t * buff);
void shellCmdService(volatile uint8_t  * pcBuff);



#endif
