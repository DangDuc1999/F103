#include "i2c_function.h"

// Hardware IIC

uint8_t 	i2c_single_Write( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr, uint8_t data){

		I2C_GenerateSTART( I2Cx,ENABLE);
		while ( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
		I2C_Send7bitAddress(I2Cx, Device_Addr, I2C_Direction_Transmitter);
		while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
		I2C_SendData(I2Cx,Reg_Addr);
		while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
		I2C_SendData(I2Cx,data);
		while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
		I2C_GenerateSTOP(I2Cx,ENABLE);	
	
	return(0);
		
}


uint8_t 	i2c_single_Read( I2C_TypeDef* I2Cx, uint8_t Device_Addr, uint8_t Reg_Addr){
		uint8_t receive_data;
		while  (I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY));
	
		I2C_GenerateSTART(I2Cx,ENABLE);
		while ( !I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
	
		I2C_Send7bitAddress(I2Cx,Device_Addr,I2C_Direction_Transmitter);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
		I2C_SendData(I2Cx,Reg_Addr);
		while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	
		I2C_GenerateSTART(I2Cx,ENABLE);
		while ( !I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
	
		I2C_Send7bitAddress(I2Cx,Device_Addr,I2C_Direction_Receiver);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
		I2C_AcknowledgeConfig(I2Cx,DISABLE);
		I2C_GenerateSTOP(I2Cx,ENABLE);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));
		
		
		receive_data = I2C_ReceiveData(I2Cx);
		return(receive_data);
}



