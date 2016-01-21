
#include "SPI2C.h"
#include <Wire.h>
#include "I2C32.h"

#include <SPI.h>
#include "SPI32.h"
#include "MPU6XXX32.h"
MPU6XXX32 mpu;
SPI2C_config con =  { SPI2C_type_e::SPI2C_I2C,0x00,SPI2C_I2C_CLOCK_400, SPI2C_NOT_USED,SPI2C_NOT_USED };
SPI2C *comP = SPI2C::setSPIC2C(&con);

void setup()
{
	 Wire.begin();
	mpu.initialize();

	 
	Wire.beginTransmission(0x68);
	int error = Wire.endTransmission();

	SerialUSB.begin(115200);


 
	error = mpu.getDeviceID();
	while (!SerialUSB);
	SerialUSB.println(error,HEX);
  /* add setup code here */

}
int16_t ax, ay, az;
int16_t gx, gy, gz;
void loop()
{
	mpu.getAcceleration(&ax, &ay, &az);
	 
		mpu.getRotation(&gx, &gy, &gz);
		SerialUSB.print(gx); SerialUSB.print("\t"); SerialUSB.print(gy); SerialUSB.print("\t"); SerialUSB.print(gz); SerialUSB.print ("\t");
		//SPISettings ss()
	SerialUSB.print(ax); SerialUSB.print(  "\t"); SerialUSB.print(ay); SerialUSB.print("\t"); SerialUSB.print(az); SerialUSB.println("\t");
	//SPISettings ss()
 // /* add main program code here */
	delay(1000);
}
