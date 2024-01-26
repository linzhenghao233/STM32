#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

//指定地址写
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDRESS);
//	MyI2C_ReceiveAck();
//	MyI2C_SendByte(RegAddress);
//	MyI2C_ReceiveAck();
//	MyI2C_SendByte(Data);
//	MyI2C_ReceiveAck();
//	MyI2C_Stop();
}

//指定地址读
uint8_t MPU6050_ReadReg(uint8_t RegAddress){
//	uint8_t Data;
//	
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDRESS);
//	MyI2C_ReceiveAck();
//	MyI2C_SendByte(RegAddress);
//	MyI2C_ReceiveAck();
//	
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//变为读
//	MyI2C_ReceiveAck();
//	Data = MyI2C_ReceiveByte();
//	MyI2C_SendAck(1);
//	MyI2C_Stop();
	
	return Data;
}

void MPU6050_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//STM32作为从机会响应几位地址
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;//STM32作为从机时使用
	I2C_Init(I2C2, &I2C_InitStructure);
	
	I2C_Cmd(I2C2, ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);//解除睡眠
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);//选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);//采样率分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);//配置滤波参数最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);//陀螺仪和加速度计都选最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_GetID(void){
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
					int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ){
	uint8_t DataH, DataL;
						
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
						
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
						
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;

	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
