
#include "gtest/gtest.h"
#include "JsonProtocol.h"
#include "SensorData.h"
#include <string>

class TestJsonProtocol : public testing::Test {
protected:
  JsonProtocol *protocol;
  SensorData *sensor_data;
  SensorBoardSerial *sensor_board_serial_dummy;

  std::string controller_read_msg;
  std::string controller_write_msg;
  uint8_t address = 5;

  virtual void SetUp() {
    controller_read_msg.clear();
    controller_write_msg.clear();
    sensor_data = new SensorData(address);
    sensor_data->data_type = SensorData::DatasetTypes::FLOAT32;
    sensor_data->num_datasets = 27;
    sensor_board_serial_dummy = new SensorBoardSerial(controller_read_msg, controller_write_msg);
    protocol = new JsonProtocol(*sensor_board_serial_dummy, *sensor_data);
  }

  virtual void TearDown() {
    delete sensor_data;
    delete sensor_board_serial_dummy;
    delete protocol;
  }
};

TEST_F(TestJsonProtocol, constructor) {
  EXPECT_TRUE(protocol);
}

TEST_F(TestJsonProtocol, get_sensor_info) {
  controller_read_msg += "\x02";
  controller_read_msg += std::string(R"({"s_n":"OPC-N3","s_t":"Particle Sensor","s_k_a":"true","n_o_d":"27","datasets":)"
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
                                     R"({"d_n":"t","u":"C_raw"},{"d_n":"h","u":"%_raw"}],{"d_n":"flow rate","u":"ml/s"},)"
                                     R"("su_t":"30","p_v":"1.0"})");
  controller_read_msg += "\x03";

  EXPECT_EQ(  protocol->get_sensor_info(), MBED_SUCCESS);

  std::string sensor_info_cmd_template;
  sensor_info_cmd_template += "\x02";
  sensor_info_cmd_template += R"({"s_a":"0x05","cmd":"send_info"})";
  sensor_info_cmd_template += "\x03\x03";
  EXPECT_EQ(controller_write_msg, sensor_info_cmd_template);

  EXPECT_EQ(sensor_data->name, "OPC-N3");
  EXPECT_EQ(sensor_data->type, "Particle Sensor");
  EXPECT_EQ(sensor_data->num_datasets, 27);
  EXPECT_EQ(sensor_data->protocol_version, "1.0");
  EXPECT_EQ(sensor_data->startup_time, 30);
  EXPECT_EQ(sensor_data->data_type, SensorData::DatasetTypes::FLOAT32);
  EXPECT_EQ(sensor_data->address, address);
  EXPECT_EQ(sensor_data->min_sample_time, -1);
  EXPECT_EQ(sensor_data->supports_data_ready, false);
  EXPECT_EQ(sensor_data->supports_keep_alive, true);
  EXPECT_EQ(sensor_data->dataset_infos.size(), 27);
  EXPECT_EQ(sensor_data->dataset_infos[0].name, "Bin0 350nm");
  EXPECT_EQ(sensor_data->dataset_infos[0].unit, "#/s");
  EXPECT_EQ(sensor_data->dataset_infos[26].name, "flow rate");
  EXPECT_EQ(sensor_data->dataset_infos[26].unit, "ml/s");
}

TEST_F(TestJsonProtocol, get_sensor_info_with_crc) {
  controller_read_msg += "\x02";
  controller_read_msg += std::string(R"({"s_n":"OPC-N3","s_t":"Particle Sensor","n_o_d":"27","datasets":)"
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
                                     R"({"d_n":"t","u":"C_raw"},{"d_n":"h","u":"%_raw"}],{"d_n":"flow rate","u":"ml/s"},)"
                                     R"("su_t":"30","p_v":"1.0"}DEC9)");
  controller_read_msg += "\x03";

  EXPECT_EQ(  protocol->get_sensor_info(), MBED_SUCCESS);
}

TEST_F(TestJsonProtocol, get_sensor_info_with_wrong_crc) {
  controller_read_msg += "\x02";
  controller_read_msg += std::string(R"({"s_n":"OPC-N3","s_t":"Particle Sensor","n_o_d":"27","datasets":)"
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
                                     R"({"d_n":"t","u":"C_raw"},{"d_n":"h","u":"%_raw"}],{"d_n":"flow rate","u":"ml/s"},)"
                                     R"("su_t":"30","p_v":"1.0"}DEAD)");
  controller_read_msg += "\x03";

  EXPECT_EQ(  protocol->get_sensor_info(), MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CRC_ERROR));
}

TEST_F(TestJsonProtocol, read_data) {
  controller_read_msg += "\x02";
  controller_read_msg += std::string(R"({"v":[{"v":"0000000490"},{"v":"0000000087"},{"v":"0000000043"},)"
                                     R"({"v":"0000000010"},{"v":"0000000014"},{"v":"0000000010"},{"v":"0000000001"},)"
                                     R"({"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},)"
                                     R"({"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},)"
                                     R"({"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},)"
                                     R"({"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},{"v":"0000000000"},)"
                                     R"({"v":"0000000000"},{"v":"0000026161"},{"v":"0000027877"},{"v":"0000000506"}]})");
  controller_read_msg += "\x03";

  EXPECT_EQ(  protocol->read_data(), MBED_SUCCESS);

  std::string sensor_read_cmd_template;
  sensor_read_cmd_template += "\x02";
  sensor_read_cmd_template += R"({"s_a":"0x05","cmd":"send_data"})";
  sensor_read_cmd_template += "\x03\x03";
  EXPECT_EQ(controller_write_msg, sensor_read_cmd_template);

  ASSERT_EQ(sensor_data->datasets.size(), 27);
  EXPECT_EQ(sensor_data->datasets[0], static_cast<float>(490));
  EXPECT_EQ(sensor_data->datasets[26], static_cast<float>(506));
}

TEST_F(TestJsonProtocol, init_measurement) {
  EXPECT_EQ(  protocol->init_measurement(), MBED_SUCCESS);

  std::string sensor_read_cmd_template;
  sensor_read_cmd_template += "\x02";
  sensor_read_cmd_template += R"({"s_a":"0x05","cmd":"init_meas"})";
  sensor_read_cmd_template += "\x03\x03";
  EXPECT_EQ(controller_write_msg, sensor_read_cmd_template);
}

TEST_F(TestJsonProtocol, stop_measurement) {
  EXPECT_EQ(  protocol->stop_measurement(), MBED_SUCCESS);

  std::string sensor_read_cmd_template;
  sensor_read_cmd_template += "\x02";
  sensor_read_cmd_template += R"({"s_a":"0x05","cmd":"sens_stop"})";
  sensor_read_cmd_template += "\x03\x03";
  EXPECT_EQ(controller_write_msg, sensor_read_cmd_template);
}