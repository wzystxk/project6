#ifndef __led_H
#define __led_H 

#include "ALL_Includes.h"

#define LED_GPIO_CLK   RCC_AHBPeriph_GPIOB 
#define LED_PORT   	   GPIOB
#define LED_PIN        GPIO_Pin_8


void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);

#endif



