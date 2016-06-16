
class Device { //eg 9dof sensor
protected:
  address(es)
  bus
  id_regs
public:
  Device();
  ~Device();
  init
  sensors
}

class Sensor : public Device {
private:
  data_regs //data registers
  ctl_regs // control registers
public:
  read_function
  Sensor();
}
