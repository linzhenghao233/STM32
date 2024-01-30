#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

static uint8_t MID;
static uint16_t DID;

static uint8_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x04};
static uint8_t ArrayRead[4];

int main(void){
	OLED_Init();
	W25Q64_Init();
	
	OLED_ShowString(1, 1, "DID:    MID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);
	
	while(1){
		
	}
}
