
#include "SensorData.h"
#include "Logger.h"
#include "utils.h"
#include <climits>

SensorData::SensorData(uint8_t address) : address(address) {
}

void SensorData::get_csv_header(std::string &dest) {
  dest.clear();
  dest += "Data Measurement of Sensor: " + name + "\n";
  std::string time_string;
  utils::get_formatted_time_string("%d.%m.%Y %T", time_string);
  dest += "Start Time: " + time_string + "\n";
  dest += "Sensortype: " + type + "\n";
  dest += "Timestamp;";
  for (const auto &dataset_info : dataset_infos) {
    dest += ";" + dataset_info.name + " [" + dataset_info.unit + "]";
  }
  dest += "\n";
}

void SensorData::get_csv_data(std::string &dest) {
  dest.clear();
  utils::get_formatted_time_string("%d.%m.%Y;%T", dest);
  for (const auto &value : datasets) {
    std::string num_string;
    utils::convert_to_exp_num_string(value, num_string);
    dest += ";" + num_string;
  }
  dest += "\n";
}

mbed_error_status_t SensorData::from_json(const std::string &json_string) {
  const size_t capacity = 4096;
  DynamicJsonDocument json_doc(capacity);
  DeserializationError deserialization_error = deserializeJson(json_doc, json_string);
  if (deserialization_error) {
    Logger::log(Logger::Module::SENSOR_DATA, Logger::Level::INFO,
                "JSON deserialization failed: " + std::string(deserialization_error.c_str()));
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_FAILED_OPERATION);
  }

  get_value_from_json(json_doc, "s_n", name);
  get_value_from_json(json_doc, "s_t", type);
  get_value_from_json(json_doc, "p_v", protocol_version);
  std::string data_type_string;
  get_value_from_json(json_doc, "d_t", data_type_string);
  data_type = data_type_string == "uint32" ? DatasetTypes::UINT32 : DatasetTypes::FLOAT32;

  get_value_from_json(json_doc, "su_t", startup_time);
  get_value_from_json(json_doc, "m_s_t", min_sample_time);
  get_value_from_json(json_doc, "n_o_d", num_datasets);
  get_value_from_json(json_doc, "s_d_r", supports_data_ready);
  get_value_from_json(json_doc, "s_k_a", supports_keep_alive);
  get_dataset_infos(json_doc, "datasets", dataset_infos);

  if (name.empty() || type.empty() || protocol_version.empty() || startup_time == -1 || num_datasets == -1
      || dataset_infos.empty() || static_cast<int>(dataset_infos.size()) != num_datasets) {
    Logger::log(Logger::Module::SENSOR_DATA, Logger::Level::INFO,
                "Missing Field(s) in sensor info. (s_n, s_t, p_v, su_t, n_o_d and datasets are necessary)");
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_ITEM_NOT_FOUND);
  }

  return MBED_SUCCESS;
}

template<typename T>
void SensorData::get_value_from_json(const DynamicJsonDocument &json_doc, const char *key, T &dest) {
  if (json_doc.containsKey(key)) {
    dest = json_doc[key].as<T>();
  }
}

void SensorData::get_dataset_infos(const DynamicJsonDocument &json_doc, const char *key,
                                   std::vector<dataset_info_t> &dest) {
  dest.clear();
  if (json_doc.containsKey(key)) {
    int dataset_size = json_doc[key].size();
    for (int i = 0; i < dataset_size; i++) {
      std::string dataset_name = json_doc[key][i]["d_n"];
      std::string dataset_unit = json_doc[key][i]["u"];
      if (!dataset_name.empty() && !dataset_unit.empty()) {
        dataset_info_t dataset_info = {dataset_name, dataset_unit};
        dest.push_back(dataset_info);
      }
    }
  }
}