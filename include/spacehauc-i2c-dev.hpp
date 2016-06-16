#ifndef INCLUDE_SPACEHAUC_I2C_DEV_HPP_
#define INCLUDE_SPACEHAUC_I2C_DEV_HPP_

#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
//#include <getopt.h>
//#include <stdlib.h>

using std::vector;
using std::string;

class I2C_Device { //eg 9dof sensor
protected:
  string mI2C_device_name;
  uint8_t mBus;
  int mFile;
  vector<uint8_t> mAddress;
  vector<uint8_t> mID_Regsiters;
  int readBytes(uint8_t count, uint8_t *buffer);
  int writeBytes(uint8_t count, uint8_t *input);
public:
  I2C_Device();
  virtual ~I2C_Device();
  bool initDevice();
};

class TemperatureSensor : public I2C_Device {
private:
  vector<uint8_t> mDataRegisters; //data registers
  vector<uint8_t> mControlRegisters; // control registers
  uint8_t mTemperature;
public:
  explicit TemperatureSensor(uint8_t bus, uint8_t address, uint8_t ID_register,
    uint8_t controlRegister, uint8_t dataRegister);
  ~TemperatureSensor();
  bool initTempSensor();
  uint8_t readTemp();
};

#endif  // INCLUDE_SPACEHAUC_I2C_DEV_HPP_
