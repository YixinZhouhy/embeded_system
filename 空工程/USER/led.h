#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define ON   0
#define OFF  1

#define LED1(a) if(a)\
									GPIO_SetBits(GPIOC, GPIO_Pin_0);\
								else   \
									GPIO_ResetBits(GPIOC, GPIO_Pin_0);
#define LED2(a) if(a)\
									GPIO_SetBits(GPIOC, GPIO_Pin_1);\
								else   \
									GPIO_ResetBits(GPIOC, GPIO_Pin_1);
void LED_GPIO_Config(void);
#endif 
