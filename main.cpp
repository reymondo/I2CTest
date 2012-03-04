/*
 * main.c
 *
 *  Created on: 12-01-2012
 *      Author: reymondo
 */


#define LIS35_I2CADDR 56 

#define LIS35_REG_OUTX 	0x29
#define LIS35_REG_OUTY	0x2B
#define LIS35_REG_OUTZ	0x2D

#define LIS35_REG_CR1 0x20
#define LIS35_REG_CR1_XEN 0x1
#define LIS35_REG_CR1_YEN 0x2
#define LIS35_REG_CR1_ZEN 0x4
#define LIS35_REG_CR1_DR_400HZ 0x80
#define LIS35_REG_CR1_ACTIVE 0x40
#define LIS35_REG_CR1_FULL_SCALE 0x20

#define LIS35_REG_CR2 0x21
#define LIS35_REG_CR2_BOOT 0x40

#define LIS35_CR3 0x22
#define LIS35_CR3_IHL 0x80
#define LIS35_CR3_CLICK_INT 0x7
#define LIS35_CR3_FF1_INT 0x1
#define LIS35_AUTOINC 0x80

#define LIS35_FF_WU_CFG_1 0x30
#define LIS35_FF_WU_SRC_1 0x31
#define LIS35_FF_WU_THS_1 0x32
#define LIS35_FF_WU_DURATION_1 0x33


#define LIS35_CLICK_CFG 0x38
#define LIS35_CLICK_THSY_X 0x3b
#define LIS35_CLICK_THSZ 0x3c
#define LIS35_CLICK_TIME_LIMIT 0x3D


#define LIS35_STATUS_REG 0x27



#include "stm32f10x.h"
#include "stm32-P107.hpp"
#include "KamodRGB.hpp"


LED GreenLED;
LED YellowLED;
USART Console;


int main()
{
	SystemInit();

	//LEDS
	GreenLED.init(green);
	YellowLED.init(yellow);

	GreenLED.Off();
	YellowLED.On();


	//USART
	Console.init(2) ;
	Console.sendString("\r\nStart!!\r\n\r\n");

	//SYSTICK
	SysTick_Config(10000000);

	YellowLED.Toggle();

	I2C i2c=I2C(1);

	KamodRGB Rgb=KamodRGB(0,i2c);
	Rgb.light(KAmber,255);

	Console.sendString("KAMOD MEMS 2\r\n");
	unsigned char B[2] = {LIS35_REG_CR1, LIS35_REG_CR1_XEN | LIS35_REG_CR1_YEN | LIS35_REG_CR1_ZEN | LIS35_REG_CR1_ACTIVE | LIS35_REG_CR1_FULL_SCALE};
	unsigned char C[5];

//	B[0]=LIS35_REG_CR1;
//	B[1]=LIS35_REG_CR1_XEN | LIS35_REG_CR1_YEN | LIS35_REG_CR1_ZEN | LIS35_REG_CR1_ACTIVE;
//	i2c.sendBytes(58,B,2);
//
//	i2c.readBytes(58,B,2);
//	Console.sendChar(B[0]);
//	Console.sendChar(B[1]);

	Rgb.light(KRed,0);
	Rgb.light(KBlue,0);
	Rgb.light(KGreen,0);

  	YellowLED.Toggle();

  	//main loop
  	while(1)
	{
  		for(int i=3;i<6;i++)
  		{
  			for(int j=0;j<256;j++)
  			{
  				i2c.sendBytes(LIS35_I2CADDR, B, 2);

				B[0] = LIS35_REG_OUTX | LIS35_AUTOINC ;
				i2c.sendBytes2(LIS35_I2CADDR, B, 1);


				i2c.readBytes(LIS35_I2CADDR, C, 5);

				//Rgb.light(KRed,C[0]);
				Rgb.light(KGreen,C[2]);
				//Rgb.light(KBlue,C[4]);

				for(int z=0;z<100000;z++);
  			}

  		}


	}


	return 0;
}

extern "C" void SysTick_Handler(void);
void SysTick_Handler(void)
{
	YellowLED.Toggle();
	GreenLED.Toggle();
}

