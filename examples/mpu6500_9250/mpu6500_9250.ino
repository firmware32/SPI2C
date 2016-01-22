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
#include <SPI2C.h>

#include <Wire.h>
#include <SPI.h> // includE SPI

#include "MPU6X_PARTIAL.h" //Not a complete library
#define SER SerialUSB // Serial Choose appropriate
MPU6XXX32 MPU_I2C;
MPU6XXX32 MPU_SPI;
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
 
void loop()
{

	int tim_me = micros();
	MPU_SPI.getAcceleration(&ax, &ay, &az);
	MPU_SPI.getRotation(&gx, &gy, &gz);
		SER.print("spi ");
		SER.print(micros() - tim_me); SER.print("gyro \t");
		SER.print(gx); SER.print("\t"); SER.print(gy); SER.print("\t"); SER.print(gz); SER.print("\t ac ");
		SER.print(ax); SER.print("\t"); SER.print(ay); SER.print("\t"); SER.print(az); SER.println("\t");
 

	tim_me = micros();
	MPU_I2C.getAcceleration(&ax, &ay, &az);

	MPU_I2C.getRotation(&gx, &gy, &gz);
	SER.print("i2c ");
	SER.print(micros() - tim_me); SER.print("gyro \t");
	SER.print(gx); SER.print("\t"); SER.print(gy); SER.print("\t"); SER.print(gz); SER.print("\t ac ");
 SER.print(ax); SER.print("\t"); SER.print(ay); SER.print("\t"); SER.print(az); SER.println("\t");

	delay(100);
}
