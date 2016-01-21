// SPI32.h

#ifndef _SPI32_h
#define _SPI32_h

#include "SPI2C.h"
	#include "arduino.h"

 class SPI32 : public SPI2C
{
 protected:


 public:
	 SPIClass * spiP;
	void config(SPISettings &setting);


	// Inherited via SPI2C
	virtual void init() override;
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

extern SPI32 spi32;

#endif

