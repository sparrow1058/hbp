#include "stm32f10x.h"
#include "usart1.h"
#include "stdio.h"
#include "user_val.h"
#include "bsp_type.h"


volatile uint8_t aRxBuffer[100]={0};
volatile uint8_t RxCounter=0;
volatile uint8_t RxFrameState=0;

int main(void)
{  
	/* 配置系统时钟为 72M */      
  SystemInit();
  /* USART1 config 115200 8-N-1 */
	USART_Config();

	printf("xshell Init \r\n");
	ioh->init();		
	hbp->init();			// init i2c1 heart blood  device
	
    while(1)
    {
			if(RxFrameState==1)
			{
				printf("Receive %d bytes \r\n",RxCounter);
				aRxBuffer[RxCounter]='\0';
				if(RxCounter>4)
				{
					printf("%s",aRxBuffer);
					shellCmdService(aRxBuffer);
					
				}
				RxCounter=0;
				RxFrameState=0;
     //   if(shell_rx_rdy){Task_ShellRxGuard(NULL);} 
			}
		}
}
