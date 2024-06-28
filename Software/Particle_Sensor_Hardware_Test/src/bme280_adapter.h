//
// Created by stefan on 11.09.20.
//

#ifndef SENSOR_NODE_LORA_SPS30_HW_TEST_BME280_ADAPTER_H
#define SENSOR_NODE_LORA_SPS30_HW_TEST_BME280_ADAPTER_H


void user_delay_us(uint32_t period, void *intf_ptr);

void user_spi_init();

int8_t user_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t user_spi_write(uint8_t reg_addr, const unsigned char *reg_data, uint32_t len, void *intf_ptr);

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev, uint32_t num_measurements);

#endif //SENSOR_NODE_LORA_SPS30_HW_TEST_BME280_ADAPTER_H
