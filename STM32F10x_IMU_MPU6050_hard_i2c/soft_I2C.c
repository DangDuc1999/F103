#include "soft_I2C.h"
#include "delay.h"



void soft_i2c_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef 		soft_i2c;
	soft_i2c.GPIO_Mode 	= GPIO_Mode_Out_PP;
	soft_i2c.GPIO_Pin	 		= SCL_I2C1_Pin|SDA_I2C1_Pin;
	soft_i2c.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&soft_i2c);
	
	SDA_H;
	SCL_H;
	
	
}
void soft_i2c_start(void){
	SCL_H;
	SDA_H;
	delay_TIM_us(3);
	SDA_L;
	delay_TIM_us(3);
	SCL_L;
	delay_TIM_us(3);
}
void soft_i2c_stop(void){
	SDA_L;
	delay_TIM_us(3);
	SCL_H;
	delay_TIM_us(3);
	SDA_H;
	delay_TIM_us(3);
}
void soft_i2c_ack(void);
void soft_i2c_nack(void);
uint8_t soft_i2c_send_single_byte( uint8_t data){
		
	uint8_t stt;
	for (int i = 0; i<8;i++){
		if (data & 0x80){
			SDA_H;
		}
		else SDA_L;
		
		data <<= 1;		// dich 1 bit data sang trai
		
		delay_TIM_us(3);		// sau khi truyen xong 1 bit, SCL duoc keo len muc cao
		SCL_H;
		delay_TIM_us(3);		// keo xuong muc thap (tao 1 xung clock di kem voi bit vua duoc gui)
		SCL_L;
		delay_TIM_us(3);
		
	}
	return(stt);
}
uint8_t soft_i2c_read_single_byte(void){

	uint8_t received_byte = 0;
	
		SDA_H;
		delay_TIM_us(3);
	
	for (int i =0; i<8;i++){
		received_byte <<=1;
		
		SCL_H;
		delay_TIM_us(3);
		
		if (SDA_VAL){
				received_byte |= 0x01;
		}
		
		delay_TIM_us(1);
		SCL_L;
		delay_TIM_us(3);
	
	}	
	
	return(received_byte);
}


void 	soft_i2c_make_ack(void){	//ack: sda o muc thap
		SCL_L;		delay_TIM_us(3);
		SDA_L;		delay_TIM_us(3);
		SCL_H;		delay_TIM_us(3);
		SCL_L;		delay_TIM_us(3);
}
void 	soft_i2c_make_nack(void){
	//nack: sda o muc cao
	SCL_L;		delay_TIM_us(3);
	SDA_H;	delay_TIM_us(3);
	SCL_H;		delay_TIM_us(3);
	SCL_L;		delay_TIM_us(3);
}
uint8_t soft_i2c_wait_ack(void){
	SCL_L;	delay_TIM_us(3);
	SDA_H; delay_TIM_us(3);
	SCL_H; delay_TIM_us(3);
	if(SDA_VAL){
		SCL_L;
		delay_TIM_us(3);
		return(0);
	}
	
		SCL_L;
		delay_TIM_us(3);
		return(1);
}




void soft_i2c_send_burst_bytes(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);
void soft_i2c_read_burst_bytes(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);


