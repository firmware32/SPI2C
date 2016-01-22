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

