#include "IMU.h"
#include "delay.h"

#define 	I2C_OwnAddr	0x00		//default 
uint8_t received_data[14];
float accel_x, accel_y, accel_z, gyro_x, gyro_y,gyro_z;
float temp;
int16_t data_x[2], data_y[2],  data_z[2];

void IMU_I2C1_Init(void){
		//clock
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //clock port gpio I2c1
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE); // clock i2c1
	
		//gpio config mode af
		GPIO_InitTypeDef  IMU_GPIO_Struct;
		IMU_GPIO_Struct.GPIO_Mode 	= GPIO_Mode_AF_OD;
		IMU_GPIO_Struct.GPIO_Pin 		= SCL_I2C1_Pin|SDA_I2C1_Pin;
		IMU_GPIO_Struct.GPIO_Speed 	= GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&IMU_GPIO_Struct);
	
		//config i2c
		I2C_InitTypeDef 	IMU_I2C1_Struct;
		IMU_I2C1_Struct.I2C_Mode							= I2C_Mode_I2C;
		IMU_I2C1_Struct.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
		IMU_I2C1_Struct.I2C_Ack 								= I2C_Ack_Enable;
		IMU_I2C1_Struct.I2C_ClockSpeed					= 100000;
		IMU_I2C1_Struct.I2C_DutyCycle						= I2C_DutyCycle_2;
		IMU_I2C1_Struct.I2C_OwnAddress1  				= I2C_OwnAddr;
		I2C_Init(I2C1,&IMU_I2C1_Struct);
		
		//enable module
		I2C_Cmd(I2C1,ENABLE);
		
		

		i2c_single_Write(I2C1,IMU_default_Address,IMU_PWR_MGMT_1,IMU_PW_MGMT_Internal_8MHz);
		delay_us(5);

		i2c_single_Write(I2C1,IMU_default_Address, IMU_SMPLRT_DIV, IMU_SMPLRT_DIV_1KHz);	//Sample Rate  = Gyro Output Rate(8Khz) /(1+SMPRLT_DIV) 0x07 <=> SMPRLT_DIV=1 -> SampleRate = 1Khz
		delay_us(5);
		
		i2c_single_Write(I2C1,IMU_default_Address,IMU_CONFIG,IMU_CONFIG_6);			
		delay_us(5);
		
		i2c_single_Write(I2C1,IMU_default_Address,IMU_ACCEL_CONFIG,IMU_ACCEL_SCALE_8G);
		delay_us(5);

		i2c_single_Write(I2C1,IMU_default_Address,IMU_GYRO_CONFIG,IMU_GYRO_SCALE_500);
		delay_us(5);
		
		i2c_single_Write(I2C1,IMU_default_Address,IMU_FIFO_EN,IMU_FIFO_EN_TEMP_GYRO_ACCEL);		//enable FIFO 
		delay_us(5);
		
}


void IMU_get_temp(void){
		received_data[12] = i2c_single_Read(I2C1,IMU_default_Address,IMU_TMP_OUT_H);
		received_data[13] = i2c_single_Read(I2C1,IMU_default_Address,IMU_TMP_OUT_L);
		temp = (int16_t) ((received_data[12]<<8|received_data[13]));
		temp = (float) temp/(340.00)+36.53;
}

void IMU_get_accel_X(void){
					received_data[0] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_XOUT_H);
					received_data[1] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_XOUT_L);
					data_x[0] =(int16_t)  ((received_data[0] <<8| received_data[1]) );
					accel_x = data_x[0]/IMU_ACCEL_SENS_8;
					
}
void IMU_get_accel_Y(void){
					received_data[2] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_YOUT_H);
					received_data[3] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_YOUT_L);
					data_y[0] =(int16_t)  ((received_data[2] <<8| received_data[3]) );		
					accel_y = data_y[0]/IMU_ACCEL_SENS_8;

}
void IMU_get_accel_Z(void){
					received_data[4] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_ZOUT_H);
					received_data[5] = i2c_single_Read(I2C1,IMU_default_Address,IMU_ACCEL_ZOUT_L);
					data_z[0] =(int16_t)  ((received_data[4] <<8| received_data[5]) );
					accel_z = data_z[0]/IMU_ACCEL_SENS_8;

}
void IMU_get_gyro_X(void){
					received_data[6] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_XOUT_H);
					received_data[7] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_XOUT_L);
					data_x[1] =(int16_t)  ((received_data[6] <<8| received_data[7]) );
					gyro_x = data_x[1] / IMU_GYRO_SENS_500;
	
				

}
void IMU_get_gyro_Y(void){
					received_data[8] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_YOUT_H);
					received_data[9] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_YOUT_L);
					data_y[1] =(int16_t)  ((received_data[8] <<8| received_data[9]) );
					gyro_y = data_y[1] / IMU_GYRO_SENS_500;

}
void IMU_get_gyro_Z(void){
					received_data[10] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_ZOUT_H);
					received_data[11] = i2c_single_Read(I2C1,IMU_default_Address,IMU_GYRO_ZOUT_L);
					data_z[1] =(int16_t)  ((received_data[10] <<8| received_data[11]) );
					gyro_z = data_z[1] / IMU_GYRO_SENS_500;
				

}


void IMU_get_accel(void){
		IMU_get_accel_X();
		IMU_get_accel_Y();
		IMU_get_accel_Z();
}


void IMU_get_gyro(void){
		IMU_get_gyro_X();
		IMU_get_gyro_Y();
		IMU_get_gyro_Z();
}


