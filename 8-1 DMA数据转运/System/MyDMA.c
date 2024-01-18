#include "stm32f10x.h"                  // Device header

static uint16_t MyDMA_Size;//static声明表示只本文件使用

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint8_t Size){
	MyDMA_Size = Size;
	
	//RCC开启DMA的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//调用DMA_Init并初始化各个参数
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize = Size;//缓存大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//是否使用自动重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//是否是存储器到存储器，即软件触发或硬件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	//调用DMA_Cmd控制开关
	DMA_Cmd(DMA1_Channel1, DISABLE);
}

void MyDMA_TransFer(void){
	//要再写入数据需先使DMA失能
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
