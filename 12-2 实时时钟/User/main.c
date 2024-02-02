#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

int main(void){
	OLED_Init();
	MyRTC_Init();
	
	OLED_ShowString(1, 1, "Date:XXXX-XX-XX");
	OLED_ShowString(2, 1, "Time:XX:XX:XX");
	OLED_ShowString(3, 1, "CNT:");
	
	while(1){
		MyRTC_ReadTime();
		OLED_ShowNum(1, 1, RTC_GetCounter(), 10);;
	}
}
