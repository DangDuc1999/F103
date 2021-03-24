#ifndef _IMU_H_
#define _IMU_H_

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "i2c_function.h"

/*								SCL			SDA
			I2C1				PB6			PB7
								PB8			PB9
			
			I2C2				PB10		PB11


*/
#define 		SCL_I2C1_Pin						GPIO_Pin_6
#define		SDA_I2C1_Pin						GPIO_Pin_7

#define		I2C1_port								GPIOB

#define 		IMU_default_Address					0xD0		//0x68 la dia chi 7 bit, con khi ghi vao se ghi 8 bit nen la 0xD0
#define 		IMU_soft_I2C_default_Address	0x68	
	
// sefl test Register
// Type: R/W
#define  	IMU_XA_TEST 						0x0D
#define 		IMU_YA_TEST						0x0E
#define 		IMU_ZA_TEST						0x0
#define 		IMU_RESERVED					0x10

// Sample rate Divider Register
// Type: R/W
#define 		IMU_SMPLRT_DIV				0x19
#define 		IMU_SMPLRT_DIV_1KHz		0x07 	// sample rate 1khz



// Configuration Register
// Type: R/W
#define 		IMU_CONFIG						0x1A		// bit[7:6] : reserved		bit[5:3]: EXT_SYNC_SET[2:0]  	bit[2:0]: DLPF_CFG[2:0] 
/** Get digital low-pass filter configuration.
 * The DLPF_CFG parameter sets the digital low pass filter configuration. It
 * also determines the internal sampling rate used by the device as shown in
 * the table below.
 *
 * Note: The accelerometer output rate is 1kHz. This means that for a Sample
 * Rate greater than 1kHz, the same accelerometer sample may be output to the
 * FIFO, DMP, and sensor registers more than once.
 *
 * <pre>
 *         		  ACCELEROMETER    |           GYROSCOPE
 * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
 * ---------+-----------+--------+-----------+--------+-------------
 * 0      			 | 260Hz     | 0ms      | 256Hz     | 0.98ms  | 8kHz
 * 1        		 | 184Hz     | 2.0ms   | 188Hz     | 1.9ms    | 1kHz
 * 2        		 | 94Hz       | 3.0ms   | 98Hz       | 2.8ms   | 1kHz
 * 3        		 | 44Hz       | 4.9ms   | 42Hz       | 4.8ms   | 1kHz
 * 4        		 | 21Hz       | 8.5ms   | 20Hz       | 8.3ms   | 1kHz
 * 5        		 | 10Hz       | 13.8ms | 10Hz       | 13.4ms  | 1kHz
 * 6        		 | 5Hz         | 19.0ms | 5Hz         | 18.6ms  | 1kHz
 * 7        		 |   -- Reserved --   	   |   -- Reserved --        | Reserved
 **/

#define		IMU_CONFIG_0						0x00
#define		IMU_CONFIG_1						0x01
#define		IMU_CONFIG_2						0x02
#define		IMU_CONFIG_3						0x03
#define		IMU_CONFIG_4						0x04
#define		IMU_CONFIG_5						0x05
#define		IMU_CONFIG_6						0x06


// Gyro Config Res
// Type: R/W
#define 		IMU_GYRO_CONFIG				0x1B

//accel config
// rw
#define 		IMU_ACCEL_CONFIG			0x1C

//FIFO enable
// rw
#define 		IMU_FIFO_EN						0x23


// master control
// rw
#define 		IMU_I2C_MST_CTRL				0x24


//offfset Reg
#define 		IMU_OFFSET_GYRO_X_H		0x13
#define 		IMU_OFFSET_GYRO_X_L		0x14
#define 		IMU_OFFSET_GYRO_Y_H	0x15
#define 		IMU_OFFSET_GYRO_Y_L		0x16
#define 		IMU_OFFSET_GYRO_Z_H		0x17
#define 		IMU_OFFSET_GYRO_Z_L		0x18


#define 		IMU_OFFSET_ACCEL_X_H	0x06
#define 		IMU_OFFSET_ACCEL_X_L	0x07
#define 		IMU_OFFSET_ACCEL_Y_H	0x08
#define 		IMU_OFFSET_ACCEL_Y_L	0x09
#define 		IMU_OFFSET_ACCEL_Z_H	0x0A
#define 		IMU_OFFSET_ACCEL_Z_L	0x0B


