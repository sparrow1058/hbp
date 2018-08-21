#include "stm32f10x.h"
#include "bsp_type.h"
#include "user_val.h"

#define ECG_LEADOFF	PA14
#define ECG_FR			PA15
#define ECG_PDN			PB3
#define ECG_LPSEL		PB4

#define ECG_PWR			PB12
#define SPO2_PWR		PB13
#define BMP_PWR			PB14
#define INT_O				PB15
#define INT_I				PA8
#define ECG_LODN_DET	PB8
#define ECG_LODP_DET	PB9
#define DOR_DET				PC13
#define SYS_STATUS	PA3
#define SPO2_INT		PB0
#define LOCK_EN			PB1
#define EEPROM_CS		PA4


#define IOC_SET(ID,VAL)	if (VAL)	\
					GPIO_SetBits(GPIOB,ID);\
					else		\
					GPIO_ResetBits(GPIOB,ID)
#define IOC_GET(ID)	GPIO_ReadOutputDataBit(GPIOB,ID)					
uint16_t iolist[]=
{
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15,
};	
void IO_Set(uint8_t id,bool val)
{
	IOC_SET(iolist[id],val);
}
bool IO_Get(uint8_t id)
{
	
	return IOC_GET(iolist[id]);
}				
void IO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);	 // turn off all led
	//GPIO_SetBits(GPIOB, GPIO_Pin_13 );
	GPIO_SetBits(GPIOB, GPIO_Pin_14 );
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
}
void IO_Init(void)
{
	IO_Config();
	//GPIO_SetBits(GPIOB,GPIO_Pin_14);
//	printf("set pwr \n");
	
}
IO_HANDLE	io_handle={
	.name	="io",
	.nums	=  10,
	.init	= IO_Init,
	.ioset	=IO_Set,
	.ioget	=IO_Get,
};
IO_HANDLE *ioh	=&io_handle;
