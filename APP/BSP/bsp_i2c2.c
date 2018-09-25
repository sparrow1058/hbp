#include "stm32f10x.h"
#include "bsp_type.h"
#include "user_val.h"
#include "stdio.h"

#define I2C_ID				I2C2
#define I2C_Speed			40000
#define HBP_ADDRESS			0xA0		//7bit address 0x60
#define REG_HBP_VER			0x00		//Read:  Return 8 bytes string
#define REG_HBP_CTRL		0x00		//Write: 0xA1  ON  ,, 0XA0  OFF
#define REG_HBP_STATUS		0x01		//Read:  bit0==1 Heart rate is update  bit1==1 ,blood pressure is update 
#define REG_HBP_HR			0x02		//Read:	1byte   HR:30-200
#define REG_HBP_BP			0x03		//Read: 2 bytes 

#define H_VERSION		"HW:1.00"
#define S_VERSION		"SW:1.00"
char	hyVersion[20];	

static void I2C2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
static void I2C2_Mode_Config(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1= HBP_ADDRESS;
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed=I2C_Speed;
	I2C_Cmd(I2C2,ENABLE);
	I2C_Init(I2C_ID,&I2C_InitStructure);
	I2C_AcknowledgeConfig(I2C_ID,ENABLE);
	
	
}

void I2C_EE_ByteWrite(u8 WriteAddr,u8 pBuffer)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C_ID, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C_ID, HBP_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
      
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2C_ID, WriteAddr);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C_ID, pBuffer); 
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C_ID, ENABLE);
}
void I2C_EE_BufferRead(u8 ReadAddr,u8* pBuffer,  u16 NumByteToRead)
{  
  //*((u8 *)0x4001080c) |=0x80; 
    while(I2C_GetFlagStatus(I2C_ID, I2C_FLAG_BUSY)); // Added by Najoua 27/08/2008
    
    
  /* Send START condition */
  I2C_GenerateSTART(I2C_ID, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C_ID, HBP_ADDRESS, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C_ID, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2C_ID, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C_ID, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2C_ID, HBP_ADDRESS, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C_ID, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(I2C_ID, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C_ID, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(I2C_ID);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C_ID, ENABLE);
}

void HBP_Init(void)
{
	I2C2_GPIO_Config();
	I2C2_Mode_Config();
	//gethyVersion();
}
HBP_HANDLE  hbp_handle=
{
	.name			= "em2",
	.hVersion	=H_VERSION,
	.sVersion	=S_VERSION,
	.hyVersion=hyVersion,
	.init			=HBP_Init,
	.hpCtrl		=devCtrl,
	.getHR		=getHeartRate,
	.getBP		=getBloodPressure,
};
HBP_HANDLE *hbp	=&hbp_handle;