#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t KeyNum;

int main(void){
	Buzzer_Init();
	LightSensor_Init();
	
	Buzzer_OFF();
	while(1){
		if(LightSensor_Get() == 0){
			Buzzer_ON();
		}
		else{
			Buzzer_OFF();
		}
	}
}
