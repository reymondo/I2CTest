/*
 * KamodRGB.cpp
 *
 *  Created on: 29-02-2012
 *      Author: reymondo
 */

#include "KamodRGB.hpp"


KamodRGB::KamodRGB()
{

}
KamodRGB::KamodRGB(u8 addr, I2C i2c){
	init(addr,i2c);
}
void KamodRGB::init(u8 add, I2C i)
{
	i2c=i;
	addr=add;

	unsigned char B[3][2]={{0,0},{1,0},{8,255}};
	for(int i=0;i<3;i++)
	{
		i2c.sendBytes(addr,B[i],2);
	}

	light(KAmber,0);
	light(KRed,0);
	light(KGreen,0);
	light(KBlue,0);
}

void KamodRGB::light(KamodRGBColors color, u8 val)
{
	unsigned char B[2]={color,val};
	i2c.sendBytes(addr,B,2);
}


