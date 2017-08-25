#ifndef _P8563_H
#define _P8563_H

#include "stdint.h"

//#include "stm32f0xx.h"


#define rtc_8563 0xA2


void p8563_read(void);
void p8563_gettime(void);
void p8563_settime(void);
void p8563_init(void);
uint8_t transmit(uint8_t i);


#endif

