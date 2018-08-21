#ifndef __USER_VAL_H
#define __USER_VAL_H
#include "stm32f10x.h"
#include "bsp_type.h"
#include "stdio.h"
uint8_t getCmdType(uint8_t * buff);
void shellCmdService(volatile uint8_t  * pcBuff);
extern  HBP_HANDLE  *hbp;
extern ADC_HANDLE 	*adch;
extern IO_HANDLE		*ioh;
//#define AT_REPLAY printf

#define AT_REPLAY(...) printf("<");printf(__VA_ARGS__);printf(">")

#endif
