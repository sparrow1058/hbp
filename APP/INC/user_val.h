#ifndef __USER_VAL_H
#define __USER_VAL_H
#include "stm32f10x.h"
#include "bsp_type.h"
#include "stdio.h"
//----------------
#define MAX_CMDS	20
//THE AT CMD ID 
#define AT_HVER		0
#define AT_SVER		1	
#define AT_HYVER	2
#define AT_HP_ON	3
#define AT_HP_OFF	4
#define AT_HR		5	
#define AT_BP		6
#define AT_ECGON	7
#define AT_ECGOFF	8
#define AT_UPF		9
#define AT_PKEY		10
#define AT_SKEY		11
#define AT_START	12
#define AT_STOP		13


void shellCmdService(volatile uint8_t  * pcBuff);
extern  HBP_HANDLE  *hbp;
extern ADC_HANDLE 	*adch;
extern IO_HANDLE		*ioh;
//#define AT_REPLAY printf

#define AT_REPLAY(...) printf("<");printf(__VA_ARGS__);printf(">")


#endif
