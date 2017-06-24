#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

#define ADC1_DR_Address  (uint32_t)(0x40012400 + 0x4c)
#define AdcDataLength  50

void ADC1_Init(void);

#endif
