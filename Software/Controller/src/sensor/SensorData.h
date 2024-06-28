
#ifndef CONTROLLER_SENSORDATA_H
#define CONTROLLER_SENSORDATA_H

#include "ArduinoJson.h"
#include "mbed_error.h"
#include <string>
#include <vector>

/**
 * Class holding information about the sensor, sensor board and
 * the last measured values.
 */
class SensorData {
public:
  /**
   * Enum defining the data types for the measured values from the sensor board
   */
  enum DatasetTypes {
    FLOAT32, //!< 32-bit floating point number
    UINT32   //!< 32-bit unsigned integer number
  };

  /**
   * Create a SensorData object
   *
   * @param address The slave address of the sensor board
   */
  explicit SensorData(uint8_t address);

  /**
   * Default destructor
   */
  virtual ~SensorData() = default;

  /**
   * Constructs the header for the measurement data CSV file
   *
   * @param dest Reference to the string where the header is written to
   */
  void get_csv_header(std::string &dest);

  /**
   * Constructs a new entry for the measurement data CSV file with the current time stamp
   * and the measurement values from #datasets.
   *
   * @param dest Reference to the string where the line is written to
   */
  void get_csv_data(std::string &dest);

  /**
   * Deserialization of the \p json_string and storing the sensor information
   * into the members of this SensorData object.
   *
   * @param json_string Reference to the JSON string containing the sensor info
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  int from_json(const std::string &json_string);

  /** Struct defining the information for every characteristic the sensor can measure */
  struct dataset_info_s {
    std::string name; //!< Name of the measured characteristic
    std::string unit; //!< Unit of the measured characteristic
  };

  typedef struct dataset_info_s dataset_info_t;


  /** Name of the sensor, e.g. SPS30 */
  std::string name;
  /** Type of the sensor, e.g. Particle Sensor */
  std::string type;
  /** (Highest) supported protocol version, e.g. 2.0 */
  std::string protocol_version;
  /** Data type that will be used to send the #datasets */
  DatasetTypes data_type = DatasetTypes::FLOAT32;
  /** Information about the measured characteristics */
  std::vector<dataset_info_t> dataset_infos;
  /** Slave address of the sensor board */
  uint8_t address = 255;
  /** Startup time for the sensor */
  int startup_time = -1;
  /** Number of datasets that will sent by the sensor board */
  int num_datasets = -1;
  /** Minimum time between two consecutive measurements */
  int min_sample_time = -1;
  /** Flag to state if the sensor supports setting the data ready flag after startup */
  bool supports_data_ready = false;
  /** Flag to state if the sensor can stay powered on between the measurements */
  bool supports_keep_alive = false;

  /** Last #num_datasets measured values */
  std::vector<float> datasets;

  /**
   * Extracts the value with the given \p key out of the \p json_doc and
   * writes it to \p dest.
   *
   * @tparam T       The Output type of \p dest
   * @param json_doc The JsonDocument containing the deserialized sensor information
   * @param key      The key to the searched value
   * @param dest     The destination to write the searched value to
   */
  template<typename T>
  static void get_value_from_json(const DynamicJsonDocument &json_doc, const char *key, T &dest);

  /**
   * Extracts info about the datasets at the given \p key out of the \p json_doc and
   * writes it to the vector \p dest.
   *
   * @param json_doc The JsonDocument containing the deserialized sensor information
   * @param key      The key to the searched dataset information
   * @param dest     The destination to write the dataset info to
   */
  static void
  get_dataset_infos(const DynamicJsonDocument &json_doc, const char *key, std::vector<dataset_info_t> &dest);
};


#endif //CONTROLLER_SENSORDATA_H
