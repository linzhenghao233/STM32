#include "stm32f10x.h"                  // Device header

void Encoder_Init(void){
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//复用时需更改成对应端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	Tim_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructure.TIM_Period = 65536 - 1;	//ARR
	Tim_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;	//PSC
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &Tim_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	
	//配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//TIM_ICPolarity_Rising选择这个不反相
	
	TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_Get(void){
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Temp;
}
