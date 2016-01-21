#include "SPI2C.h"
#include <Wire.h>
#include "I2C32.h"

#include <SPI.h>
#include "SPI32.h"
SPI2C *comP = &spi32;

void setup()
{
	Serial.begin(115200);
	

	
  /* add setup code here */

}

void loop()
{
	comP->init();

  /* add main program code here */

}