// i2c slave control
// rw
#define 		IMU_I2C_SLV0_ADDR			0x25
#define 		IMU_I2C_SLV0_REG				0x26
#define 		IMU_I2C_SLV0_CTRL			0x27

#define 		IMU_I2C_SLV1_ADDR			0x28
#define 		IMU_I2C_SLV1_REG				0x29
#define 		IMU_I2C_SLV1_CTRL			0x2A

#define 		IMU_I2C_SLV2_ADDR			0x2B
#define 		IMU_I2C_SLV2_REG				0x2C
#define 		IMU_I2C_SLV2_CTRL			0x2D

#define 		IMU_I2C_SLV3_ADDR			0x2E
#define 		IMU_I2C_SLV3_REG				0x2F
#define 		IMU_I2C_SLV3_CTRL			0x30

#define 		IMU_I2C_SLV4_ADDR			0x31
#define 		IMU_I2C_SLV4_REG				0x32
#define 		IMU_I2C_SLV4_DO				0x33
#define 		IMU_I2C_SLV4_CTRL			0x34
#define 		IMU_I2C_SLV4_DI					0x35

// master stt
#define 		IMU_I2C_MST_STT				0x36

//int pin, bypass enable confirguration
#define 		IMU_INT_PIN_CFG				0x37

// interrupt enable
#define 		IMU_INT_EN							0x38

//int stt - read only
#define 		IMU_INT_STT						0x3A

// Accel measurements
#define 		IMU_ACCEL_XOUT_H			0x3B
#define 		IMU_ACCEL_XOUT_L			0x3C
#define 		IMU_ACCEL_YOUT_H			0x3D
#define 		IMU_ACCEL_YOUT_L			0x3E
#define 		IMU_ACCEL_ZOUT_H			0x3F
#define 		IMU_ACCEL_ZOUT_L			0x40

//temprature 
#define 		IMU_TMP_OUT_H					0x41
#define 		IMU_TMP_OUT_L					0x42

//gyro measurements
#define 		IMU_GYRO_XOUT_H				0x43
#define 		IMU_GYRO_XOUT_L				0x44
#define 		IMU_GYRO_YOUT_H			0x45
#define 		IMU_GYRO_YOUT_L				0x46
#define 		IMU_GYRO_ZOUT_H				0x47
#define 		IMU_GYRO_ZOUT_L				0x48

//external sensor data
#define 		IMU_EXT_SENS_DATA_00		0x49
#define 		IMU_EXT_SENS_DATA_01		0x4A
#define 		IMU_EXT_SENS_DATA_02		0x4B
#define 		IMU_EXT_SENS_DATA_03		0x4C
#define 		IMU_EXT_SENS_DATA_04		0x4D
#define 		IMU_EXT_SENS_DATA_05		0x4E
#define 		IMU_EXT_SENS_DATA_06		0x4F
#define 		IMU_EXT_SENS_DATA_07		0x50
#define 		IMU_EXT_SENS_DATA_08		0x51
#define 		IMU_EXT_SENS_DATA_09		0x52
#define 		IMU_EXT_SENS_DATA_10		0x53
#define 		IMU_EXT_SENS_DATA_11		0x54
#define 		IMU_EXT_SENS_DATA_12		0x55
#define 		IMU_EXT_SENS_DATA_13		0x56
#define 		IMU_EXT_SENS_DATA_14		0x57
#define 		IMU_EXT_SENS_DATA_15		0x58
#define 		IMU_EXT_SENS_DATA_16		0x59
#define 		IMU_EXT_SENS_DATA_17		0x5A
#define 		IMU_EXT_SENS_DATA_18		0x5B
#define 		IMU_EXT_SENS_DATA_19		0x5C
#define 		IMU_EXT_SENS_DATA_20		0x5D
#define 		IMU_EXT_SENS_DATA_21		0x5E
#define 		IMU_EXT_SENS_DATA_22		0x5F
#define 		IMU_EXT_SENS_DATA_23		0x60

//i2c slave data out
#define 		IMU_I2C_SLV0_DO					0x63
#define 		IMU_I2C_SLV1_DO					0x64
#define 		IMU_I2C_SLV2_DO					0x65
#define 		IMU_I2C_SLV3_DO					0x66

