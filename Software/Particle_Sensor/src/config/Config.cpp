#include "Config.h"
#include <climits>
#include <cstring>
#include "Logger.h"

Config::entry_t Config::global_config[] =
    {
        {
            .name ="log_level",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = LVL_INFO},
            .min = {.uint32_v = LVL_SUPPRESS},
            .max = {.uint32_v = NUM_LOG_LEVELS - 1},
            .description = "Log level/verbosity [0: suppress, 1: error, 2: info, 3: debug]"
        },
        {
            .name ="sample_time_sec",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 3600},
            .min = {.uint32_v = 1},
            .max = {.uint32_v = 100000},
            .description = "Time between two consecutive measurements in seconds"
        },
        {
            .name ="status_enable",
            .type = ConfigType::BOOL,
            .value = {.bool_v = true},
            .description = "Enable sending of status data (Vbat, RSSI, SNR) over LoRa [true|false]"
        },
        {
            .name ="status_interval_sec",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 7200},
            .min = {.uint32_v = 30},
            .max = {.uint32_v = 99999999},
            .description = "Time between two consecutive status updates in seconds"
        },
        {
            .name ="sps_startup_sec",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 30},
            .min = {.uint32_v = 1},
            .max = {.uint32_v = 1000},
            .description = "SPS30 startup time between starting measurement and reading measurement data"
        },
        {
            .name ="moving_avg_length",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 5},
            .min = {.uint32_v = 1},
            .max = {.uint32_v = 1000},
            .description = "Number of measurement values used to compute the moving average. (1 = no averaging)"
        },
        {
            .name ="sd_log_enable",
            .type = ConfigType::BOOL,
            .value = {.bool_v = true},
            .description = "Enable logging of measured data to SD card [true|false]"
        },
        {
            .name ="lora_enable",
            .type = ConfigType::BOOL,
            .value = {.bool_v = true},
            .description = "Enable communication thread and sending measured data over LoRa [true|false]"
        },
        {
            .name ="lora_carrier_freq",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 868000000},
            .min = {.uint32_v = 863000000},
            .max = {.uint32_v = 867000000},
            .description = "LoRa: carrier frequency [863000000 - 870000000]"
        },
        {
            .name ="lora_bandwidth",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 0},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 3},
            .description = "LoRa: bandwidth [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]"
        },
        {
            .name ="lora_datarate",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 12},
            .min = {.uint32_v = 6},
            .max = {.uint32_v = 12},
            .description = "LoRa: datarate [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096 chips]"
        },
        {
            .name ="lora_coderate",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 1},
            .min = {.uint32_v = 1},
            .max = {.uint32_v = 4},
            .description = "LoRa: coding rate [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]"
        },
        {
            .name ="lora_preamble_len",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 8},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 100000},
            .description = "LoRa: preamble length in symbols"
        },
        {
            .name ="lora_fix_len",
            .type = ConfigType::BOOL,
            .value = {.bool_v = false},
            .description = "LoRa: fixed length packets [false: variable, true: fixed]"
        },
        {
            .name ="lora_crc_on",
            .type = ConfigType::BOOL,
            .value = {.bool_v = true},
            .description = "LoRa: enables/Disables the CRC [false: OFF, true: ON]"
        },
        {
            .name ="lora_freq_hop_on",
            .type = ConfigType::BOOL,
            .value = {.bool_v = false},
            .description = "LoRa: enables disables the intra-packet frequency hopping [false: OFF, true: ON]"
        },
        {
            .name ="lora_hop_period",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 4},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 100000},
            .description = "LoRa: number of symbols between each hop"
        },
        {
            .name ="lora_iq_inverted",
            .type = ConfigType::BOOL,
            .value = {.bool_v = false},
            .description = "LoRa: Inverts IQ signals [false: not inverted, true: inverted]"
        },
        {
            .name ="lora_tx_power",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 14},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 14},
            .description = "LoRa: Sets the output power [0 - 14dBm]"
        },
        {
            .name ="lora_tx_timeout",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 3000},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 0xFFFFFFFF},
            .description = "LoRa: Transmission timeout [ms]"
        },
        {
            .name ="lora_rx_symb_timeout",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 255},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 0xFFFFFFFF},
            .description = "LoRa: timeout in symbols"
        },
        {
            .name ="lora_rx_payload_len",
            .type = ConfigType::UINT32,
            .value = {.uint32_v = 255},
            .min = {.uint32_v = 0},
            .max = {.uint32_v = 255},
            .description = "LoRa: Sets payload length when fixed length is used"
        },
        {
            .name ="lora_rx_continuous",
            .type = ConfigType::BOOL,
            .value = {.bool_v = true},
            .description = "LoRa: Sets the reception in continuous mode [false: single mode, true: continuous mode]"
        },
        {
            .name ="pm1.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PM1.0 data"
        },
        {
            .name ="pm1.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PM1.0 data"
        },
        {
            .name ="pm2.5_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PM2.5 data"
        },
        {
            .name ="pm2.5_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PM2.5 data"
        },
        {
            .name ="pm4.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PM4.0 data"
        },
        {
            .name ="pm4.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PM4.0 data"
        },
        {
            .name ="pm10.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PM10.0 data"
        },
        {
            .name ="pm10.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PM10.0 data"
        },
        {
            .name ="pn0.5_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PN0.5 data"
        },
        {
            .name ="pn0.5_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PN0.5 data"
        },
        {
            .name ="pn1.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PN1.0 data"
        },
        {
            .name ="pn1.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PN1.0 data"
        },
        {
            .name ="pn2.5_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PN2.5 data"
        },
        {
            .name ="pn2.5_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PN2.5 data"
        },
        {
            .name ="pn4.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PN4.0 data"
        },
        {
            .name ="pn4.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PN4.0 data"
        },
        {
            .name ="pn10.0_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for PN10.0 data"
        },
        {
            .name ="pn10.0_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for PN10.0 data"
        },
        {
            .name ="part_size_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction offset for typical particle size data"
        },
        {
            .name ="part_size_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Particle Sensor Data: Set correction factor for typical particle size data"
        },
        {
            .name ="temp_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction offset for air temperature data"
        },
        {
            .name ="temp_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction factor for air temperature data"
        },
        {
            .name ="press_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction offset for air pressure data"
        },
        {
            .name ="press_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction factor for air pressure data"
        },
        {
            .name ="hum_offset",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 0.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction offset for relative humidity data"
        },
        {
            .name ="hum_factor",
            .type = ConfigType::FLOAT,
            .value = {.float_v = 1.0},
            .min = {.float_v = -9999999.9},
            .max = {.float_v = 9999999.9},
            .description = "Environmental Sensor Data: Set correction factor for relative humidity data"
        }
    };

