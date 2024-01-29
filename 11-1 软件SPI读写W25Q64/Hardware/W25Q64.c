#include "stm32f10x.h"                  // Device header
#include "MySPI.h"

void W25Q64_Init(void){
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID){
	MySPI_Start();
	MySPI_SwapByte(0x9F);
	*MID = MySPI_SwapByte(0xFF);
	*DID = MySPI_SwapByte(0xFF);
	*DID <<= 8;
	*DID |= MySPI_SwapByte(0xFF);
	MySPI_Stop();
}