//i2c master delay
#define 		IMU_MST_DELAY_CTRL			0x67

//signal path reset
#define 		IMU_SIGNAL_PATH_RST			0x68

//user control
#define 		IMU_USER_CTRL						0x6A

//power managements
#define		IMU_PWR_MGMT_1					0x6B
#define 		IMU_PWR_MGMT_2					0x6C
#define 		IMU_PW_MGMT_Internal_8MHz			0x00
// Bit7				|	Bit6		|	Bit5		|	Bit4		|	Bit3			 |	Bit2			Bit1			Bit0 |
//DEVICE_RST	|	SLEEP	|	CYCLE	|	-			|	TEMP_DIS |	-----CLKSEL[2:0]-------------- |
/** Set clock source setting.
 * An internal 8MHz oscillator, gyroscope based clock, or external sources can
 * be selected as the MPU-60X0 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-60X0 can operate
 * in low power modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-60X0 clock source defaults to the internal oscillator.
 * However, it is highly recommended that the device be configured to use one of
 * the gyroscopes (or an external clock source) as the clock reference for
 * improved stability. The clock source can be selected according to the following table:
 *
 * <pre>
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal 8MHz oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset

 */

//FIFO count
#define 		IMU_FIFO_COUNT_H				0x72
#define 		IMU_FIFO_COUNT_L					0x73

//FIFO read/write
#define 		IMU_FIFO_R_W						0x74

//who am I
#define 		IMU_WHO_AM_I						0x75

/* Gyro sensitivities in ?бу/s */
#define 		IMU_GYRO_SENS_250				((float) 131)
#define 		IMU_GYRO_SENS_500				((float) 65.5)
#define 		IMU_GYRO_SENS_1000			((float) 32.8)
#define 		IMU_GYRO_SENS_2000			((float) 16.4)

/* Acce sensitivities in g */
#define		IMU_ACCEL_SENS_2				((float) 16384)
#define 		IMU_ACCEL_SENS_4				((float) 8192)
#define 		IMU_ACCEL_SENS_8				((float) 4096)
#define 		IMU_ACCEL_SENS_16				((float) 2048)

// mpu6050 co 2 dia chi slave, co the su dung 2 cam bien mpu cung 1 luc. Dia chi duoc cau hinh phu thuoc vao chan AD0
#define		IMU_Device_1	 					0			//AD0 LOW
#define 		IMU_Device_2						0x02 		//AD0 HIGH

// gyro scale
#define 		IMU_GYRO_SCALE_250		0x00
#define		IMU_GYRO_SCALE_500		0x08
#define		IMU_GYRO_SCALE_1000		0x10
#define		IMU_GYRO_SCALE_2000		0x18

// accel scale
#define		IMU_ACCEL_SCALE_2G		0x00
#define 		IMU_ACCEL_SCALE_4G		0x08
#define 		IMU_ACCEL_SCALE_8G		0x10
#define		IMU_ACCEL_SCALE_16G		0x18

//FIFO ENABLE
#define 		IMU_FIFO_EN_TEMP_GYRO_ACCEL	0xF8

//hard i2c
void IMU_I2C1_Init(void);
void IMU_get_temp(void);
float  IMU_get_accel_X(void);
float IMU_get_accel_Y(void);
float  IMU_get_accel_Z(void);
float IMU_get_gyro_X(void);
float  IMU_get_gyro_Y(void);
float IMU_get_gyro_Z(void);
void IMU_get_accel(void);
void IMU_get_gyro(void);
void IMU_calculate_offset(void);



//soft i2c
void IMU_soft_i2c_get_temp(void);
float  IMU_soft_I2C_get_accel_X(void);
float IMU_soft_I2C_get_accel_Y(void);
float  IMU_soft_I2C_get_accel_Z(void);
float IMU_soft_I2C_get_gyro_X(void);
float  IMU_soft_I2C_get_gyro_Y(void);
float IMU_soft_I2C_get_gyro_Z(void);
void IMU_soft_I2C_get_accel(void);
void IMU_soft_I2C_get_gyro(void);
void IMU_soft_I2C_calculate_offset(void);
void IMU_soft_I2C_calculate_offset(void);
void IMU_soft_I2C_get_gyro(void);
void IMU_soft_I2C_get_accel(void);



#endif


