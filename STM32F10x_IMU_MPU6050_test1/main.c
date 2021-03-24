#include "stm32f10x.h"
#include "IMU.h"
#include "i2c_function.h"
#include "delay.h"

extern uint8_t received_data[14];
extern float accel_x, accel_y, accel_z, gyro_x, gyro_y,gyro_z;
extern float temp;
extern uint16_t data_x[2], data_y[2],  data_z[2];
int i=10000;

//cau hinh led test o chan PA4
void led_Init(void){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
		GPIO_InitTypeDef  led_Struct;
		led_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
		led_Struct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_15;
		led_Struct.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOA,&led_Struct);
	
	
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


int main(){
		SystemCoreClockUpdate();
		SystemInit();
		led_Init();
	//IMU_I2C1_Init();
		while(1){

//				IMU_get_accel();
//				IMU_get_gyro();
//				IMU_get_temp();
				GPIO_SetBits(GPIOA,GPIO_Pin_15);
				delay_ms(100);
				GPIO_ResetBits(GPIOA,GPIO_Pin_15);
				delay_ms(100);


		}

}

