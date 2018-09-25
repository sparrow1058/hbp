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
typedef struct ADC_HANDLE_STRUCT
{
	const char *const name;
	bool	status;	// 设备打开状态	

	__IO u32 *adcVal;	//ADC 
	__IO u16 vol0;
	__IO u16 vol1;
	const pvFunVoid init;
	const pvFunBool ECGCtrl;	//控制打开
}ADC_HANDLE;

typedef struct REPORT_DATA_STRUCT
{
	u8		type;			//report type	0x00:Report All data  0x01: hr&bp	0x02: ecg value
	u8		hr;				//heart rate state  A0= NO Data   A1: new Data
	u8		hrVal;			//heart rate value
	u8		hbp;			//heart blood pressure B0 No Data	B1: new Data
	u8		sbpVal;			//1byte sbp value
	u8		dbpVal;			//1byte dbp value
	u8		ecg;			//ecg state   C0= NO data   C1: new Data
	u16		ecgVal;			//2 bytes ecg value
}REPORT_STRUCT;


#endif
