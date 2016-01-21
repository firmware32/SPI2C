// SPI2C.h

#ifndef _SPI2C_h
#define _SPI2C_h


	#include "arduino.h"


class SPI2C
{
 protected:


 public:
	 virtual void init(void * ptr)=0;
	virtual void init()=0;
	virtual void write(int adr_cs, byte data) = 0;
	virtual void write(int adr_cs, byte address, byte data) = 0;
	virtual void write(int adr_cs, byte address, byte * data, int length) = 0;
	virtual void write16(int adr_cs, byte address, int16_t data) = 0;
	virtual void writeBit(int adr_cs, byte adress, byte bitNum, bool val) = 0;
	virtual byte read(int adr_cs, byte address) = 0;
	virtual void read(int adr_cs, byte address, byte * buffer, int length) = 0;
	virtual int16_t read16(int adr_cs, byte address) = 0;
	virtual void readBit(int adr_cs, byte address, byte bitNum) = 0;

	 
};



#endif

