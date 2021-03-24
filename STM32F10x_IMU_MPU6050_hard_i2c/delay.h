#include "stm32f10x.h"
//ham delay 1 cach tuong doi
void delay_ms(uint32_t time);
void delay_us(uint32_t time);

// delay voi  Timer4
void delay_TIM_us(uint32_t time);
void delay_TIM_1ms(void);
void delay_TIM_ms(uint32_t time);
void delay_TIM_Init(void);

//delay voi Systick
void delay_Sys_Init(void);
void delay_Sys_ms(uint32_t time);
void delay_Sys_us(uint32_t time);
void SysTick_Handler(void);


