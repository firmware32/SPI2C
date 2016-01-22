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
 
#include "SPI2C.h"
#include <Wire.h>
#include <SPI.h>
#include "SPI32.h"
#include "I2C32.h"

static SPI32 spi32D(&SPI);
static I2C32 i2c32(&Wire);
#if defined(ARDUINO_SAM_DUE)
static I2C32 i2c32_1(&Wire1);
#endif
 
SPI2C * SPI2C::setSPIC2C(SPI2C_config * t)
{
	 switch (t->spi2ctype)
			{
			case SPI2C_type_e::SPI2C_I2C :
				
				return (SPI2C*)&i2c32;
				break;
			case SPI2C_type_e::SPI2C_SPI :
			case SPI2C_type_e::SPI2C_SPI_TRANSACTIONAL:
				return (SPI2C*)&spi32D;
				break;
#if defined(ARDUINO_SAM_DUE)
			case SPI2C_type_e::SPI2C_I2C1:
				return (SPI2C*)&i2c32_1;
				break;

#endif
			default:
				return nullptr;
				break;
			}
	 

	
}
