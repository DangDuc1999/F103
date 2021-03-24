#include "soft_I2C.h"
#include "delay.h"
#include "IMU.h"



void soft_i2c_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef 		soft_i2c;
	soft_i2c.GPIO_Mode 	= GPIO_Mode_Out_OD;
	soft_i2c.GPIO_Pin	 		= SCL_I2C1_Pin|SDA_I2C1_Pin;
	soft_i2c.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&soft_i2c);
	
	SDA_H;
	SCL_H;
	
	
		soft_i2c_single_write(IMU_soft_I2C_default_Address,IMU_PWR_MGMT_1,IMU_PW_MGMT_Internal_8MHz);
		delay_us(3);
		
		soft_i2c_single_write(IMU_soft_I2C_default_Address, IMU_SMPLRT_DIV, IMU_SMPLRT_DIV_1KHz);	//Sample Rate  = Gyro Output Rate(8Khz) /(1+SMPRLT_DIV) 0x07 <=> SMPRLT_DIV=1 -> SampleRate = 1Khz
		delay_us(3);
		
		soft_i2c_single_write(IMU_soft_I2C_default_Address,IMU_CONFIG,IMU_CONFIG_6);			
		delay_us(3);
		
		soft_i2c_single_write(IMU_soft_I2C_default_Address,IMU_ACCEL_CONFIG,IMU_ACCEL_SCALE_8G);
		delay_us(3);
		
		soft_i2c_single_write(IMU_soft_I2C_default_Address,IMU_GYRO_CONFIG,IMU_GYRO_SCALE_500);
		delay_us(3);
		
		IMU_soft_I2C_calculate_offset();
	
}
void soft_i2c_start(void){
	SCL_H;
	delay_TIM_us(3);
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


void soft_i2c_send_single_byte( uint8_t data){
	
	for (int i = 0; i<8;i++){
		if (data & 0x80){  //0x80 = 10000000
			SDA_H;
			
		}
		
		else {
			SDA_L;

		}
		delay_TIM_us(3);
		data <<= 1;		// dich 1 bit data sang trai
		
		delay_TIM_us(3);		// sau khi truyen xong 1 bit, SCL duoc keo len muc cao
		SCL_H;
		delay_TIM_us(5);		// keo xuong muc thap (tao 1 xung clock di kem voi bit vua duoc gui)
		SCL_L;
		delay_TIM_us(3);
		
	}
	

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
		
		delay_TIM_us(3);
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
	
	delay_TIM_us(3);
	SCL_H; 
	delay_TIM_us(2);
	if(SDA_VAL){
		SCL_L;
		delay_TIM_us(3);
		return(0);
	}
	
	else{
	
		SCL_L;
		delay_TIM_us(3);
		return(1);
	}
	
}


void soft_i2c_send_7bit_addr(uint8_t Device_Addr, uint8_t dirrection){
	if (dirrection){
			soft_i2c_send_single_byte( Device_Addr <<1 | dirrection);
	}
	
	else {
			soft_i2c_send_single_byte( Device_Addr <<1 | dirrection);
	}

}

void soft_i2c_single_write( uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t data){
		// send 1 byte den 1 dia chi, 1 thanh ghi
		soft_i2c_start();
		soft_i2c_send_7bit_addr(IMU_soft_I2C_default_Address,Transmit);
		while (!soft_i2c_wait_ack());
		soft_i2c_send_single_byte(Reg_Addr);
		while (!soft_i2c_wait_ack());
		soft_i2c_send_single_byte(data);
		while (!soft_i2c_wait_ack());
		soft_i2c_stop();

}	
uint8_t soft_i2c_single_read(uint8_t Device_Addr, uint8_t Reg_Addr){
			// doc 1 byte tu 1 dia chi, 1 thanh ghi
		uint8_t received_data;
		soft_i2c_start();
	
		soft_i2c_send_7bit_addr(IMU_soft_I2C_default_Address,Transmit);
		while (!soft_i2c_wait_ack());
		soft_i2c_send_single_byte(Reg_Addr);
		while (!soft_i2c_wait_ack());
		soft_i2c_start();
		soft_i2c_send_7bit_addr(IMU_soft_I2C_default_Address,Receive);
	
		while (!soft_i2c_wait_ack());
	
		received_data = soft_i2c_read_single_byte();
	
		soft_i2c_make_nack();
		soft_i2c_stop();
	
		return(received_data);
}				




