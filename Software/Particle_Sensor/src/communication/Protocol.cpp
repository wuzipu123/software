#include "Protocol.h"
#include "MbedCRC.h"
#include "mbed_error.h"
#include "mbed_debug.h"
#include "utils.h"
#include "Logger.h"

#define SMARTMOTE_AUTH_ID     0xff
#define SMARTMOTE_HW_ID       0x4220
#define SMARTMOTE_ACK         0x5a
#define MEASURED_DATA_TYPE_ID 32
#define STATUS_DATA_TYPE_ID   39

Protocol::Protocol(Lora &lora) : _lora(lora) {
}

uint32_t Protocol::get_hw_uuid() {
  uint32_t uuid[3] = {0};
  uuid[0] = HAL_GetUIDw0();
  uuid[1] = HAL_GetUIDw1();
  uuid[2] = HAL_GetUIDw2();
  return utils::calc_crc32((const void *) uuid, 12);
}

uint32_t Protocol::get_sw_uuid() {
  std::string sw_version = utils::app_version();
  return utils::calc_crc32((const void *) sw_version.c_str(), sw_version.size());
}

void Protocol::auth_reset() {
  _client_auth_done = false;
  _node_crc = 0;
  _base_crc = 0;
}

void Protocol::send_auth() {
  node_auth_t node_auth;
  auth_reset();

  if (_node_crc == 0) {
    _node_crc = (uint16_t) utils::get_rand();
  }

  node_auth.smartmote_auth_id = SMARTMOTE_AUTH_ID;
  node_auth.node_crc = _node_crc;
  node_auth.hw_id = SMARTMOTE_HW_ID;
  node_auth.hw_uuid = get_hw_uuid();
  node_auth.sw_uuid = get_sw_uuid();
  node_auth.crc = utils::calc_crc16((const void *) &node_auth, sizeof(node_auth_t) - sizeof(uint16_t));

  _lora.send((uint8_t *) &node_auth, sizeof(node_auth_t));
}

mbed_error_status_t Protocol::read_received() {
  if (!_client_auth_done) {
    return check_auth(_lora.rx_payload, _lora.rx_payload_len);
  }
  if (_node_crc && _base_crc) {
    return check_ack(_lora.rx_payload, _lora.rx_payload_len);
  }
  return MBED_SUCCESS;
}

mbed_error_status_t Protocol::check_ack(const uint8_t *buf, uint16_t size) {
  if (size != sizeof(base_ack_t)) {
    LOG(LVL_DEBUG, "base ack len fail: %u, should be: %zu", size, sizeof(base_ack_t));
    return MBED_ERROR_INVALID_SIZE;
  }

  if (MBED_SUCCESS != crc_check(buf, size)) {
    LOG(LVL_DEBUG, "base ack CRC failed!");
    return MBED_ERROR_CRC_ERROR;
  }

  base_ack_t *base_ack = (base_ack_t *) buf;
  if (base_ack->node_id != _node_id) {
    LOG(LVL_DEBUG, "base ack wrong node ID!");
    return MBED_ERROR_INVALID_DATA_DETECTED;
  }

  if (base_ack->ack != SMARTMOTE_ACK) {
    LOG(LVL_DEBUG, "base ack wrong ACK(not 0x5a)!");
    auth_reset();
    return MBED_ERROR_FAILED_OPERATION;
  }

  return MBED_SUCCESS;
}

mbed_error_status_t Protocol::check_auth(const uint8_t *buf, uint16_t size) {
  if (size != sizeof(base_auth_t)) {
    LOG(LVL_DEBUG, "base auth len fail: %u, should be: %zu", size, sizeof(base_auth_t));
    return MBED_ERROR_INVALID_SIZE;
  }

  base_auth_t *base_auth = (base_auth_t *) buf;
  LOG(LVL_DEBUG, "base crc: 0x%04x nodeid: %d", base_auth->base_crc, base_auth->node_id);
  _base_crc = base_auth->base_crc;

  if (MBED_SUCCESS != crc_check(buf, size)) {
    LOG(LVL_DEBUG, "base auth CRC failed!");
    auth_reset();
    return MBED_ERROR_CRC_ERROR;
  }

  _node_id = base_auth->node_id;
  _client_auth_done = true;

  return MBED_SUCCESS;
}

mbed_error_status_t Protocol::crc_check(const uint8_t *buf, uint16_t size) {
  uint8_t *crc_buf = (uint8_t *) malloc(size + sizeof(uint16_t));
  memcpy(crc_buf, buf, size);
  memcpy(crc_buf + size - sizeof(uint16_t), &_node_crc, sizeof(uint16_t));
  memcpy(crc_buf + size, &_base_crc, sizeof(uint16_t));
  uint16_t crc_calc = utils::calc_crc16(crc_buf, size + sizeof(uint16_t));
  free(crc_buf);

  uint16_t crc;
  memcpy(&crc, &buf[size - sizeof(uint16_t)], sizeof(uint16_t));

  if (crc != crc_calc) {
    return MBED_ERROR_CRC_ERROR;
  }

  return MBED_SUCCESS;
}

void Protocol::send_measured_data(const measured_data_t &measured_data) {
  node_measured_data_t data;

  data.node_id = _node_id;
  data.type_id = MEASURED_DATA_TYPE_ID;
  data.values = measured_data;
  data.crc = _base_crc;
  data.temp_crc = _node_crc;
  data.crc = utils::calc_crc16((uint8_t *) &data, sizeof(node_measured_data_t));

  int send_len = sizeof(node_measured_data_t) - sizeof(node_measured_data_t::temp_crc);
  _lora.send((uint8_t *) &data, send_len);
}

void Protocol::send_status_data(const status_data_t &status_data) {
  node_status_data_t data;

  data.node_id = _node_id;
  data.type_id = STATUS_DATA_TYPE_ID;
  data.values = status_data;
  data.crc = _base_crc;
  data.temp_crc = _node_crc;
  data.crc = utils::calc_crc16((uint8_t *) &data, sizeof(node_status_data_t));

  int send_len = sizeof(node_status_data_t) - sizeof(node_status_data_t::temp_crc);
  _lora.send((uint8_t *) &data, send_len);
}

bool Protocol::is_auth_done() {
  return _client_auth_done;
}
