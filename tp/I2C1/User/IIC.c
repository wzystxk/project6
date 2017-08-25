#include "IIC.h"

void Onewire_Enable_GPIO_Port(void)
{
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC,ENABLE);
}
void Onewire_OUT_PULL_UP(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void CLK_OUT_PULL_UP(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void Onewire_OUT_FLOATING(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Onewire_IN_FLOATING(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void Onewire_IN_PULL_UP(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}


void RQ_IN_FLOATING(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}


void delay_us(uint16_t us)
{
	us=5*us;
	while(--us);
}


void init(void)
{
	Onewire_Enable_GPIO_Port();
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	RQ_IN_FLOATING();
	SET_DQ();
	SET_CLK();
	delay_us(10);
}

void i2c_start(void)
{
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	SET_DQ();
	delay_us(10);
	SET_CLK();
	delay_us(10);
	CLR_DQ();
	delay_us(10);
}

void i2c_stop(void)
{
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	CLR_DQ();
	delay_us(10);
	SET_CLK();
	delay_us(10);
	SET_DQ();
	delay_us(10);
}

void wait_ack(void)
{
	uint16_t us;
	us=0;
	Onewire_IN_PULL_UP();
	CLK_OUT_PULL_UP();
	SET_CLK();
	delay_us(10);
	while(GET_DQ()&&(us<1024))
		us++;
	CLR_CLK();
	delay_us(10);	
}

void send_ack(uint8_t ack)
{
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	if(ack)
		CLR_DQ();
	else
		SET_DQ();
	SET_CLK();
	delay_us(10);
	CLR_CLK();
	delay_us(10);
	SET_DQ();
	delay_us(10);
}

void write_byte(uint8_t dat)
{
	uint8_t i;
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	for(i=0;i<8;i++){
		CLR_CLK();
		delay_us(10);
		if(dat&0x80)
			SET_DQ();
		else
			CLR_DQ();
		dat=dat<<1;
		delay_us(10);
		SET_CLK();
		delay_us(10);
	}
	CLR_CLK();
	delay_us(10);
	SET_DQ();
	delay_us(10);
}

static uint8_t read_byte(void)
{
	uint8_t i,dat;
	Onewire_OUT_PULL_UP();
	CLK_OUT_PULL_UP();
	CLR_CLK();
	delay_us(10);
	SET_DQ();
	delay_us(10);
	Onewire_IN_PULL_UP();
	for(i=0;i<8;i++){
		SET_CLK();
		delay_us(10);
		dat<<=1;
		if(GET_DQ())
			dat|=0x01;
		CLR_CLK();
		delay_us(10);
	}
	return dat;
}

void write_i2c(uint8_t device, uint8_t addr, uint8_t dat)
{
	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(addr);
	wait_ack();
	write_byte(dat);
	wait_ack();
	i2c_stop();
}


uint8_t read_i2c(uint8_t device, uint8_t addr)
{
	uint8_t dat;
	init();
	i2c_start();
	write_byte(device);
	wait_ack();
	write_byte(addr);
	wait_ack();
	i2c_start();
	write_byte(device+0x01);
	wait_ack();
	dat=read_byte();
	send_ack(0);
	i2c_stop();
	return dat;
}












///* Reset */
//void resetOnewire(void) 
//{
//	Onewire_OUT_PULL_UP();
//	CLR_DQ();
//	delay_us(450);
//	SET_DQ();
//	delay_us(60);
//	Onewire_IN_PULL_UP(); 
//	delay_us(10);
//	while(!(GET_DQ()));
//	Onewire_OUT_PULL_UP();
//	SET_DQ();
//}

///* Read */
//uint8_t rOnewire(void)
//{
//    uint8_t data=0,i=0;
//    for(i=0;i<8;i++)
//    {
//		Onewire_OUT_PULL_UP();
//		CLR_DQ();
//		data=data>>1;
//		SET_DQ();
//		Onewire_IN_PULL_UP();
//		delay_us(8);
//		if(GET_DQ())data|=0x80;
//		Onewire_OUT_PULL_UP();
//		SET_DQ();
//		delay_us(60);
//    }
//    return(data);
//}

///* Write */
//void wOnewire(uint8_t data)
//{
//	uint8_t i=0;
//	Onewire_OUT_PULL_UP();
//	SET_DQ();
//	delay_us(16);
//    	for(i=0;i<8;i++)
//    	{
//		CLR_DQ();
//		if(data&0x01)
//		{
//			SET_DQ();
//		}
//   	 	else
//   	 	{
//			CLR_DQ();
//    	}
//    	data=data>>1;
//		delay_us(40);  //65
//		SET_DQ();
//    }
//}
