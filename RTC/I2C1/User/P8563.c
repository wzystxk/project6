#include "P8563.h"
#include "IIC.h"
#include "main.h"
#include "data.h"
#include "stdint.h"
//#include "main.c"
//#include "IIC.c"



uint8_t g8563_Store[6];
//extern uint8_t g8563_Store[6]; /*时间交换区,全局变量声明*/
//extern uint8_t c8563_Store[6]={0x16,0x02,0x29,0x17,0x20,0x00}; /*写入时间初值：星期一 07:59:00*/
uint8_t c8563_Store[6]={0x16,0x02,0x29,0x20,0x57,0x00}; /*写入时间初值：星期一 07:59:00*/


void p8563_read(void)
{
	uint8_t time[7];
	uint8_t i=0;
	for(i=0;i<7;i++)
	time[i]=read_i2c(rtc_8563, i+2);
	
		g8563_Store[0]=time[0]&0x7f; /*秒 */
		g8563_Store[1]=time[1]&0x7f; /*分 */
		g8563_Store[2]=time[2]&0x3f; /*小时 */
		g8563_Store[3]=time[3]&0x3f; /*日 */
		g8563_Store[4]=time[5]&0x1f; /*月 */
		g8563_Store[5]=time[6]; /*年  */
}

void p8563_gettime(void)
{
	p8563_read();
	if(g8563_Store[0]==0)
		p8563_read();
}

void p8563_settime(void)
{
	write_i2c(rtc_8563, 8, g8563_Store[0]);
	write_i2c(rtc_8563, 7, g8563_Store[1]);
	write_i2c(rtc_8563, 5, g8563_Store[2]);
	write_i2c(rtc_8563, 4, g8563_Store[3]);
	write_i2c(rtc_8563, 3, g8563_Store[4]);
	write_i2c(rtc_8563, 2, g8563_Store[5]);
}


void p8563_init(void)
{
	uint8_t i;
	for(i=0;i<5;i++)
	g8563_Store[i]=c8563_Store[i]; 
	p8563_settime();
}


uint8_t transmit(uint8_t i)
{
	uint8_t tmp;
	tmp=((g8563_Store[i]>>4)&0x0F)*10 + (g8563_Store[i]&0x0F);
	return tmp;
}

