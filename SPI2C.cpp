// 

// 
// 
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
