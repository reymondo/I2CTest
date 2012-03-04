/*
 * stm32-P107.hpp
 *
 *  Created on: 23-02-2012
 *      Author: reymondo
 */
#include "stm32f10x.h"

#ifndef STM32_P107_HPP_
#define STM32_P107_HPP_

typedef enum ELEDs
{
	green,
	yellow
}ELEDs;


class LED
{
  public:
	LED();
	LED(ELEDs color);
	void init(ELEDs color)  ;
	void On()    ;
	void Off()   ;
	void Toggle();
  private:
	unsigned short GPIO_Pin ;
};

class USART
{
  public:
	USART();
	USART(unsigned char U) ;
	void init(unsigned char U);
	void sendChar(char c)   ;
	void sendString(const char * c) ;
	char readChar()   ;
	void readLine(const char * c) ;
	void recCharHandler(char c);

  private:
	USART_TypeDef * USARTx;
	unsigned short  GPIO_Pin_Tx ;
	unsigned short  GPIO_Pin_Rx ;
	unsigned char 	USARTx_IRQn ;

	char buff[64];
	unsigned char ptr;
};

class I2C
{
  public:
	I2C();
	I2C(unsigned char I) ;
	void init(unsigned char I);
	void sendBytes(unsigned char addr, unsigned char * b ,unsigned char len);
	void sendBytes2(unsigned char addr, unsigned char * b, unsigned char len);
	void readBytes(unsigned char addr, unsigned char * b, unsigned char len);


  private:
	I2C_TypeDef * I2Cx;
	unsigned short  GPIO_Pin_SCL ;
	unsigned short  GPIO_Pin_SDA ;
};


#endif /* STM32_P107_HPP_ */
