#include "stm32f10x.h"
#include "bsp_type.h"
#include "user_val.h"

#define ADC1_DR_Address    ((u32)0x4001244C)
#define ADC2_DR_Address			((u32)0x4001244C)
#define IO_LPSEL		//	
__IO u32 ADC_ConvertedValue;

static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable DMA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 , ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure PC.01  as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);				// PC1,?????????
}
static void ADC1_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
/*

  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC2_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	*/
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;;	
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;//DMA»º´æµÄ´óÐ¡
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word ;	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_InitStructure.ADC_Mode =ADC_Mode_RegSimult;
  	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	
	ADC_Init(ADC1, &ADC_InitStructure);
 
	/* ADC2 configuration */
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult ;	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	
	ADC_Init(ADC2, &ADC_InitStructure);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
//ADC1 PA1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );//A1
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);  
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
//ADC2 PA2
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5 );//A5
	/* Enable ADC2 DMA */
	ADC_DMACmd(ADC2, ENABLE);	
	/* Enable ADC2 */
	ADC_Cmd(ADC2, ENABLE);   
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));	
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
     
  /* Start ADC1 Software Conversion */ 
//  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

void ECG_ONOFF(bool cmd)
{

	if(cmd)
	{
		adch->status=true;
		 ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		 ADC_SoftwareStartConvCmd(ADC2, ENABLE);

	}else
	{
		ADC_SoftwareStartConvCmd(ADC1, DISABLE);
		ADC_SoftwareStartConvCmd(ADC2, DISABLE);

		adch->status=false;		
	}
}
ADC_HANDLE adc_handle={
	.name	= "adc",
	.status	=false,
	.adcVal	=&ADC_ConvertedValue,
	.init		=ADC1_Init,
	.ECGCtrl	=ECG_ONOFF,
};
ADC_HANDLE *adch	=&adc_handle;
