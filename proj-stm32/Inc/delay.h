#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f1xx.h"

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























