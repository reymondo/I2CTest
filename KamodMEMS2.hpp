/* 
 * File:   KamodMEMS2.hpp
 * Author: reymondo
 *
 * Created on 4 marzec 2012, 19:30
 */

#ifndef KAMODMEMS2_HPP
#define	KAMODMEMS2_HPP

#include "stm32-P107.hpp"


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

class KamodMEMS2 {
  public:
    KamodMEMS2();
    KamodMEMS2(unsigned char ad, I2C i2c);
    void init(unsigned char  ad, I2C i2c);
    unsigned char  getx();
    unsigned char  gety();
    unsigned char  getz();
    
  private:
    I2C i2c;
    u8 addr;

};

#endif	/* KAMODMEMS2_HPP */

