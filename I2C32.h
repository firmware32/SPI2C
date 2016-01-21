// I2C32.h

#ifndef _I2C32_h
#define _I2C32_h

#include "SPI2C.h"
	#include "arduino.h"

 



class I2C32  : public SPI2C
{
 protected:
	 TwoWire * wire;

 public:
	void init();

	// Inherited via SPI2C
	virtual void init(void * ptr) override;
	virtual void write(int adr_cs, byte data) override;
	virtual void write(int adr_cs, byte address, byte data) override;
	virtual void write(int adr_cs, byte address, byte * data, int length) override;
	virtual void write16(int adr_cs, byte address, int16_t data) override;
	virtual void writeBit(int adr_cs, byte adress, byte bitNum, bool val) override;
	virtual byte read(int adr_cs, byte address) override;
	virtual void read(int adr_cs, byte address, byte * buffer, int length) override;
	virtual int16_t read16(int adr_cs, byte address) override;
	virtual void readBit(int adr_cs, byte address, byte bitNum) override;
	
};

extern I2C32 i2c32;

#endif

