# SPI2C
SPI2C - I2C &amp; SPI in one common library 

Many sensors now come in  two formats SPI or I2C lot of time the API is almost identical however the translation is not. This library is intended to remededy that. I have included a limited MPUXXXX library as an example of how to harness the power of the SPI(I)2C :)
```
//Easy to use:  works with Arduino DUE or Arduino Zero (SAMD21 boards)
#include <SPI2C.h>
#include <Wire.h>
#include <SPI.h> // includE SPI
#include "MPU6X_PARTIAL.h" //Not a complete library
#define SER SerialUSB // Serial Choose appropriate
MPU6XXX32 MPU_I2C;
MPU6XXX32 MPU_SPI;

//  TYPE - I2C_ADDRESS/SPI_CS_PIN  - I2C_CLOCK/SPI_CLOCK - IC32_NA/SPI BIT DIR  I2C_NA/SPI_MOD
SPI2C_config spi2cI2CConfig =  { SPI2C_type_e::SPI2C_I2C,0x68,SPI2C_I2C_CLOCK_400, SPI2C_NOT_USED,SPI2C_NOT_USED };
SPI2C_config spi2cSPIConfig = { SPI2C_type_e::SPI2C_SPI_TRANSACTIONAL,10,1000000, MSBFIRST,SPI_MODE3 };
 
SPISettings setting(1000000, MSBFIRST, SPI_MODE3);
void setup()
{
	SER.begin(115200);
	while (!SER);

	// Setup SPI pin 10
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	//library expects SPI & WIRE to best started if used.
  SPI.begin();
  Wire.begin();

  // init both MPUs - comment out seperatly if you don't have two boards
  MPU_I2C.init(&spi2cI2CConfig);
  MPU_SPI.init(&spi2cSPIConfig);

	 
}
int16_t ax, ay, az;
int16_t gx, gy, gz;
 // Instructions if you have two mpu6500 or mpu9250 hook 2 up at a time if not comment out appropriate section.
void loop()
{
//SPI VERSION
	int tim_me = micros();
	MPU_SPI.getAcceleration(&ax, &ay, &az);
	MPU_SPI.getRotation(&gx, &gy, &gz);
		SER.print("spi ");
		SER.print(micros() - tim_me); SER.print("gyro \t");
		SER.print(gx); SER.print("\t"); SER.print(gy); SER.print("\t"); SER.print(gz); SER.print("\t ac ");
		SER.print(ax); SER.print("\t"); SER.print(ay); SER.print("\t"); SER.print(az); SER.println("\t");
 

//I2C VERSION
	tim_me = micros();
	MPU_I2C.getAcceleration(&ax, &ay, &az);

	MPU_I2C.getRotation(&gx, &gy, &gz);
	SER.print("i2c ");
	SER.print(micros() - tim_me); SER.print("gyro \t");
	SER.print(gx); SER.print("\t"); SER.print(gy); SER.print("\t"); SER.print(gz); SER.print("\t ac ");
  SER.print(ax); SER.print("\t"); SER.print(ay); SER.print("\t"); SER.print(az); SER.println("\t");

	delay(100);
}
```
