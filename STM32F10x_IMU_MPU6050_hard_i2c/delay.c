#include "delay.h"
#include "stm32f10x_tim.h"

//delay tuong doi
uint32_t tick;
uint16_t time_delay;


void delay_ms(uint32_t time){
	tick = time*3600;
	while(tick--){
	}
}

void delay_us(uint32_t time){
	tick = time*3.6;
	while(tick--){
	}
}




// delay voi Timer4
void delay_TIM_Init(void){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
		TIM_TimeBaseInitTypeDef 				delay_TIM;
		delay_TIM.TIM_ClockDivision			=	 TIM_CKD_DIV1;
		delay_TIM.TIM_CounterMode 			=	 TIM_CounterMode_Up;
		delay_TIM.TIM_Period					= 	 65535;			// Gia tri bo dem cua timer
		delay_TIM.TIM_Prescaler				= 	 71;				// bo chia tan, f_CNT = f_Sys/(Prescaler+1) => f_CNT = 1000000 ~ T = 1us
		delay_TIM.TIM_RepetitionCounter	= 0 ;
	
		TIM_TimeBaseInit(TIM4,&delay_TIM);
		TIM_Cmd(TIM4,ENABLE);
	

}

void delay_TIM_us(uint32_t time){
	TIM_SetCounter(TIM4,0);
	while( TIM_GetCounter(TIM4) < time);
}
void delay_TIM_1ms(void){
	TIM_SetCounter(TIM4,0);
	while( TIM_GetCounter(TIM4) < 1000);
}
void delay_TIM_ms(uint32_t time){

	while(time--){
		delay_TIM_1ms();
	}

}


//delay voi Systick
void delay_Sys_Init(void){
	SystemCoreClockUpdate();
	//SysTick_Config(SystemCoreClock/1000); //1ms interrupt
	SysTick_Config(SystemCoreClock/1000000); //1us interrupt
}
void delay_Sys_ms(uint32_t time){
	while(time--){
		delay_Sys_us(1000);	//  delay 1ms
	}

}
void delay_Sys_us(uint32_t time){
	time_delay=time;
	while(time_delay!=0);
}

void SysTick_Handler(void){
	time_delay--;
}

