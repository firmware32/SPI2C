//	written by : Doug Reuter
//	SPI2C is a libarary that combines both SPI calls and I2C calls into 
// like methods so sensors that use both protocols can be used with minimum modfication
//	may work on other arduino boards as well
//	http://Firmware32.com   https://github.com/firmware32/SPI2C/
//	Copyright (C) 2016 Doug Reuter   dougreuter@gmail.com

//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <Wire.h>
#include "I2C32.h"



void I2C32::init()
{
	if (!i2cEnabled)
	{
		SerialUSB.println("i2c enabled");
		//wire->begin();
		i2cEnabled = true;
	}

}

I2C32::I2C32(TwoWire * w)
{
	wire = w;
}
I2C32::I2C32()
{
	wire = &Wire;
	wire->begin();
}
 
void I2C32::write(  byte data)
{
	 wire->beginTransmission(currentConfg->i2c_address);
	 wire->write(data);
	 wire->endTransmission();
}

void I2C32::write(    byte reg, byte data)
{
	write(  reg, &data, 1);
}

void I2C32::write(  byte reg, byte * data, int length)
{
	wire->beginTransmission(currentConfg->i2c_address);
	wire->write((uint8_t)reg);
	for (uint8_t i = 0; i < length; i++) 
		wire->write((uint8_t)data[i]);
	wire->endTransmission();

}

void I2C32::write16( byte reg, int16_t* data)
{
	wire->beginTransmission(currentConfg->i2c_address);
	wire->write((uint8_t)reg);
	wire->write((uint8_t)(data[0] >> 8));    // send MSB
	wire->write((uint8_t)data[1]);         // send LSB
	wire->endTransmission();
}

void I2C32::writeBit(  byte adress, byte bitNum, bool val)
{
	uint8_t b = read( adress );
	b = (val != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	return write( adress, b);
}

byte I2C32::read(  byte address)
{ 
	byte b;
	read(  address, &b, 1);
	return b;
}

void I2C32::read( byte address, byte * buffer, int length)
{
	int8_t count = 0;
	uint32_t t1 = millis();
	uint32_t timeout = 1000;

	for (uint8_t k = 0; k < length; k += min(length, BUFFER_LENGTH)) {
		wire->beginTransmission(currentConfg->i2c_address);
		wire->write(address);
		wire->endTransmission();
		wire->beginTransmission(currentConfg->i2c_address);
		wire->requestFrom(currentConfg->i2c_address, (uint8_t)min(length - k, BUFFER_LENGTH));

		for (; wire->available() && (timeout == 0 || millis() - t1 < timeout); count++) {
			buffer[count] = wire->read();
 
		}
	}
 
}

int16_t I2C32::read16(  byte address)
{
	byte b[2];
	read( address,  b, 2);
	return (int16_t)(b[0] << 8 ) + b[1];
	return int16_t();
}

  uint8_t I2C32::readBit( byte address, byte bitNum)
{
	uint8_t b =  read( address );

	return ( b & (1 << bitNum));
 
}

  int8_t I2C32::readBits( uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t * data)
  {
	 
	  uint8_t  b = read(  regAddr);

			  uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
			  b &= mask;
			  b >>= (bitStart - length + 1);
			  *data = b;
		 
		 
  return b;
  }

void I2C32::setSPI2CConfig(SPI2C_config * con)
{
	currentConfg = con;
	
	wire->setClock(currentConfg->i2c_clock);

}

void I2C32::writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
	uint8_t b = read(regAddr );

		uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1); // shift data into correct position
		data &= mask; // zero all non-important bits in data
		b &= ~(mask); // zero all important bits in existing byte
		b |= data; // combine data with existing byte
		  write( regAddr, b);
	 
}


 