#include "stm32f10x.h"
#include "..\1.Lib\Delay.h"

void I2C_LCD_Config();
void lcd_Write_byte(char data);
void lcd_Control_Write(char data);
void LCD_Init();
void LCD_Send_String(char* data);
#define PCF8574A_Address 0x27

int main()
{
	I2C_LCD_Config();
	LCD_Init();
	LCD_Send_String("I am Iron man");
}
void I2C_LCD_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	// Clock I2C and Peripheral
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	// Config SDA & SCL
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	// Config I2C
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Init(I2C2,&I2C_InitStructure);
	// Bat bo I2C
	I2C_Cmd(I2C2,ENABLE);
}

void lcd_Write_byte(char data)
{
	// Send Start Conditional
	I2C_GenerateSTART(I2C2, ENABLE);
	// Test on EV5 and clear it
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
	// Send PCF8574A address for write
	I2C_Send7bitAddress(I2C2,PCF8574A_Address,I2C_Direction_Transmitter);
	// Test on EV6 and clear it
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	// Send the byte to be written
	I2C_SendData(I2C2,data);
	// Test on EV8 and clear it
	while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	// Send STOP condition
	I2C_GenerateSTOP(I2C2, ENABLE);

}

void LCD_Init()
{
	// Set 4 bits interface
	lcd_Control_Write(0x33);
	Delay(10);
	lcd_Control_Write(0x32);
	Delay(50);
	// Start to set LCD function
	lcd_Control_Write(0x28);
	Delay(50);
	// Clear LCD
	lcd_Control_Write(0x01);
	Delay(50);
	
	// Set entry mode
	lcd_Control_Write(0x06); Delay(50);
	// Set Display to on
	
	lcd_Control_Write(0x0C); Delay(50);
	// Move cursor to home and set data address to 0
	lcd_Control_Write(0x02); Delay(50);
}
void  lcd_Control_Write(char data)
{
	char data_u, data_1;
	uint8_t data_t[4], i = 0;
	data_u = data&0xF0;
	data_1 = (data << 4)&0xF0;
	data_t[0] = data_u|0x04;	// en =  1, rs = 0
	data_t[1] = data_u;				// en = 0,  rs = 0
	data_t[2] = data_1|0x04;	// en = 1,  rs = 0
	data_t[3] = data_1|0x08;	// en = 0, rs = 0
	for(i = 0;i<4;i++)
	{
		lcd_Write_byte(data_t[i]);
	}
}
void LCD_Send_String(char *data)
{
	uint16_t i = 0;
	while(data[i]!=0)
	{
		lcd_Write_byte(data[i]);
		i++;
	}
}