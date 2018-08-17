#ifndef __BSP_TYPE_H
#define __BSP_TYPE_H
#include "stm32f10x.h"
#include "stdint.h"
#include "stdbool.h"

typedef void    (*pvFunVoid) (void);
typedef void    (*pvFunBool) (bool     bVal);
//For HBP I2C Device
typedef uint16_t	(*pvFun_Bytes)	(void);

typedef void (*pvFunSet)(uint8_t id,bool val);
typedef bool (*pbFunGet)(uint8_t id);

typedef struct CMD_HANDLE_STRUCT
{
	const char * cmd;
	const void * callFun;
}CMD_HANDLE;
typedef struct HBP_HANDLE_STRUCT
{
		const char * const name;
	//For Model version
	const char * hVersion;
	const char * sVersion;
	const char * hyVersion;
	
	const pvFunVoid init;		//i2C init
	const pvFunBool hpCtrl;		//device on off
	const pvFun_Bytes getHR;	//get heart rate
	const pvFun_Bytes getBP;	//get blood pressure
	
}HBP_HANDLE;
typedef struct IO_HANDLE_STRUCT
{
	const char * const name;
	uint8_t 	nums;
	
	const pvFunVoid init;		//IO config
	const pvFunSet ioset;		//set io
	const pbFunGet ioget;		//get io
}IO_HANDLE;



#endif
