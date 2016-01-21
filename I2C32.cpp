// 
// 
// 
#include <Wire.h>
#include "I2C32.h"


void I2C32::init()
{



}

void I2C32::init(void * ptr)
{
	wire = ((TwoWire*)ptr);
	
}

void I2C32::write(int adr_cs, byte data)
{
	wire->beginTransmission(adr_cs);
	wire->write(data);
	wire->endTransmission();
}

void I2C32::write(int adr_cs, byte address, byte data)
{
}

void I2C32::write(int adr_cs, byte address, byte * data, int length)
{
}

void I2C32::write16(int adr_cs, byte address, int16_t data)
{
}

void I2C32::writeBit(int adr_cs, byte adress, byte bitNum, bool val)
{
}

byte I2C32::read(int adr_cs, byte address)
{
	return byte();
}

void I2C32::read(int adr_cs, byte address, byte * buffer, int length)
{
}

int16_t I2C32::read16(int adr_cs, byte address)
{
	return int16_t();
}

void I2C32::readBit(int adr_cs, byte address, byte bitNum)
{
}


I2C32 i2c32;