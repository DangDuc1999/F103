#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"
void delay(uint32_t time);
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
	GPIO_Config(GPIOC,GPIO_Pin_13);
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay(1000);
	}
	
}