Config::config_value_t Config::default_config[NUM_CONFIG_ENTRIES] = {0};

bool Config::get_entry(const std::string &name, entry_t &dest) {
  for (const auto &entry : global_config) {
    if (entry.name == name) {
      dest = entry;
      return true;
    }
  }
  return false;
}

bool Config::set_value(const std::string &name, const std::string &value_string) {
  for (auto &entry : global_config) {
    if (entry.name == name) {
      config_value_t value;
      switch (entry.type) {
        case ConfigType::BOOL:
          if (!utils::string_to_bool(value_string, value.bool_v)) {
            return false;
          }
          break;
        case ConfigType::UINT32:
          value.uint32_v = strtol(value_string.c_str(), nullptr, 10);
          if (!utils::is_in_range(value.uint32_v, entry.min.uint32_v, entry.max.uint32_v)) {
            return false;
          }
          break;
        case ConfigType::FLOAT:
          value.float_v = strtof(value_string.c_str(), nullptr);
          if (!utils::is_in_range(value.float_v, entry.min.float_v, entry.max.float_v)) {
            return false;
          }
          break;
      }
      entry.value = value;
      return true;
    }
  }
  return false;
}

void Config::save_default_config() {
  uint32_t i = 0;
  for (const auto &entry : global_config) {
    default_config[i++] = entry.value;
  }
}

void Config::reset_config() {
  uint32_t i = 0;
  for (auto &entry : global_config) {
    entry.value = default_config[i++];
  }
}

