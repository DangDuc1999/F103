#include "stm32f10x.h"
#include "IMU.h"
#include "i2c_function.h"
#include "delay.h"
#include "soft_I2C.h"

extern uint8_t received_data[14];
extern float accel_x, accel_y, accel_z, gyro_x, gyro_y,gyro_z;
extern float temp;
extern uint16_t data_x[2], data_y[2],  data_z[2];
extern float off_set_ax, off_set_ay, off_set_az;
extern float off_set_gx, off_set_gy, off_set_gz;

//cau hinh led test o chan PA4
void led_Init(void){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitTypeDef  led_Struct;
		led_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
		led_Struct.GPIO_Pin = GPIO_Pin_4;
		led_Struct.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOA,&led_Struct);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


int main(){

		SystemInit();
		led_Init();
		delay_TIM_Init();
		soft_i2c_Init();
	
		while(1){
			
			IMU_soft_i2c_get_temp();
			IMU_soft_I2C_get_accel();
			IMU_soft_I2C_get_gyro();
			delay_TIM_us(2);
			
			
		}

}

