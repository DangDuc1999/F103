#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"

void GPIO_AFConfig(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,GPIOSpeed_TypeDef GPIO_Speedx);
void PWM_Init(uint16_t percent);
void TIM_Init();
int main()
{
	SystemInit();
	GPIO_AFConfig(GPIOC,GPIO_Pin_13,GPIO_Speed_50MHz);
	GPIO_AFConfig(GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz); // chanel 1 TIM2
	TIM_Init();
	PWM_Init(10);
	while(1)
	{
	}
	
}
void GPIO_AFConfig(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,GPIOSpeed_TypeDef GPIO_Speedx)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speedx;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
	
}
// Use Timer2
void TIM_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimBaseInitStructure.TIM_Prescaler = 71;
	TIM_TimBaseInitStructure.TIM_Period = 1000-1; // 1 kHz pwm
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);
}
void PWM_Init(uint16_t percent)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;// Opposite with Pulse
	TIM_OCInitStructure.TIM_Pulse = 1000*percent/100 - 1;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
}
	
