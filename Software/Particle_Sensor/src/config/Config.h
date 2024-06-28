
#ifndef PARTICLE_SENSOR_CONFIG_H
#define PARTICLE_SENSOR_CONFIG_H

#include "defines.h"
#include <vector>
#include <map>
#include "utils.h"
#include "mbed_error.h"
#include "FlashIAP.h"

/**
 * Number of config entries in #Config::global_config
 */
#define NUM_CONFIG_ENTRIES 49

/**
 * Class holding only static member functions and static variables
 * to provide an easy access to the configuration parameters
 */
class Config {
public:
  /**
   * Enum defining the possible data types for the config entries
   */
  enum ConfigType {
    BOOL,
    UINT32,
    FLOAT,
  };

  /**
   * Union defining the config value types
   */
  typedef union {
    bool bool_v;
    uint32_t uint32_v;
    float float_v;
  } config_value_t;

  /**
   * Defines the format of a config parameter entry
   */
  typedef struct {
    std::string name;         // Name of the parameter (snake_case)
    ConfigType type;          // The data type of the parameter
    config_value_t value;     // The value of the parameter
    config_value_t min;       // The minimum of the parameter, for the range check
    config_value_t max;       // The maximum of the parameter, for the range check
    std::string description;  // A description for the parameter
  } entry_t;

  /**
   * Array holding the configuration parameters including
   * the meta data for every parameter.
   */
  static entry_t global_config[NUM_CONFIG_ENTRIES];

  /**
   * Copies the parameter values of #global_config to #default_config.
   * This function is used to store the default configuration before the
   * #global_config is overwritten with the values loaded from the flash memory.
   */
  static void save_default_config();

  /**
   * Copies the the values from #default_config to #global_config.
   */
  static void reset_config();

  /**
   * Getter function for configuration parameter values.
   *
   * @tparam T   Data type of the parameter to be retrieved
   * @param name Name of the parameter to be retrieved
   * @return the value of the parameter with the given \p name
   */
  template<typename T>
  static T get(const std::string &name);

  /**
   * Getter function for a configuration parameter entry
   *
   * @param name Name of the parameter to be retrieved
   * @param dest Destination on which the entry is written to
   * @return true if a parameter with the given \p name was found, false otherwise
   */
  static bool get_entry(const std::string &name, entry_t &dest);

  /**
   * Set the parameter with the given \p name to the value of the given
   * \p value_string if the \p name exists and the value is within the range
   * of the parameter.
   *
   * @param name         Name of the parameter to be set
   * @param value_string The value to be set as string
   * @return true if the parameter was set, false otherwise
   */
  static bool set_value(const std::string &name, const std::string &value_string);

  /**
   * Writes all configuration parameter values to the flash memory at address #STORAGE_ADDR_CONFIG.
   *
   * @param flash Reference to the FlashIAP object
   * @return MBED_SUCCESS if write operation succeeded, an mbed_error_status_t otherwise
   */
  static mbed_error_status_t write_config_to_flash(mbed::FlashIAP &flash);

  /**
   * Reads all configuration parameter values from the flash memory at address #STORAGE_ADDR_CONFIG.
   *
   * @param flash
   * @return
   */
  static mbed_error_status_t read_config_from_flash(mbed::FlashIAP &flash);

private:
  /**
   * Array holding the default configuration parameter values.
   */
  static Config::config_value_t default_config[NUM_CONFIG_ENTRIES];

  /**
   * Writes data from \p source with the given \p size to the given \p address
   * in the flash memory.
   *
   * @param flash   Reference to the FlashIAP object
   * @param address Address within the flash memory to write to
   * @param source  Data which is written to the flash memory
   * @param size    Size of the data to be written
   * @return MBED_SUCCESS if write was successful, an mbed_error_status_t otherwise
   */
  static mbed_error_status_t write_to_flash(mbed::FlashIAP &flash, uint32_t address, uint8_t *source, size_t size);

  /**
   *
   * @param flash       Reference to the FlashIAP object
   * @param address     Address within the flash memory to read from
   * @param destination Buffer where the read data is copied to
   * @param size        Size of the data to be read
   * @return MBED_SUCCESS if read was successful, an mbed_error_status_t otherwise
   */
  static mbed_error_status_t read_from_flash(mbed::FlashIAP &flash, uint32_t address, uint8_t *destination,
                                             size_t size);
};

template<typename T>
T Config::get(const std::string &name) {
  for (const auto &entry : global_config) {
    if (entry.name == name) {
      switch (entry.type) {
        case ConfigType::BOOL:
          return (T) entry.value.bool_v;
        case ConfigType::UINT32:
          return (T) entry.value.uint32_v;
        case ConfigType::FLOAT:
          return (T) entry.value.float_v;
      }
    }
  }
  MBED_ERROR(MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CODE_READ_FAILED), "Config::get() failed");
  return 0;
}

#endif //PARTICLE_SENSOR_CONFIG_H
