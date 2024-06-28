
#include "utils.h"
#include "mbed.h"

namespace utils {
  void get_formatted_time_string(const char *format_string, std::string &dest) {
    time_t current_time = time(nullptr);
    char time_string[100];
    strftime(time_string, 100, format_string, localtime(&current_time));
    dest.clear();
    dest.append(time_string);
  }

  void convert_to_exp_num_string(float num, std::string &dest) {
    char buffer[20] = {0};
    snprintf(buffer, 20, "%.9e", num);
    dest.clear();
    dest += buffer;
  }

  bool is_number(const string &str) {
    for (auto c : str) {
      if (!(c >= '0' && c <= '9')) {
        return false;
      }
    }
    return true;
  }

  std::string to_hex_string(uint32_t number) {
    char hex_string[20];
    sprintf(hex_string, "0x%lX", number);
    return std::string(hex_string);
  }

#ifdef PRINT_STATS

  void print_statistics() {
    while (true) {
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
      ThisThread::sleep_for(30000);
    }
  }

#endif //PRINT_STATS
}