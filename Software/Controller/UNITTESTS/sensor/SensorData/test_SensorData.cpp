#include "gtest/gtest.h"
#include "SensorData.h"
#include <string>

class TestSensorData : public testing::Test {
protected:
  SensorData *sensor_data;

  std::string sensor_info_json;
  int address = 1;

  virtual void SetUp() {
    sensor_data = new SensorData(address);
    sensor_info_json = std::string(R"({"s_n":"OPC-N3","s_t":"Particle Sensor","n_o_d":"27","datasets":)"
                                   R"([{"d_n":"Bin0 350nm","u":"#/s"},{"d_n":"Bin1 460nm","u":"#/s"},)"
                                   R"({"d_n":"Bin2 660nm","u":"#/s"},{"d_n":"Bin3 1000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin4 1300nm","u":"#/s"},{"d_n":"Bin5 1700nm","u":"#/s"},)"
                                   R"({"d_n":"Bin6 2300nm","u":"#/s"},{"d_n":"Bin7 3000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin8 4000nm","u":"#/s"},{"d_n":"Bin9 5200nm","u":"#/s"},)"
                                   R"({"d_n":"Bin10 6500nm","u":"#/s"},{"d_n":"Bin11 8000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin12 10000nm","u":"#/s"},{"d_n":"Bin13 12000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin14 14000nm","u":"#/s"},{"d_n":"Bin15 16000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin16 18000nm","u":"#/s"},{"d_n":"Bin17 20000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin18 22000nm","u":"#/s"},{"d_n":"Bin19 25000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin20 28000nm","u":"#/s"},{"d_n":"Bin21 31000nm","u":"#/s"},)"
                                   R"({"d_n":"Bin22 34000nm","u":"#/s"},{"d_n":"Bin23 37000nm","u":"#/s"},)"
                                   R"({"d_n":"t","u":"C_raw"},{"d_n":"h","u":"%_raw"},{"d_n":"flow rate","u":"ml/s"}],)"
                                   R"("su_t":"30","p_v":"1.0"})");
  }

  virtual void TearDown() {
    delete sensor_data;
  }
};

TEST_F(TestSensorData, constructor) {
  EXPECT_TRUE(sensor_data);
}

TEST_F(TestSensorData, from_json) {
  EXPECT_EQ(sensor_data->from_json(sensor_info_json), 0);
  EXPECT_EQ(sensor_data->name, "OPC-N3");
  EXPECT_EQ(sensor_data->type, "Particle Sensor");
  EXPECT_EQ(sensor_data->num_datasets, 27);
  EXPECT_EQ(sensor_data->protocol_version, "1.0");
  EXPECT_EQ(sensor_data->startup_time, 30);
  EXPECT_EQ(sensor_data->data_type, SensorData::DatasetTypes::FLOAT32);
  EXPECT_EQ(sensor_data->address, address);
  EXPECT_EQ(sensor_data->min_sample_time, -1);
  EXPECT_EQ(sensor_data->supports_data_ready, false);
  EXPECT_EQ(sensor_data->supports_keep_alive, false);
  EXPECT_EQ(sensor_data->dataset_infos.size(), 27);
  EXPECT_EQ(sensor_data->dataset_infos[0].name, "Bin0 350nm");
  EXPECT_EQ(sensor_data->dataset_infos[0].unit, "#/s");
  EXPECT_EQ(sensor_data->dataset_infos[26].name, "flow rate");
  EXPECT_EQ(sensor_data->dataset_infos[26].unit, "ml/s");
}

TEST_F(TestSensorData, from_json_deserialization_fail) {
  sensor_info_json.insert(6, "x");
  EXPECT_EQ(sensor_data->from_json(sensor_info_json),
            MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_FAILED_OPERATION));
}

TEST_F(TestSensorData, get_csv_header) {
  sensor_data->from_json(sensor_info_json);

  std::string csv_header_string;
  sensor_data->get_csv_header(csv_header_string);
  std::string template_string(
      "Data Measurement of Sensor: OPC-N3\n"
      "Start Time: 10.12.2019 12:57:47\n"
      "Sensortype: Particle Sensor\n"
      "Timestamp;;Bin0 350nm [#/s];Bin1 460nm [#/s];Bin2 660nm [#/s];Bin3 1000nm [#/s];Bin4 1300nm [#/s];"
      "Bin5 1700nm [#/s];Bin6 2300nm [#/s];Bin7 3000nm [#/s];Bin8 4000nm [#/s];Bin9 5200nm [#/s];"
      "Bin10 6500nm [#/s];Bin11 8000nm [#/s];Bin12 10000nm [#/s];Bin13 12000nm [#/s];Bin14 14000nm [#/s];"
      "Bin15 16000nm [#/s];Bin16 18000nm [#/s];Bin17 20000nm [#/s];Bin18 22000nm [#/s];Bin19 25000nm [#/s];"
      "Bin20 28000nm [#/s];Bin21 31000nm [#/s];Bin22 34000nm [#/s];Bin23 37000nm [#/s];t [C_raw];h [%_raw];"
      "flow rate [ml/s]\n");

  EXPECT_EQ(csv_header_string, template_string);
}

TEST_F(TestSensorData, get_csv_data_float) {
  sensor_data->from_json(sensor_info_json);
  sensor_data->data_type = SensorData::DatasetTypes::FLOAT32;
  sensor_data->datasets.push_back({490.0f});
  sensor_data->datasets.push_back({87.0f});
  sensor_data->datasets.push_back({43.0f});
  sensor_data->datasets.push_back({10.0f});
  sensor_data->datasets.push_back({14.0f});
  sensor_data->datasets.push_back({10.0f});
  sensor_data->datasets.push_back({1.0f});
  for (int i = 0; i < 17; i++) {
    sensor_data->datasets.push_back({0.0f});
  }
  sensor_data->datasets.push_back({26161.0f});
  sensor_data->datasets.push_back({27877.0f});
  sensor_data->datasets.push_back({506.0f});

  std::string csv_data_string;
  sensor_data->get_csv_data(csv_data_string);
  std::string template_string(
      "10.12.2019;12:57:47;4.900000000e+02;8.700000000e+01;4.300000000e+01;1.000000000e+01;1.400000000e+01"
      ";1.000000000e+01;1.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;"
      "0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0"
      ".000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0.000000000e+00;0"
      ".000000000e+00;2.616100000e+04;2.787700000e+04;5.060000000e+02\n");

  EXPECT_EQ(csv_data_string, template_string);
}