#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"

#define LSI_TIM_MEASURE
__IO uint32_t LsiFreq = 40000;
extern __IO uint16_t CaptureNumber;
void GPIO_OConfig(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,GPIOSpeed_TypeDef GPIO_Speedx);
void TIM5_ConfigForLSI(void);
int main()
{
	SystemInit();
	GPIO_OConfig(GPIOC,GPIO_Pin_13,GPIO_Speed_50MHz);
	GPIO_OConfig(GPIOA,GPIO_Pin_3,GPIO_Speed_50MHz);
	// Check if the system has resumed from IWDG reset
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)!=RESET)
	{
		// IWDGRST flag set
		// Turn on led13
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		//Cleaar reset flag
		RCC_ClearFlag();
	}
	else{
		// TWDG flag is not set
		// Turn off led13
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
	}
	
#ifdef LSI_TIM_MEASURE
	RCC_LSICmd(ENABLE);
	
	//wait till LSI is ready
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
	// Wait untill the TIM5 get 2 LSI edges
//	while(CaptureNumber != 2)
//	{}
		
	//Disable TIM5 CC4 Interrupt Request
		TIM_ITConfig(TIM5,TIM_IT_CC4,DISABLE);
		
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
		
		IWDG_SetPrescaler(IWDG_Prescaler_32);
		
		IWDG_SetReload(LsiFreq/128);
		
		IWDG_ReloadCounter();
		
		IWDG_Enable();
		
#endif
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay(500);
		IWDG_ReloadCounter();
	}
	
}
void GPIO_OConfig(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,GPIOSpeed_TypeDef GPIO_Speedx)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speedx;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
	
}
void TIM5_ConfigForLSI(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;

  /* Enable TIM5 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  
  /* Enable the TIM5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;//TIM5_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Configure TIM5 prescaler */
  TIM_PrescalerConfig(TIM5, 0, TIM_PSCReloadMode_Immediate);

  /* Connect internally the TM5_CH4 Input Capture to the LSI clock output */
  GPIO_PinRemapConfig(GPIO_Remap_TIM5CH4_LSI, ENABLE);
  
  /* TIM5 configuration: Input Capture mode ---------------------
     The LSI oscillator is connected to TIM5 CH4
     The Rising edge is used as active edge,
     The TIM5 CCR4 is used to compute the frequency value 
  ------------------------------------------------------------ */
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  
  /* TIM10 Counter Enable */
  TIM_Cmd(TIM5, ENABLE);

  /* Reset the flags */
  TIM5->SR = 0;
    
  /* Enable the CC4 Interrupt Request */  
  TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);  
}
