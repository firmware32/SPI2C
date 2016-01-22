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
// I2C32.h

#ifndef _I2C32_h
#define _I2C32_h

#include "SPI2C.h"
	#include "arduino.h"


class I2C32  : public SPI2C
{
 protected:
	

 public:
	 virtual void init() override;
 
	TwoWire * wire;

	bool i2cEnabled;
	// Inherited via SPI2C
	I2C32();
	I2C32(TwoWire * w);
 
	virtual void write(byte data) override;
	virtual void write(byte address, byte data) override;
	virtual void write(byte address, byte * data, int length) override;
	virtual void write16(byte address, int16_t*  data) override;
	virtual void writeBit(byte adress, byte bitNum, bool val) override;
	virtual byte read(byte address) override;
	virtual void read(byte address, byte * buffer, int length) override;
	virtual int16_t read16(byte address) override;
	virtual uint8_t readBit(byte address, byte bitNum) override;
	virtual int8_t  readBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) override;
	virtual void setSPI2CConfig(SPI2C_config * con) override;
	virtual void writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) override;
};


#endif

