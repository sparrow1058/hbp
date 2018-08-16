/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    ��I2C EEPROM(AT24C02)���ԣ�������Ϣͨ��USART1��ӡ�ڵ��Եĳ����նˡ�
 *          
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034 
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/	

#include "stm32f10x.h"
#include "usart1.h"
#include "i2c_ee.h"

#define  EEP_Firstpage      0x00
u8 I2c_Buf_Write[256];
u8 I2c_Buf_Read[256];
void I2C_Test(void);

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 * ����  ����
 */
int main(void)
{  
	/* ����ϵͳʱ��Ϊ 72M */      
  SystemInit();;

  /* ����1��ʼ�� */
	USART1_Config();

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();

	USART1_printf(USART1, "\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");
	USART1_printf(USART1, "\r\n ("__DATE__ " - " __TIME__ ") \r\n");
	 printf("asdfasfaf");	 
	//I2C_Test();

  while (1)
  {      
  }
}

/*
 * ��������I2C_EE_Test
 * ����  ��I2C(AT24C02)��д���ԡ�
 * ����  ����
 * ���  ����
 * ����  ����
 */
void I2C_Test(void)
{
	u16 i;

	printf("д�������\n\r");
    
	for ( i=0; i<=255; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = i;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //��I2c_Buf_Write��˳�����������д��EERPOM�� 
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);	 
  
  printf("\n\r����������\n\r");
  //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read�� 
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256); 

  //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("����:I2C EEPROMд������������ݲ�һ��\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  printf("I2C(AT24C02)��д���Գɹ�\n\r");
}

/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
