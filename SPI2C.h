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
	SPI2C_config * spi2cConfig;
	SPI2C_config * currentConfg;

	static SPI2C * setSPIC2C(SPI2C_config * t) ;
};



#endif

