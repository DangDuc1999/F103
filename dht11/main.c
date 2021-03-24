#include"stm32f10x.h"
#include"..\1.Lib\Delay.h"

void GPIO_Config(GPIO_TypeDef * GPIOx,GPIOMode_TypeDef GPIO_mode,uint16_t GPIO_Pin_x)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_mode;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
	
}
	

int main()
{
	uint16_t data, u16Tim;
	uint8_t u8Buff[5];
	uint8_t i;
	uint8_t checkSum;
	GPIO_Config(GPIOB,GPIO_Mode_AF_OD,GPIO_Pin_12);
	GPIO_Config(GPIOC,GPIO_Mode_AF_PP,GPIO_Pin_13);
	
	while(1)
	{
		// Send Start
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_Ms(20);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		
		// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<45){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
	if((u16Tim >= 45) || (u16Tim < 5)){
		while(1){}
	}
	
	// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<90){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 90) || (u16Tim < 70)){
		while(1){}
		}
	
		// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<95){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 95) || (u16Tim < 75)){
		while(1){}
		}
		// Nhan byte so 1
		for(i = 0;i <8;i++){
			// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<65){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 65) || (u16Tim < 45)){
		while(1){}
		}
				// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<80){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 80) || (u16Tim < 10)){
		while(1){}
		}
			u8Buff[0] <<= 1 ;
		if(u16Tim >45){
			// nhan duoc bit 1
			u8Buff[0] |= 1;
		}
		else{
			// Nhan duoc bit 0
			u8Buff[0] &= -1;
		}
		}
		
		// Nhan byte so 2
		for(i = 0;i <8;i++){
			// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<65){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 65) || (u16Tim < 45)){
		while(1){}
		}
				// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<80){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 80) || (u16Tim < 10)){
		while(1){}
		}
			u8Buff[1] <<= 1 ;
		if(u16Tim >45){
			// nhan duoc bit 1
			u8Buff[1] |= 1;
		}
		else{
			// Nhan duoc bit 0
			u8Buff[1] &= -1;
		}
		}
		
		// Nhan byte so 3
		for(i = 0;i <8;i++){
			// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<65){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 65) || (u16Tim < 45)){
		while(1){}
		}
				// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<80){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 80) || (u16Tim < 10)){
		while(1){}
		}
			u8Buff[2] <<= 1 ;
		if(u16Tim >45){
			// nhan duoc bit 1
			u8Buff[2] |= 1;
		}
		else{
			// Nhan duoc bit 0
			u8Buff[2] &= -1;
		}
		}
		
		// Nhan byte so 4
		for(i = 0;i <8;i++){
			// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<65){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 65) || (u16Tim < 45)){
		while(1){}
		}
				// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<80){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 80) || (u16Tim < 10)){
		while(1){}
		}
			u8Buff[3] <<= 1 ;
		if(u16Tim >45){
			// nhan duoc bit 1
			u8Buff[3] |= 1;
		}
		else{
			// Nhan duoc bit 0
			u8Buff[3] &= -1;
		}
		}
		
		// Nhan byte so 5
		for(i = 0;i <8;i++){
			// Cho PB12 len cao
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<65){
			
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 65) || (u16Tim < 45)){
		while(1){}
		}
				// Cho PB12 xuong thap
		TIM_SetCounter(TIM4,0);
		while(TIM_GetCounter(TIM4)<80){
			
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)){
			break;
		}
	}
		u16Tim = TIM_GetCounter(TIM4);
			if((u16Tim >= 80) || (u16Tim < 10)){
		while(1){}
		}
			u8Buff[4] <<= 1 ;
		if(u16Tim >45){
			// nhan duoc bit 1
			u8Buff[4] |= 1;
		}
		else{
			// Nhan duoc bit 0
			u8Buff[4] &= -1;
		}
		}
		checkSum = u8Buff[0] + u8Buff[1] + u8Buff[2]+ u8Buff[3];
		if(checkSum != u8Buff[4]){
			while(1){}
		}
		// Da doc duoc nhiet do
		
	}
}