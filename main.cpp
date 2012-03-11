/*
 * main.c
 *
 *  Created on: 12-01-2012
 *      Author: reymondo
 */

#include "stm32f10x.h"
#include "stm32-P107.hpp"
#include "KamodRGB.hpp"
#include "KamodMEMS2.hpp"


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

	Rgb.light(KRed,0);
	Rgb.light(KBlue,0);
	Rgb.light(KGreen,0);
        
        KamodMEMS2 mems=KamodMEMS2(56,i2c);

  	YellowLED.Toggle();

  	//main loop
  	while(1)
	{
  		for(int i=3;i<6;i++)
  		{
  			for(int j=0;j<256;j++)
  			{
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

