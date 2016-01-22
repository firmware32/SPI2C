
#include "SPI2C.h"
#include <Wire.h>
#include "I2C32.h"

#include <SPI.h>
#include "SPI32.h"
#include "MPU6XXX32.h"
MPU6XXX32 mpu;
MPU6XXX32 mpu2;
SPI2C_config con =  { SPI2C_type_e::SPI2C_I2C,0x68,SPI2C_I2C_CLOCK_400, SPI2C_NOT_USED,SPI2C_NOT_USED };
SPI2C *comP = SPI2C::setSPIC2C(&con);
SPISettings setting(1000000, MSBFIRST, SPI_MODE3);
void setup()
{
	SPI.begin();
  Wire.begin();
	 mpu.initialize();
	  mpu2.init(&con);
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);
	//
	 
	//Wire.beginTransmission(0x68);
	//int error = Wire.endTransmission();

	SerialUSB.begin(115200);
	while (!SerialUSB);
 
	//digitalWrite(10, LOW);
	//SPI.beginTransaction(setting);
	//SPI.transfer(MPU6050_RA_WHO_AM_I | 0x80);
	//SerialUSB.println(SPI.transfer(0));


	//SPI.endTransaction();
	//digitalWrite(10, HIGH);
 //
		int error = 0;
	 error = mpu.getDeviceID();
	 SerialUSB.println("HI"	);
	 SerialUSB.println(error,HEX);
  
  /* add setup code here */

}
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
void loop()
{
	//while (1)
	//{
	//	SerialUSB.print(mpu2.getDeviceID());
	//	SerialUSB.print("\t");
	//	SerialUSB.println(mpu.getDeviceID());



	//}
	int tim_me = micros();
 mpu.getAcceleration(&ax, &ay, &az);
	
		mpu.getRotation(&gx, &gy, &gz);
		SerialUSB.print("spi ");
		SerialUSB.print( micros() - tim_me); SerialUSB.print("\t gyro ");
		SerialUSB.print(gx); SerialUSB.print("\t"); SerialUSB.print(gy); SerialUSB.print("\t"); SerialUSB.print(gz); SerialUSB.print ("\t ac ");
		//SPISettings ss()
 	SerialUSB.print(ax); SerialUSB.print(  "\t"); SerialUSB.print(ay); SerialUSB.print("\t"); SerialUSB.print(az); SerialUSB.println("\t");
	//SPISettings ss()

	tim_me = micros();
 	mpu2.getAcceleration(&ax, &ay, &az);

	mpu2.getRotation(&gx, &gy, &gz);
	SerialUSB.print("i2c ");
	SerialUSB.print(micros() - tim_me); SerialUSB.print("\t gyro ");
	SerialUSB.print(gx); SerialUSB.print("\t"); SerialUSB.print(gy); SerialUSB.print("\t"); SerialUSB.print(gz); SerialUSB.print("\t ac ");
	//SPISettings ss()
 SerialUSB.print(ax); SerialUSB.print("\t"); SerialUSB.print(ay); SerialUSB.print("\t"); SerialUSB.print(az); SerialUSB.println("\t");

 // /* add main program code here */
	delay(1000);
}
