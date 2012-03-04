/*
 * stm32-P107.cpp
 *
 *  Created on: 23-02-2012
 *      Author: reymondo
 */

#include "stm32-P107.hpp"


LED::LED()
{

}

LED::LED(ELEDs color)
{
	init(color);
}

void LED::init(ELEDs color)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	switch (color)
	{
	case green:
		GPIO_Pin = GPIO_Pin_6;
		break;
	case yellow:
		GPIO_Pin = GPIO_Pin_7;
		break;
//	default :
//		assert();//TODO
	}

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void LED::On()
{
	GPIO_SetBits(GPIOC, GPIO_Pin);
}

void LED::Off()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin);
}

void LED::Toggle()
{
	if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin) != RESET)
	{
		Off();
	}
	else
	{
		On();
	}
}

USART::USART()
{

}

USART::USART(unsigned char U)
{
	init(U);
}

void USART::init(unsigned char U)
{
	ptr=0;
	buff[ptr]='\0';
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	USART_InitTypeDef USART_InitStructure;

	unsigned long RCC_APB1Periph, RCC_APB2Periph;

	switch (U)
	{
		case 2:
			USARTx      = USART2;
			GPIO_Pin_Tx = GPIO_Pin_5;
			GPIO_Pin_Rx = GPIO_Pin_6;
			USARTx_IRQn = USART2_IRQn;

			RCC_APB1Periph = RCC_APB1Periph_USART2;
			RCC_APB2Periph = RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO ;

			break;

//		default :
//			assert(); //TODO
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);


	//Set USART Tx as AF push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//Set USART Rx as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USARTx, &USART_ClockInitStructure);


	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	GPIO_PinRemapConfig(GPIO_Remap_USART2  ,ENABLE);

	//Write USART parameters
	USART_Init(USARTx, &USART_InitStructure);

	//Enable USART
	USART_Cmd(USARTx, ENABLE);
	//hmmm
	while( USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	//USART_Cmd(USART1, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void USART::sendChar(char c)
{
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	USART_SendData(USARTx, (uint8_t) c);
}
char USART::readChar()
{
	return (char) USART_ReceiveData(USARTx);
}

void USART::sendString(const char * c)
{
	int i=0;
	while(c[i]!='\0')
	{
		sendChar(c[i++]);
	}
}
void USART::recCharHandler(char c)
{
	if (c=='\r')
	{
		sendChar((uint8_t)'\r');
		sendChar((uint8_t)'\n');
		sendString("Otrzymano komende: ");
		sendString(buff);
		sendChar((uint8_t)'\r');
		sendChar((uint8_t)'\n');
		sendChar((uint8_t)'>');
		ptr=0;
		buff[0]='\0';
		return;
	}
	if (ptr<64)
	{
		sendChar(c);
		buff[ptr]=c;
		buff[++ptr]='\0';
	}
}

extern "C" void USART2_IRQHandler(void);
void USART2_IRQHandler(void)
{
	extern LED YellowLED ;
	extern USART Console ;
	char b;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		YellowLED.Toggle();

		b=Console.readChar();
		Console.recCharHandler(b);
	}
}

I2C::I2C()
{

}

I2C::I2C(unsigned char I)
{
	init(I);
}
void I2C::init(unsigned char I)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;


	unsigned long RCC_APB1Periph, RCC_APB2Periph;

	switch (I)
	{
		case 1:
			I2Cx      = I2C1;
			GPIO_Pin_SCL = GPIO_Pin_8;
			GPIO_Pin_SDA = GPIO_Pin_9;

			RCC_APB1Periph = RCC_APB1Periph_I2C1;
			RCC_APB2Periph = RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ;

			break;

	//		default :
	//			assert(); //TODO
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

	// Configure I2C1 SCL pin
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SCL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure I2C1 SDA pin
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SDA;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x03;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 200000;
	I2C_Init(I2C1, &I2C_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap_I2C1  ,ENABLE);

	I2C_Cmd(I2Cx, ENABLE);

}

void I2C::sendBytes(unsigned char addr, unsigned char * b, unsigned char len)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	for(unsigned char i=0 ; i<len ; i++)
	{
		I2C_SendData(I2Cx,b[i]);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_GenerateSTOP(I2Cx, ENABLE);

}
void I2C::sendBytes2(unsigned char addr, unsigned char * b, unsigned char len)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	for(unsigned char i=0 ; i<len ; i++)
	{
		I2C_SendData(I2Cx,b[i]);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}

}

void I2C::readBytes(unsigned char addr, unsigned char * b, unsigned char len)
{
	I2C_AcknowledgeConfig(I2Cx,ENABLE);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	for(int i=0 ; i<len ; i++)
	{
		if(i==len-1)
		{
			 I2C_AcknowledgeConfig(I2Cx,DISABLE);
		}
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
		b[i]=I2C_ReceiveData(I2Cx);
	}
	I2C_GenerateSTOP(I2Cx, ENABLE);

}
