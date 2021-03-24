#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef UART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
void Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	// Tx mode AF_PP, Rx mode Floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// Led config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	// Config UART
	UART_InitStructure.USART_BaudRate = 115200;
	UART_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART_InitStructure.USART_StopBits = USART_StopBits_1;
	UART_InitStructure.USART_Parity = USART_Parity_No;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&UART_InitStructure);
	
	// Xoa co Ngat UART
	USART_ClearFlag(USART2,USART_IT_RXNE);
	// cau hinh cho phep ngat nhan
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	// Cho phep UART hoat dong
	USART_Cmd(USART2,ENABLE);
}
void USART2_IRQHandler(void)
{
	uint16_t data;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)));
		data = USART_ReceiveData(USART2);
		if(USART_GetITStatus(USART2,USART_IT_TXE)== RESET)
			USART_SendData(USART2,data);
	}
}
int main()
{
	Config();
}