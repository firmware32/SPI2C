// 
// 
// 
#include <SPI.h>
#include "SPI32.h"


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
	byte byte_value =  read(adress);
	if (val == 0)
	{
		byte_value = byte_value & ~(1 << bitNum); // AND result from register byte value and byte with only one "0" at place of bit to write (rest "1"'s)
	}
	else // databit is intended to be a "1"
	{
		byte_value = byte_value | (1 << bitNum); // OR  result from register byte value and byte with only one "1" at place of bit to write (rest "0"'s)
	}
	write(adress, byte_value);
}

byte SPI32::read( byte address)
{
	byte b;
	SPIBEGIN
		SP->transfer(address);
	b = SP->transfer(0x00);

	SPIEND
		return b;
}

void SPI32::read( byte address, byte * buffer, int length)
{
	SPIBEGIN
		SP->transfer(address);
	for (uint8_t i = 0; i < length; i++)
	{
		buffer[i] = SP->transfer(0x00);
	}


	SPIEND
		 
}

int16_t SPI32::read16( byte address)
{
 
	byte  byteH, byteL;
	uint16_t return_value;
 
	SPIBEGIN
	  SP->transfer(address);
	byteH = SP->transfer(0);
	byteL = SP->transfer(0);
	SPIEND
	return_value = ((uint16_t)byteH << 8) | (byteL);
	
		return return_value;
	 
}
uint8_t SPI32::readBit( byte address, byte bitNum)
{
	byte byte_value =  read(address);
	byte bit_value = byte_value & (1 << bitNum); // AND result from register byte value and byte with only one "1" at place of bit to return (rest "0"'s)
	return bit_value;
}
int8_t SPI32::readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t * data)
{
	 
	int8_t b = read ( regAddr);
	byte mask = ((1 << length) - 1) << (bitStart - length + 1);
	b = b & mask;
	b = b >> (bitStart - length + 1);
	data[0] = b;
	return b;
}
void SPI32::setSPI2CConfig(SPI2C_config * con)
{
	currentConfg = con;
	spiSettings = SPISettings(currentConfg->spi_clock, (BitOrder)currentConfg->spi_bitOrder, currentConfg->spi_dataMode);

}

void SPI32::writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
	 
		byte byte_value =  read(regAddr);
		byte mask = ((1 << length) - 1) << (bitStart - length + 1); // create mask
		data <<= (bitStart - length + 1); // shift data into correct position
		data &= mask;                     // zero all non-important bits in data (just to make sure)
		byte_value &= ~(mask);            // zero all important bits in existing byte, maintain the rest
		byte_value |= data;               // combine data with existing byte
		 write(regAddr, byte_value);
}

void SPI32::init()
{
}
