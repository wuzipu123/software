

#ifndef CONTROLLER_UTILS_H
#define CONTROLLER_UTILS_H

#include <ctime>
#include <string>

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

#ifdef MBED_DEBUG
#define DEBUG_PRINTF(fmt, ...)                    \
    ({                                            \
      do {                                        \
        fprintf(stderr, fmt, __VA_ARGS__);        \
      } while (0);                                \
    })

#define DEBUG_PRINT(fmt)                          \
    ({                                            \
        fprintf(stderr, fmt);                     \
    })
#else
#define DEBUG_PRINTF(fmt, ...)
#define DEBUG_PRINT(fmt)
#endif //MBED_DEBUG

namespace utils {
  /**
   * Get the current time in the format specified by \p format_string
   * and write the result into \p dest.
   *
   * @param format_string Format specifier for the strftime() function
   * @param dest          The string to write to
   */
  void get_formatted_time_string(const char *format_string, std::string &dest);

  /**
   * Convert a given float \p num into a string encoded in the
   * the scientific format and write it into \p dest.
   *
   * @param num  The number to convert
   * @param dest The string to write the number to
   */
  void convert_to_exp_num_string(float num, std::string &dest);

  /**
   * Check if every character in \p str is >= '0' and <= '9' and
   * thus represents an unsigned integer.
   *
   * @param str The number string
   * @return true if \p str is a number, false otherwise
   */
  bool is_number(const std::string &str);

  /**
   * Convert a given \p number into a hex string.
   *
   * @param number The number to convert
   * @return the string with the number in hex format
   */
  std::string to_hex_string(uint32_t number);

#ifdef PRINT_STATS
  /**
   * Print the stack, heap and CPU statistics in an endless loop every 30 seconds.
   * Should be executed in a separate thread.
   * For the statistics to work it is necessary to define the following macros:
   * MBED_MEM_TRACING_ENABLED
   * MBED_HEAP_STATS_ENABLED
   * MBED_CPU_STATS_ENABLED
   * MBED_STACK_STATS_ENABLED
   */
  void print_statistics();
#endif //PRINT_STATS
} // namespace utils

#endif //CONTROLLER_UTILS_H
