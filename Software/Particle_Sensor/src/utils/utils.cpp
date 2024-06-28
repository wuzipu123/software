
#include "utils.h"
#include "defines.h"
#include "MbedCRC.h"
#include "trng_api.h"

#ifdef PRINT_STATS
#include "mbed.h"
#endif

namespace utils {
  void get_formatted_time_string(const char *format_string, std::string &dest, time_t timestamp) {
    time_t time_temp = timestamp;
    if (0 == time_temp) {
      time_temp = time(nullptr);
    }
    char time_string[100];
    strftime(time_string, 100, format_string, localtime(&time_temp));
    dest.clear();
    dest.append(time_string);
  }

  bool is_number(const std::string &str) {
    for (size_t i = 0; i < str.size(); i++) {
      if (!(str[i] >= '0' && str[i] <= '9')) {
        if (i == 0 && str[i] == '-') {
          continue;
        }
        return false;
      }
    }
    return true;
  }

  bool string_to_bool(const std::string &str, bool &dest) {
    if (str == "true" || str == "TRUE" || str == "T" || str == "t" || str == "1") {
      dest = true;
      return true;
    } else if (str == "false" || str == "FALSE" || str == "F" || str == "f" || str == "0") {
      dest = false;
      return true;
    }
    return false;
  }

  std::string to_hex_string(uint32_t number) {
    char hex_string[20];
    snprintf(hex_string, 20, "0x%lx", (unsigned long) number);
    return std::string(hex_string);
  }

  std::string app_version() {
    char buf[14];
    snprintf(buf, 14, "%d.%d.%d", version.major, version.minor, version.build);
    return std::string(buf);
  }

  uint16_t calc_crc16(const void *buf, int size) {
    mbed::MbedCRC<POLY_16BIT_CCITT, 16> ct;
    uint32_t crc = 0;

    ct.compute(buf, size, &crc);

    return (uint16_t) crc;
  }

  uint32_t calc_crc32(const void *buf, int size) {
    mbed::MbedCRC<POLY_32BIT_ANSI, 32> ct;
    uint32_t crc = 0;

    ct.compute(buf, size, &crc);

    return crc;
  }

  uint32_t get_rand() {
    trng_t trng;
    trng_init(&trng);
    uint32_t rand_num;
    size_t out_len = 0;
    trng_get_bytes(&trng, (uint8_t *) &rand_num, sizeof(uint32_t), &out_len);
    return rand_num;
  }

#ifdef PRINT_STATS
  void print_statistics() {
    // Stack statistics
    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stack_stats = (mbed_stats_stack_t *) malloc(cnt * sizeof(mbed_stats_stack_t));
    cnt = mbed_stats_stack_get_each(stack_stats, cnt);
    for (int i = 0; i < cnt; i++) {
      printf("Thread: 0x%lX, Stack size: %5lu, Max stack: %5lu\r\n",
             stack_stats[i].thread_id, stack_stats[i].reserved_size, stack_stats[i].max_size);
    }
    free(stack_stats);

    // Heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    printf("Heap current size: %lu bytes\r\n", heap_stats.current_size);
    printf("Heap reserved size: %lu bytes\r\n", heap_stats.reserved_size);
    printf("Heap max size: %lu bytes\r\n", heap_stats.max_size);
    printf("Heap overhead size: %lu bytes\r\n", heap_stats.overhead_size);
    printf("Heap total size: %lu bytes\r\n", heap_stats.total_size);
    printf("Heap alloc cnt: %lu\r\n", heap_stats.alloc_cnt);
    printf("Heap alloc fail cnt: %lu\r\n", heap_stats.alloc_fail_cnt);

    // CPU statistics
    mbed_stats_cpu_t cpu_stats;
    mbed_stats_cpu_get(&cpu_stats);
    printf("Uptime: %llu ", cpu_stats.uptime / 1000);
    printf("Sleep time: %llu ", cpu_stats.sleep_time / 1000);
    printf("Deep Sleep: %llu\n", cpu_stats.deep_sleep_time / 1000);
  }
#endif //PRINT_STATS
}