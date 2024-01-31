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
	
	OLED_ShowString(1, 1, "DID:   MID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);
	
	W25Q64_SectorErase(0x000000);//只能1写成0，不能0写成1，所以写入前需要擦除
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);//不能跨页写入，当到达当页最后一个地址时还再写入，会从当页第一个地址开始写入
	
	W25Q64_ReadData(0x000000, ArrayRead, 4);//读取可跨页
	
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	                           
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	
	while(1){
		
	}
}
