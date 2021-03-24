#include"stm32f10x.h"

void Delay_Tim_Init();
void Delay_Tms(uint32_t time2);
void Delay_Tus(uint32_t time1);
void GPIO_Config(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
}
int main()
{
	SystemInit();
	Delay_Tim_Init();
	GPIO_Config(GPIOC,GPIO_Pin_13);
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay_Tms(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay_Tms(1000);
	}
	
}
//Delay with Timmer 4
void Delay_Tim_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseInitTypeDef Tim_InitStructure;
	Tim_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_InitStructure.TIM_Prescaler = 71;
	Tim_InitStructure.TIM_Period = 1000-1; // 1ms
	Tim_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&Tim_InitStructure);
	TIM_Cmd(TIM4,ENABLE);
	
}
void Delay_TIM_unit(void)
{
	TIM_SetCounter(TIM4,0);
	while( TIM_GetCounter(TIM4) > 1000);
}
void Delay_Tus(uint32_t time1)
{
	while(time1--)
	{
		Delay_TIM_unit();
	}
}
void Delay_Tms(uint32_t time2)
{
	while(time2--)
	{
		Delay_Tus(1000);
	}
}
