#include "Delay.h"
__IO uint32_t time_delay;

// Delay systick
void Delay_us(uint32_t time){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000000);	// 1ms
	time_delay=time;
	// Systick_Handler run ultil time_delay = 0
	while(time_delay!=0);
}
void Delay(uint32_t time){
	uint32_t i;
	for(i = 0; i < time ;i++)
	{
		Delay_us(1000);
	}
}

void SysTick_Handler(void){
	time_delay--;
}
	
// Delay with timer 4
void TIM4Delay_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseInitTypeDef Tim_InitStructure;
	Tim_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_InitStructure.TIM_Prescaler = 71;
	Tim_InitStructure.TIM_Period = 0xFFFF;
	Tim_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&Tim_InitStructure);
	TIM_Cmd(TIM4,ENABLE);
	
}
void Delay_1Ms()
{
	TIM_SetCounter(TIM4,0);
	while(TIM_GetCounter(TIM4)<1000){
	}
	
}
void Delay_Ms(uint32_t time)
{
	while(time){
		Delay_1Ms();
		time--;
	}
	
}
