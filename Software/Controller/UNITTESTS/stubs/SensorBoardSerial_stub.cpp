

#include "SensorBoardSerial.h"

SensorBoardSerial::SensorBoardSerial(std::string &read_msg, std::string &write_msg) : _read_msg(read_msg),
                                                                                      _write_msg(write_msg){
}

size_t SensorBoardSerial::read(void *buffer, size_t length) {
  size_t num_bytes_read = 0;
  for(num_bytes_read = 0; num_bytes_read < length; num_bytes_read++) {
    if(_cursor >= _read_msg.size()) {
      break;
    }
    ((char *)buffer)[num_bytes_read] = _read_msg[_cursor];
    _cursor++;
  }
  return num_bytes_read;
}

int SensorBoardSerial::write(const void *buffer, size_t length) {
  size_t num_bytes_written = 0;
  for(num_bytes_written = 0; num_bytes_written < length; num_bytes_written++) {
    _write_msg += ((char *)buffer)[num_bytes_written];
  }
  return 0;
}



void SensorBoardSerial::enable_rx_irq() {
}

void SensorBoardSerial::disable_rx_irq() {
}
