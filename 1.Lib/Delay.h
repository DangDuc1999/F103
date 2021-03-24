#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "Delay.c"
// Delay systick
void Delay_us(uint32_t time);
void Delay(uint32_t time);
void SysTick_Handler(void);
// Delay Timer4
void TIM4Delay_Init();
void Delay_Ms(uint32_t time);
void Delay_1Ms();
#endif
