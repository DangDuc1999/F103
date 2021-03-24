#include "main.h"
void Delay(uint32_t time);
int main()
{	
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &gpioInit);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	while(1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay(1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay(1000);
		
	}
}

void Delay(uint32_t time)
{
	/* T = 1/f = 1/72000000
				72000 <= 1/1000 s
	*/
	SysTick ->LOAD = 72U*1000U-1U;
	SysTick ->VAL = 0U; // Value = 0
	SysTick ->CTRL = 5U; // 
	while(!(SysTick->CTRL & (1U<<16U)))
	{
		// waiting for return 1 if timer counted to 0 since last time this  was read
	}
	--time;
}
