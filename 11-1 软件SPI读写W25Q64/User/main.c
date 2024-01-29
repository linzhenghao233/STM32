#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

static uint8_t MID;
static uint16_t DID;

int main(void){
	OLED_Init();
	W25Q64_Init();
	
	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(1, 1, MID, 2);
	OLED_ShowHexNum(1, 8, DID, 4);
	
	while(1){
		
	}
}
