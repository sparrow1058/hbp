#include "stm32f10x.h"
#include "usart1.h"
#include "stdio.h"
#include "user_val.h"
#include "bsp_type.h"


volatile uint8_t aRxBuffer[100]={0};
volatile uint8_t RxCounter=0;
volatile uint8_t RxFrameState=0;
uint32_t adcgap=0;
void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 
int main(void)
{  
	/* ����ϵͳʱ��Ϊ 72M */      
  SystemInit();
  /* USART1 config 115200 8-N-1 */
	USART_Config();

	printf("xshell Init \r\n");
	ioh->init();		
	hbp->init();			// init i2c1 heart blood  device
	adch->init();
    while(1)
    {
			if(RxFrameState==1)
			{
		//		printf("Receive %d bytes \r\n",RxCounter);
				aRxBuffer[RxCounter]='\0';
				if(RxCounter>4)
				{
			//		printf("%s",aRxBuffer);
					shellCmdService(aRxBuffer);
					
				}
				RxCounter=0;
				RxFrameState=0;
     //   if(shell_rx_rdy){Task_ShellRxGuard(NULL);} 
			}
			report_data();
/*
			if(adch->status)
			{
				if(adcgap++>10)
				{
					adcgap=0;
					adch->vol0=(3300*((*adch->adcVal)&0xFFFF)/0xFFF);
					adch->vol1=(3300*((*adch->adcVal)>>16)/0xFFF);
					AT_REPLAY("ECG:%d %d ",adch->vol0,adch->vol1);
				//	AT_REPLAY("%x",*adch->adcVal);
				}
			}
*/
			Delay(0xfee); 
		}
}
