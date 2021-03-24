#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"
#define ADC1_DR_Address ((uint32_t)0x4001244C)
#define ADC3_DR_Address ((uint32_t)0x40013C4C)

DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
__IO uint32_t ADC1ConvertedValue[1], ADC3ConvertedValue[1];
uint32_t Vol1,Vol2;

void RCC_Config();
void GPIO_Config();
void DMA_Config();
void ADC_Config(ADC_TypeDef* ADCx,uint8_t Channelx,uint8_t Rank,uint8_t ADC_SampleTime);
int main()
{
	RCC_Config();
	GPIO_Config();
	DMA_Config();
	ADC_Config(ADC1,ADC_Channel_4,1,ADC_SampleTime_13Cycles5);
	ADC_Config(ADC3,ADC_Channel_7,1,ADC_SampleTime_13Cycles5);
	while(1)
	{
	Vol1 = ADC1ConvertedValue[0];//ADC1->DR
	Vol2 = ADC3ConvertedValue[0];//ADC3->DR
	}
}
void RCC_Config()
{
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC3|
													RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
}
void GPIO_Config()
{
	// LED PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	// AIN PA4 ,  PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
void DMA_Config()
{
	// DMA1_Channel1 -> ADC1
	//DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1ConvertedValue;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	// DMA2 Channel5 -> ADC3
	//DMA_DeInit(DMA2_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC3_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC3ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA2_Channel5,&DMA_InitStructure);
	DMA_Cmd(DMA2_Channel5,ENABLE);
	
}
void ADC_Config(ADC_TypeDef* ADCx,uint8_t Channelx,uint8_t Rank,uint8_t ADC_SampleTime)
{
	ADC_InitTypeDef ADC_initStructure;
	ADC_initStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_initStructure.ADC_ScanConvMode = ENABLE;
	ADC_initStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_initStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_initStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_initStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADCx,&ADC_initStructure);
	ADC_RegularChannelConfig(ADCx,Channelx,Rank,ADC_SampleTime_41Cycles5);
	ADC_DMACmd(ADCx,ENABLE);// ADC DMA
	ADC_Cmd(ADCx,ENABLE); // Enable ADC1
	
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);
}