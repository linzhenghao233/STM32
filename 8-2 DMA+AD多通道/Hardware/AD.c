#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void AD_Init(void){
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC开启DMA的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//对ADC时钟进行分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//72MHz / 6 = 12MHz
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//规则组（连续扫描）
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);
	//结构体初始化ADC,连续转换,扫描模式
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE	;
	ADC_Init(ADC1, &ADC_InitStructure);


	//DMA初始化
	//调用DMA_Init并初始化各个参数
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize = 4;//缓存大小
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//是否使用自动重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//是否是存储器到存储器，即软件触发或硬件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	//调用DMA_Cmd控制开关
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//开启ADC到DMA
	ADC_DMACmd(ADC1, ENABLE);
	//开启ADC的电源
	ADC_Cmd(ADC1, ENABLE);
	//ADC校准
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//void AD_GetValue(void){
//	DMA_Cmd(DMA1_Channel1, DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1, 4);
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//因为ADC还是单次模式，所以还需软件触发一下ADC
//	
//	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
//	DMA_ClearFlag(DMA1_FLAG_TC1);
//}
