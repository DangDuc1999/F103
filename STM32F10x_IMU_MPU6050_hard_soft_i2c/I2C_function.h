#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"


// doc 1 byte
uint8_t 	i2c_single_Read( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr);

// doc nhieu byte
uint8_t 	i2c_burst_Read( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);

// ghi 1 byte
uint8_t 	i2c_single_Write( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t data);

// ghi nhieu byte
uint8_t 	i2c_burst_Write( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t* data, uint8_t num_bytes);






