#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define 	SCL_I2C1_Pin						GPIO_Pin_6		// scl in output mode
#define		SDA_I2C1_Pin						GPIO_Pin_7		// sda must have both in and out

#define		I2C1_port								GPIOB

#define 	SCL_H				GPIOB->BSRR = GPIO_Pin_6
#define 	SCL_L				GPIOB->BRR = 	GPIO_Pin_6

#define 	SDA_H				GPIOB->BSRR = GPIO_Pin_7
#define 	SDA_L				GPIOB->BRR = 	GPIO_Pin_7
#define 	SDA_VAL			GPIOB->IDR & GPIO_Pin_7

#define 	Transmit			0x00
#define 	Receive				0x01

void soft_i2c_Init(void);
void soft_i2c_start(void);
void soft_i2c_stop(void);

void 	soft_i2c_make_ack(void);
void 	soft_i2c_make_nack(void);
uint8_t soft_i2c_wait_ack(void);



void soft_i2c_send_single_byte(uint8_t data);	// send 1 byte don thuan
uint8_t soft_i2c_read_single_byte(void);				// doc 1 byte don thuan

void soft_i2c_send_burst_bytes(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);
void soft_i2c_read_burst_bytes(uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);

void soft_i2c_send_7bit_addr(uint8_t Device_Addr, uint8_t dirrection);
void soft_i2c_single_write( uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t data);		// send 1 byte den 1 dia chi, 1 thanh ghi
uint8_t soft_i2c_single_read(uint8_t Device_Addr, uint8_t Reg_Addr);							// doc 1 byte tu 1 dia chi, 1 thanh ghi


