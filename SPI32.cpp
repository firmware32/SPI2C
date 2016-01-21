// 
// 
// 
#include <SPI.h>
#include "SPI32.h"

void SPI32::init()
{
//	SPI.begin();
	Serial.println("HI SPI");
	init( &SPI);

}

void SPI32::init(void * ptr)
{
	spiP = (SPIClass*)ptr;
	spiP->begin();
}


SPI32 spi32;

void SPI32::write(int adr_cs, byte data)
{
}

void SPI32::write(int adr_cs, byte address, byte data)
{
}

void SPI32::write(int adr_cs, byte address, byte * data, int length)
{
}

void SPI32::write16(int adr_cs, byte address, int16_t data)
{
}

void SPI32::writeBit(int adr_cs, byte adress, byte bitNum, bool val)
{
}

byte SPI32::read(int adr_cs, byte address)
{
	return byte();
}

void SPI32::read(int adr_cs, byte address, byte * buffer, int length)
{
}

int16_t SPI32::read16(int adr_cs, byte address)
{
	return int16_t();
}

void SPI32::readBit(int adr_cs, byte address, byte bitNum)
{
}
