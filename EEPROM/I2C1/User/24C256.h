#ifndef _24C256_H
#define _24C256_H
#include "stdint.h"

#include "IIC.h"
#define eprom 0xA0




//uint8_t read_eeprom(uint8_t device, uint8_t add);
//void write_eeprom(uint8_t device, uint8_t add, uint8_t dat);
//void mul_read(uint8_t device, uint16_t add);
//void mul_write(uint8_t device, uint16_t add);
//void transmit_in(uint8_t i, uint8_t dat);
//uint8_t transmit_out(uint8_t i);




uint8_t read_eeprom(uint8_t device, uint16_t add);
void write_eeprom(uint8_t device, uint16_t add, uint8_t dat);
void mul_read(uint8_t device, uint16_t add);
void mul_write(uint8_t device, uint16_t add);
void transmit_in(uint8_t i, uint8_t dat);
uint8_t transmit_out(uint8_t i);


#endif


