#include "spacehauc-i2c-dev.hpp"
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
using std::string;

I2C_Device::I2C_Device() {}

I2C_Device::~I2C_Device() {}

bool I2C_Device::initDevice() {
  mI2C_device_name = "/dev/i2c-" + std::to_string((int)mBus);
  mFile = open(mI2C_device_name.c_str(), O_RDWR);
  if (mFile) {
    return true;
  }
  return false;
}

int I2C_Device::readBytes(uint8_t reg, uint8_t *buffer, uint8_t count) {
  struct i2c_rdwr_ioctl_data packets;
  struct i2c_msg messages[2];
  /* write the register we want to read from */
  messages[0].addr  = mAddress[0];
  messages[0].flags = 0;
  messages[0].len   = 1;
  messages[0].buf   = &reg;

  /* read */
  messages[1].addr  = mAddress[0];
  messages[1].flags = I2C_M_RD;
  messages[1].len   = count;
  messages[1].buf   = buffer;

  packets.msgs      = messages;
  packets.nmsgs     = 2;

  return ioctl(mFile, I2C_RDWR, &packets) >= 0;
}

int I2C_Device::writeBytes(uint8_t count, uint8_t *input) {
  struct i2c_rdwr_ioctl_data packets;
  struct i2c_msg messages[1];

  messages[0].addr  = mAddress[0];
  messages[0].flags = 0;
  messages[0].len   = count;
  messages[0].buf   = input; // needs to be an array w/ first being register
    // and second being data

  packets.msgs      = messages;
  packets.nmsgs     = 1;

  return ioctl(mFile, I2C_RDWR, &packets) >= 0 ;
}


TemperatureSensor::TemperatureSensor(uint8_t bus, uint8_t address, uint8_t ID_register,
  uint8_t controlRegister, uint8_t dataRegister) {
    mBus = bus;
    mAddress.push_back(address);
    mID_Regsiters.push_back(ID_register);
    mControlRegisters.push_back(controlRegister);
    mDataRegisters.push_back(dataRegister);
}

TemperatureSensor::~TemperatureSensor() {}


bool TemperatureSensor::initTempSensor() {
  uint8_t input[2] = {mControlRegisters[0], 0x98};
  if (writeBytes (2, input)) {
    return true;
  }
  return false;
}

uint8_t TemperatureSensor::readTemp() {
  readBytes (mDataRegisters[0], &mTemperature, 2);
  return mTemperature;
}
