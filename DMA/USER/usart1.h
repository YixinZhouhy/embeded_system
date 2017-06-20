#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"
#include "stdio.h"

#define SENDBUFF_SIZE   50
#define USART1_DR_Base  0x40013804

void DMA_Config(void);
void USART1_Config(void);
	
#endif

