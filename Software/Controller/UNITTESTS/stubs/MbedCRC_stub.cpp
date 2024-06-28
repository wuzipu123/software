

#include "MbedCRC.h"
#include <cstdio>

namespace mbed {
  template<>
  MbedCRC<POLY_16BIT_CCITT, 16>::MbedCRC() {
  }

  template<>
  int32_t MbedCRC<POLY_16BIT_CCITT, 16>::compute(const void *buffer, crc_data_size_t size, uint32_t *crc) {
    *crc = 0xDEC9;
    return 0;
  }
}

