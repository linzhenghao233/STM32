#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM_InternalClockConfig(TIM2);//默认是内部，可不写
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0X0F);
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructure;
	Tim_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructure.TIM_Period = 10 - 1;
	Tim_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
	Tim_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &Tim_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

uint16_t Timer_GetCount(void){
	return TIM_GetCounter(TIM2);
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		Num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
