// 
// 
// 
#include <Wire.h>	
#include <SPI.h>
#include "SPI2C.h"
#include "MPU6XXX32.h"
 
#define WR comP->setSPI2CConfig(&mpu6xxx32Config); comP
 
//SPI2C_config mpu6xxx32Config = { SPI2C_type_e::SPI2C_I2C,0x68,SPI2C_I2C_CLOCK_400, SPI2C_NOT_USED,SPI2C_NOT_USED };
SPI2C_config mpu6xxx32Config = { SPI2C_type_e::SPI2C_SPI_TRANSACTIONAL,10,1000000,SPI_MODE1,MSBFIRST };
MPU6XXX32::MPU6XXX32()
{
}
MPU6XXX32::MPU6XXX32(uint8_t address)
{
}

void MPU6XXX32::initialize()
{
	comP = SPI2C::setSPIC2C(&mpu6xxx32Config);

	WR->setSPI2CConfig(&mpu6xxx32Config);
	 
	setClockSource(MPU6050_CLOCK_PLL_XGYRO);
	setFullScaleGyroRange(MPU6050_GYRO_FS_250);
	setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
	setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
}

bool MPU6XXX32::testConnection()
{
	return getDeviceID() == 0x34;
}


uint8_t MPU6XXX32::getDeviceID()
{

	 
 WR->readBits(  MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &buffer[0]);
	
	return buffer[0];
	return uint8_t();
}

void MPU6XXX32::setClockSource(uint8_t source)
{
 
	
	 
	WR->writeBits(  MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
 
}

void MPU6XXX32::setFullScaleGyroRange(uint8_t range)
{
	WR->writeBits(  MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void MPU6XXX32::setFullScaleAccelRange(uint8_t range)
{
	WR->writeBits( MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void MPU6XXX32::setSleepEnabled(bool enabled)
{
	WR->writeBit(  MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);

}

void MPU6XXX32::getAcceleration(int16_t * x, int16_t * y, int16_t * z)
{
	WR->read(MPU6050_RA_ACCEL_XOUT_H, buffer,6);
	*x = (((int16_t)buffer[0]) << 8) | buffer[1];
	*y = (((int16_t)buffer[2]) << 8) | buffer[3];
	*z = (((int16_t)buffer[4]) << 8) | buffer[5];
}

void MPU6XXX32::getRotation(int16_t * x, int16_t * y, int16_t * z)
{
	WR->read(  MPU6050_RA_GYRO_XOUT_H,   buffer,6);
	*x = (((int16_t)buffer[0]) << 8) | buffer[1];
	*y = (((int16_t)buffer[2]) << 8) | buffer[3];
	*z = (((int16_t)buffer[4]) << 8) | buffer[5];
}
