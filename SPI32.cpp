// 
// 
// 
#include <SPI.h>
#include "SPI32.h"

//  SPI32::SPI32(SPIClass * s)
//{
// 
//	spiP =  s;
//
//}

#define SPIBEGIN digitalWrite(	currentConfg->spi_cs ,LOW); spiP->beginTransaction(spiSettings);
#define SPIEND digitalWrite(	currentConfg->spi_cs ,HIGH); spiP->endTransaction();
#define SP spiP

SPI32::SPI32(SPIClass * s)
{
	spiP = s;
}

SPI32::SPI32()
{

	spiP = &SPI;
 
	spiP->begin();
};

void SPI32::write( byte data)
{
	SPIBEGIN
		SP->transfer(data);
	SPIEND
}

void SPI32::write( byte address, byte data)
{
	SPIBEGIN
		SP->transfer(address);
	    SP->transfer(data);
	SPIEND
}

void SPI32::write( byte address, byte * data, int length)
{
	SPIBEGIN
		SP->transfer(address);
	for (uint8_t i = 0; i < length; i++)
	 
		SP->transfer(data[i]);

	 
	
	SPIEND

}

void SPI32::write16( byte address, int16_t* data)
{
	SPIBEGIN
		SP->transfer(address);
 
		SP->transfer((uint8_t)data[0] << 8);
		SP->transfer((uint8_t)data[1]);
 
	SPIEND


}

void SPI32::writeBit( byte adress, byte bitNum, bool val)
{
}

byte SPI32::read( byte address)
{
	byte b;
	SPIBEGIN
		SP->transfer(address);
	b = SP->transfer(0x00);
	 
	SPIEND
	return byte();
}

void SPI32::read( byte address, byte * buffer, int length)
{
}

int16_t SPI32::read16( byte address)
{
	return int16_t();
}

uint8_t SPI32::readBit( byte address, byte bitNum)
{
	return 0;
}
int8_t SPI32::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t * data)
{
	return int8_t();
}
void SPI32::setSPI2CConfig(SPI2C_config * con)
{
	currentConfg = con;

	spiSettings = SPISettings(currentConfg->spi_clock, (BitOrder)currentConfg->spi_bitOrder, currentConfg->spi_dataMode);


}

void SPI32::writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
}

void SPI32::init()
{
}
