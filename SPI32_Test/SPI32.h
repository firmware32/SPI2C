// SPI32.h

#ifndef _SPI32_h
#define _SPI32_h
#include "arduino.h"
#include <SPI.h>
#include "SPI2C.h"


 class SPI32 : public SPI2C
{
 protected:


 public:
 

	 bool spEnabled;
	 // Inherited via SPI2C
 
	 SPISettings spiSettings;
	 SPIClass * spiP;
	//void config(SPISettings &setting);


	 SPI32();
	 SPI32(SPIClass * s);

	virtual void write( byte data) override;
	virtual void write( byte address, byte data) override;
	virtual void write( byte address, byte * data, int length) override;
	virtual void write16( byte address, int16_t* data) override;
	virtual void writeBit( byte adress, byte bitNum, bool val) override;
	virtual byte read( byte address) override;
	virtual void read( byte address, byte * buffer, int length) override;
	virtual int16_t read16( byte address) override;
	virtual uint8_t readBit( byte address, byte bitNum) override;
	virtual int8_t  readBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) override;
	virtual void setSPI2CConfig(SPI2C_config * con) override;
	virtual void writeBits(  uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) override;
	virtual void init() override;
 };

 

#endif

