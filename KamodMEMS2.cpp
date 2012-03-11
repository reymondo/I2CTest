/* 
 * File:   KamodMEMS2.cpp
 * Author: reymondo
 * 
 * Created on 4 marzec 2012, 19:30
 */

#include "KamodMEMS2.hpp"
#include "stm32-P107.hpp"

KamodMEMS2::KamodMEMS2() 
{
   
}

KamodMEMS2::KamodMEMS2(unsigned char  ad, I2C i) 
{
    init( ad,  i);
}

void KamodMEMS2::init(unsigned char ad, I2C i)
{
    addr=ad;
    i2c=i;
    unsigned char B[2] = {LIS35_REG_CR1, LIS35_REG_CR1_XEN | LIS35_REG_CR1_YEN | LIS35_REG_CR1_ZEN | LIS35_REG_CR1_ACTIVE | LIS35_REG_CR1_FULL_SCALE};
    i2c.sendBytes(addr,B,2);
}

unsigned char  KamodMEMS2::getx()
{
    unsigned char  B=LIS35_REG_OUTX;
    i2c.sendBytes2(addr,&B,1);
    i2c.readBytes(addr, &B, 1);
    return B;
}
