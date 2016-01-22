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
// SPI2C.h

#ifndef _SPI2C_h
#define _SPI2C_h


	#include "arduino.h"

//uint32_t clock, BitOrder bitOrder, uint8_t dataMode

#define SPI2C_I2C_CLOCK_100 100000
#define SPI2C_I2C_CLOCK_400 400000
#define SPI2C_NOT_USED  0
enum SPI2C_type_e
{
	SPI2C_NOT_SET,
	SPI2C_I2C,
	SPI2C_SPI,
	SPI2C_SPI_TRANSACTIONAL,
#if defined(ARDUINO_SAM_DUE)
	SPI2C_I2C1,
#endif
	SPI2C_COUNT


};

typedef struct {

	SPI2C_type_e spi2ctype;
	union {
		uint8_t	i2c_address;
		uint8_t spi_cs;
	};
	union {
		uint32_t i2c_clock;
		uint32_t spi_clock;
	};
	uint8_t spi_dataMode;
	uint8_t spi_bitOrder;
}SPI2C_config;

class SPI2C
{
 protected:


 public:

	virtual void init()=0;

	virtual void write( byte data) = 0;
	virtual void write( byte address, byte data) = 0;
	virtual void write( byte address, byte * data, int length) = 0;
	virtual void write16( byte address, int16_t*  data) = 0;
	virtual void writeBit( byte adress, byte bitNum, bool val) = 0;
	virtual byte read( byte address) = 0;
	virtual void read( byte address, byte * buffer, int length) = 0;
	virtual int16_t read16( byte address) = 0;
	virtual uint8_t readBit( byte address, byte bitNum) = 0;
	virtual void setSPI2CConfig(SPI2C_config * con) = 0;
	virtual int8_t  readBits( uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) = 0;
	virtual void  writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) = 0;
	 
	SPI2C_config * currentConfg;
	static SPI2C * setSPIC2C(SPI2C_config * t) ;
};



#endif

