#include "stm32f10x.h"
#include "bsp_type.h"
#define IOC_SET(ID,VAL)	if (VAL)	\
					GPIO_SetBits(GPIOC,ID);\
					else		\
					GPIO_ResetBits(GPIOC,ID)
#define IOC_GET(ID)	GPIO_GetBits(GPIOC,ID)					
uint16_t iolist[]=
{
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15,
}	
					
void IO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|  GPIO_Pin_15;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void IO_Set(uint8_t id,bool val)
{
	IOC_SET(iolist[id],val);
}
bool IO_Get(uint8_t id)
{
	IOC_GET(iolist[id],val);
}

IO_HANDLE	io_handle={
	.name	="io",
	.nums	=  10,
	.init	= IO_Init,
	.ioset	=IO_Set,
	.ioget	=IO_Get,
};