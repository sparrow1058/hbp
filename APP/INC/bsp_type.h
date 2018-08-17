#ifndef __BSP_TYPE_H
#define __BSP_TYPE_H
#include "stm32f10x.h"
#include "stdint.h"

typedef void    (*pvFunVoid) (void);
typedef void    (*pvFunBool) (bool     bVal);
//For HBP I2C Device
typedef uint16_t	(*pvFun_Bytes)	(void);

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




#endif
