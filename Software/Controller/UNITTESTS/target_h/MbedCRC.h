

#ifndef CONTROLLER_MBEDCRC_H
#define CONTROLLER_MBEDCRC_H

#include <cstdint>
#include "crc_api.h"

namespace mbed {

  template<uint32_t polynomial, uint8_t width>
  class MbedCRC {
  public:
    typedef uint64_t crc_data_size_t;

    MbedCRC();

    int32_t compute(const void *buffer, crc_data_size_t size, uint32_t *crc);
  };
}

#endif //CONTROLLER_MBEDCRC_H