mbed_error_status_t Config::write_config_to_flash(mbed::FlashIAP &flash) {
  const size_t buf_size = sizeof(Config::config_value_t) * NUM_CONFIG_ENTRIES + sizeof(uint32_t);
  uint8_t buf[buf_size] = {0};

  Config::config_value_t *values = (Config::config_value_t *) buf;
  for (uint32_t i = 0; i < NUM_CONFIG_ENTRIES; ++i) {
    values[i] = Config::global_config[i].value;
  }

  uint32_t crc = utils::calc_crc32((const void *) buf, buf_size - sizeof(uint32_t));
  memcpy((void *) &buf[buf_size - sizeof(uint32_t)], (const void *) &crc, sizeof(uint32_t));

  TRY(write_to_flash(flash, STORAGE_ADDR_CONFIG, buf, buf_size));

  return MBED_SUCCESS;
}

mbed_error_status_t Config::write_to_flash(mbed::FlashIAP &flash, uint32_t address, uint8_t *source, size_t size) {
  if (flash.init() != 0) {
    LOG(LVL_ERROR, "Flash storage initialization failed");
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  if (size > flash.get_sector_size(address)) {
    LOG(LVL_ERROR, "Could not write config with 0x%x bytes to address 0x%08x. Size too big!", size, address);
    return MBED_ERROR_INVALID_SIZE;
  }

  if (flash.erase(STORAGE_ADDR_CONFIG, flash.get_sector_size(STORAGE_ADDR_CONFIG)) != 0) {
    LOG(LVL_ERROR, "Could not write config with 0x%x bytes to address 0x%08x. Erase failed!", size, address);
    return MBED_ERROR_WRITE_FAILED;
  }

  if (flash.program(source, STORAGE_ADDR_CONFIG, size) != 0) {
    LOG(LVL_ERROR, "Could not write config with 0x%x bytes to address 0x%08x. Write failed!", size, address);
    return MBED_ERROR_WRITE_FAILED;
  }

  if (flash.deinit() != 0) {
    LOG(LVL_ERROR, "Flash storage deinitialization failed");
    return MBED_ERROR_FAILED_OPERATION;
  }

  return MBED_SUCCESS;
}

mbed_error_status_t Config::read_config_from_flash(mbed::FlashIAP &flash) {
  const size_t buf_size = sizeof(Config::config_value_t) * NUM_CONFIG_ENTRIES + sizeof(uint32_t);
  uint8_t buf[buf_size] = {0};
  TRY(read_from_flash(flash, STORAGE_ADDR_CONFIG, buf, buf_size));

  uint32_t calc_crc = utils::calc_crc32((const void *) buf, buf_size - sizeof(uint32_t));
  uint32_t stored_crc = 0;
  memcpy((void *) &stored_crc, (const void *) &buf[buf_size - sizeof(uint32_t)], sizeof(uint32_t));

  if (calc_crc != stored_crc) {
    LOG(LVL_INFO, "No config found at address 0x%08x. Use default config.", STORAGE_ADDR_CONFIG);
    return MBED_SUCCESS;
  } else

    LOG(LVL_INFO, "Config found at address 0x%08x. Load config from flash.", STORAGE_ADDR_CONFIG);

  Config::config_value_t *values = (Config::config_value_t *) buf;
  for (uint32_t i = 0; i < NUM_CONFIG_ENTRIES; ++i) {
    Config::global_config[i].value = values[i];
  }

  return MBED_SUCCESS;
}

mbed_error_status_t Config::read_from_flash(mbed::FlashIAP &flash, uint32_t address, uint8_t *destination,
                                            size_t size) {
  if (flash.init() != 0) {
    LOG(LVL_ERROR, "Flash storage initialization failed");
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  if (size > flash.get_sector_size(address)) {
    LOG(LVL_ERROR, "Could not read config with 0x%x bytes from address 0x%08x. Size too big!", size, address);
    return MBED_ERROR_INVALID_SIZE;
  }

  if (flash.read(destination, address, size) != 0) {
    LOG(LVL_ERROR, "Could not read config with 0x%x bytes from address 0x%08x. Read failed!", size, address);
    return MBED_ERROR_READ_FAILED;
  }

  if (flash.deinit() != 0) {
    LOG(LVL_ERROR, "Flash storage deinitialization failed");
    return MBED_ERROR_FAILED_OPERATION;
  }

  return MBED_SUCCESS;
}