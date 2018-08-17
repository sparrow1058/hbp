/******************** (C) COPYRIGHT 2011 ?????????? ********************
 * ???  :usart1.c
 * ??    :?printf??????USART1???????printf?????????
 *           ???PC??????????????         
 * ????:??STM32???
 * ????:------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ???  :ST3.0.0
 *
 * ??    :fire  QQ: 313303034 
 * ??    :firestm32.blog.chinaunix.net
**********************************************************************************/

#include "usart1.h"
#include <stdarg.h>
#include "misc.h"
/*
 * ???:USART1_Config
 * ??  :USART1 GPIO ??,???????115200 8-N-1
 * ??  :?
 * ??  : ?
 * ??  :????
 */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* USART1 GPIO config */
   /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200/2;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
#ifdef USE_GD_MCU
	USART_InitStructure.USART_StopBits =USART_StopBits_1;// USART_StopBits_0_5;
#else
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
#endif

	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);  
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		
  USART_Cmd(USART1, ENABLE);

    


//
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 GPIO config */
   /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
  USART_Cmd(USART2, ENABLE);


    /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);    
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn ;//	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn ;//	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
 * ???:fputc
 * ??  :???c???printf?USART1
 * ??  :?
 * ??  :?
 * ??  :?printf??
 */
int fputc(int ch, FILE *f)
{
/* ?Printf?????? */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}

/*
 * ???:itoa
 * ??  :???????????
 * ??  :-radix =10 ??10??,?????0
 *         -value ???????
 *         -buf ???????
 *         -radix = 10
 * ??  :?
 * ??  :?
 * ??  :?USART1_printf()??
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * ???:USART1_printf
 * ??  :?????,???C???printf,???????C?
 * ??  :-USARTx ????,????????1,?USART1
 *		     -Data   ????????????
 *			   -...    ????
 * ??  :?
 * ??  :? 
 * ??  :????
 *         ????USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // ????????????
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //???
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //???
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //???
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;

        case 'd':										//???
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
extern volatile uint8_t aRxBuffer[100];
extern volatile uint8_t RxCounter;
extern volatile uint8_t RxFrameState;
void USART1_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART1->DR;
		aRxBuffer[RxCounter++]=c;
	} 
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)
	{
		USART1->SR;
		USART1->DR;
		RxFrameState=1;
	} 
}
void USART2_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{ 	
	    c=USART2->DR;
	 	USART_SendData(USART2, c);  
	} 
	 
}
/******************* (C) COPYRIGHT 2011 ?????????? *****END OF FILE****/ 

