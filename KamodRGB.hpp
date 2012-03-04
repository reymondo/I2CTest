/*
 * KamodRGB.hpp
 *
 *  Created on: 29-02-2012
 *      Author: reymondo
 */

#ifndef KAMODRGB_HPP_

#include "stm32-P107.hpp"

typedef enum KamodRGBColors
{
	KAmber = 2,
	KBlue   ,
	KRed ,
	KGreen  ,

}KamodRGBColors;

class KamodRGB
{
  public:
	KamodRGB();
	KamodRGB(u8 addr, I2C i2c);
	void init(u8 addr, I2C i2c);
	void light(KamodRGBColors color, u8 val);
  private:
	I2C i2c;
	u8 addr;

};


#define KAMODRGB_HPP_


#endif /* KAMODRGB_HPP_ */
