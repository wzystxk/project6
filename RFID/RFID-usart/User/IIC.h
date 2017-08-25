#ifndef _IIC_H
#define _IIC_H
#include "stm32f0xx.h"

#define SET_DQ() 		GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define CLR_DQ() 		GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define GET_DQ() 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define GET_RQ() 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)


#define SET_CLK()		GPIO_SetBits(GPIOC,GPIO_Pin_14)
#define CLR_CLK()		GPIO_ResetBits(GPIOC,GPIO_Pin_14)


void Onewire_Enable_GPIO_Port(void);
void Onewire_OUT_PULL_UP(void);
void Onewire_OUT_FLOATING(void);
void Onewire_IN_FLOATING(void);
void Onewire_IN_PULL_UP(void);
void _delay_us(uint8_t us);
void CLK_OUT_PULL_UP(void);
void init(void);
void i2c_start(void);
void i2c_stop(void);
void wait_ack(void);
void send_ack(uint8_t ack);
void write_byte(uint8_t dat);
static uint8_t read_byte(void);
void write_i2c(uint8_t device, uint8_t addr, uint8_t dat);
uint8_t read_i2c(uint8_t device, uint8_t addr);





//void resetOnewire(void) ;
//uint8_t rOnewire(void);
//void wOnewire(uint8_t data);

#endif /*_ONEWIRE_H*/

