#include "24C256.h"
#include "stdio.h"
#include "IIC.h"




uint8_t tmp_eeprom[64];

//extern void eeprom_init(void)
//{

//}




//uint8_t read_eeprom(uint8_t device, uint8_t add)
//{
//	uint8_t dat;
//	uint8_t tmp1,tmp2;
//	tmp1=add/0xff;
//	tmp2=add%0xff;
//	init();
//	i2c_start();
//	write_byte(device);
//	wait_ack();
//	write_byte(add);
////	wait_ack();
////	write_byte(tmp2);
//	wait_ack();
//	i2c_start();
//	write_byte(device+0x01);
//	wait_ack();
//	dat=read_byte();
//	send_ack(0);
//	i2c_stop();
//	return dat;
//}

//void write_eeprom(uint8_t device, uint8_t add, uint8_t dat)
//{
//	uint8_t tmp1,tmp2;
//	tmp1=add/256;
//	tmp2=add%256;
//	init();
//	i2c_start();
//	write_byte(device);
//	wait_ack();
//	write_byte(add);
////	wait_ack();
////	write_byte(tmp2);
//	wait_ack();
//	write_byte(dat);
//	wait_ack();
//	i2c_stop();
//}


//void mul_read(uint8_t device, uint16_t add)
//{
//	uint8_t tmp1,tmp2;

//	uint8_t i;
//	uint16_t cnt=0;
//	
//	cnt=add%64;
//	add=cnt*64;
//	
//	tmp1=add/256;
//	tmp2=add%256;

//	init();
//	i2c_start();
//	write_byte(device);
//	wait_ack();
//	write_byte(tmp1);
//	wait_ack();
//	write_byte(tmp2);
//	wait_ack();
//	i2c_start();
//	write_byte(device+0x01);
//	for(i=0;i<64;i++){
//	wait_ack();
//	tmp_eeprom[i]=read_byte();}
////	send_ack(0);
//	i2c_stop();
////	return dat;
//}


//void mul_write(uint8_t device, uint16_t add)
//{
//	uint8_t tmp1,tmp2;

//	uint8_t i;
//	uint16_t cnt=0;
//	
//	cnt=add%64;
//	add=cnt*64;
//	
//	tmp1=add/256;
//	tmp2=add%256;

//	init();
//	i2c_start();
//	write_byte(device);
//	wait_ack();
//	write_byte(tmp1);
//	wait_ack();
//	write_byte(tmp2);
//	wait_ack();
//	for(i=0;i<64;i++){
//	write_byte(tmp_eeprom[i]);
//	wait_ack();}
//	i2c_stop();
//}

//void transmit_in(uint8_t i, uint8_t dat)
//{
//	tmp_eeprom[i]=dat;
//}

//uint8_t transmit_out(uint8_t i)
//{
//	uint8_t tmp;
//	tmp=tmp_eeprom[i];
//	return tmp;
//}





uint8_t read_eeprom(uint8_t device, uint16_t add)
{
	uint8_t dat;
	uint8_t tmp1,tmp2;
	tmp1=add/0xff;
	tmp2=add%0xff;
	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(tmp1);
	wait_ack();
	write_byte(tmp2);
	wait_ack();
	i2c_start();
	write_byte(device+0x01);
	wait_ack();
	dat=read_byte();
	send_ack(1);
	i2c_stop();
	return dat;
}

void write_eeprom(uint8_t device, uint16_t add, uint8_t dat)
{
	uint8_t tmp1,tmp2;
	tmp1=add/0xff;
	tmp2=add%0xff;
	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(tmp1);
	wait_ack();
	write_byte(tmp2);
	wait_ack();
	write_byte(dat);
	wait_ack();
	i2c_stop();
}


void mul_read(uint8_t device, uint16_t add)
{
	uint8_t tmp1,tmp2;

	uint8_t i;
	uint16_t cnt=0;
	
	cnt=add%64;
	add=cnt*64;
	
	tmp1=add/256;
	tmp2=add%256;

	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(tmp1);
	wait_ack();
	write_byte(tmp2);
	wait_ack();
	i2c_start();
	write_byte(device+0x01);
	for(i=0;i<64;i++){
	wait_ack();
	tmp_eeprom[i]=read_byte();}
//	send_ack(0);
	i2c_stop();
//	return dat;
}


void mul_write(uint8_t device, uint16_t add)
{
	uint8_t tmp1,tmp2;

	uint8_t i;
	uint16_t cnt=0;
	
	cnt=add%64;
	add=cnt*64;
	
	tmp1=add/256;
	tmp2=add%256;

	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(tmp1);
	wait_ack();
	write_byte(tmp2);
	wait_ack();
	for(i=0;i<64;i++){
	write_byte(tmp_eeprom[i]);
	wait_ack();}
	i2c_stop();
}

void transmit_in(uint8_t i, uint8_t dat)
{
	tmp_eeprom[i]=dat;
}

uint8_t transmit_out(uint8_t i)
{
	uint8_t tmp;
	tmp=tmp_eeprom[i];
	return tmp;
}


