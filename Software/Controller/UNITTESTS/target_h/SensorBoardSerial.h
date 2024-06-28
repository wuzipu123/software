

#ifndef CONTROLLER_SENSORBOARDSERIAL_H
#define CONTROLLER_SENSORBOARDSERIAL_H

#include <cstddef>
#include <string>

class SensorBoardSerial {
public:
  SensorBoardSerial(std::string &read_msg, std::string &write_msg);

  size_t read(void *buffer, size_t length);

  int write(const void *buffer, size_t length);

  void enable_rx_irq();

  void disable_rx_irq();

private:
  std::string &_read_msg;
  std::string &_write_msg;
  int _cursor = 0;
};


#endif //CONTROLLER_SENSORBOARDSERIAL_H
