
#ifndef PARTICLE_SENSOR_UTILS_H
#define PARTICLE_SENSOR_UTILS_H

#include <ctime>
#include <string>

/**
 * @brief Swap least and most significant byte of a uint16_t
 */
#define REVERSE_2_BYTE(n) ((((n) & 0x00FFU) << 8U) | (((n) & 0xFF00U) >> 8U))

/**
 * @brief Execute func and if it fails return with the return value of func
 */
#define TRY(func)                                 \
    ({                                            \
      auto err = (func);                          \
      if (0 != err) {                             \
        return err;                               \
      }                                           \
    })

namespace utils {
  /**
   * Get the current time in the format specified by \p format_string
   * and write the result into \p dest.
   *
   * @param format_string Format specifier for the strftime() function
   * @param dest          The string to write to
   * @param timestamp     Optional timestamp. If 0, current time is converted to string.
   */
  void get_formatted_time_string(const char *format_string, std::string &dest, time_t timestamp = 0);

  /**
   * Check \p str represents a signed integer.
   *
   * @param str The number string
   * @return true if \p str is an integer number, false otherwise
   */
  bool is_number(const std::string &str);

  /**
   * Check if \p represents a boolean value.
   *
   * @param str  The boolean string
   * @param dest The destination to write the result to
   * @return true, if the \p str represents a boolean value, false if parsing failed
   */
  bool string_to_bool(const std::string &str, bool &dest);

  /**
   * Convert a given \p number into a hex string.
   *
   * @param number The number to convert
   * @return the string with the number in hex format
   */
  std::string to_hex_string(uint32_t number);

  /**
   * Return the #version as a string. (e.g. "1.3.2")
   *
   * @return the version number string
   */
  std::string app_version();

  /**
   * Calculate the 16-bit CRC checksum of \p buf.
   *
   * @param buf the data buffer to calculate the CRC from
   * @param size the size of the data buffer
   * @return the 16-bit CRC checksum
   */
  uint16_t calc_crc16(const void *buf, int size);

  /**
   * Calculate the 32-bit CRC checksum of \p buf.
   *
   * @param buf the data buffer to calculate the CRC from
   * @param size the size of the data buffer
   * @return the 32-bit CRC checksum
   */
  uint32_t calc_crc32(const void *buf, int size);

  /**
   * Check if a given number is within a given range of two values. (inclusive)
   *
   * @tparam T  Data type of the value
   * @param val The value, which should be checked
   * @param min The lower bound of the range
   * @param max The higher bound of the range
   * @return true, if \p val is in the range, false otherwise
   */
  template<typename T>
  static inline bool is_in_range(T val, T min, T max) {
    return ((val >= min) && (val <= max));
  }

  /**
   * Get a random 32-bit number generated by the builtin TRNG.
   *
   * @return a random 32-bit number
   */
  uint32_t get_rand();

#ifdef PRINT_STATS
  /**
   * Print the stack, heap and CPU statistics
   * For the statistics to work it is necessary to define the following macros:
   * MBED_MEM_TRACING_ENABLED
   * MBED_HEAP_STATS_ENABLED
   * MBED_CPU_STATS_ENABLED
   * MBED_STACK_STATS_ENABLED
   */
  void print_statistics();
#endif //PRINT_STATS
} // namespace utils

#endif //PARTICLE_SENSOR_UTILS_H
