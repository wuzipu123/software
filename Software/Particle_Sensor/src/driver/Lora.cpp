
#include "Lora.h"
#include "defines.h"
#include "Logger.h"
#include "Config.h"

Lora::Lora() :
    rx_payload(),
    _radio(MBED_CONF_APP_SPI_MOSI,
           MBED_CONF_APP_SPI_MISO,
           MBED_CONF_APP_SPI_CLK,
           MBED_CONF_APP_LORA_CHIP_SELECT,
           MBED_CONF_APP_LORA_RESET,
           MBED_CONF_APP_LORA_DIO1,
           MBED_CONF_APP_LORA_BUSY,
           MBED_CONF_APP_LORA_FREQUENCY_SELECT,
           MBED_CONF_APP_LORA_DEVICE_SELECT,
           MBED_CONF_APP_LORA_XTAL_SELECT,
           MBED_CONF_APP_LORA_ANTENNA_SWITCH) {
}

void Lora::tx_done_cb() {
  LOG(LVL_DEBUG, "TX done callback!");
  _event_flags.set(FLAG_LORA_TX_DONE);
}

void Lora::rx_error_cb() {
  LOG(LVL_DEBUG, "RX error callback!");
}

void Lora::tx_timeout_cb() {
  LOG(LVL_DEBUG, "TX timeout callback!");
}

void Lora::rx_timeout_cb() {
  _event_flags.set(FLAG_LORA_RX_TIMEOUT);
}

void Lora::cad_done_cb(bool arg) {
  LOG(LVL_DEBUG, "CAD callback! %s", arg ? "true" : "false");
}

void Lora::rx_done_cb(const uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  if (Config::get<uint32_t>("log_level") == LVL_DEBUG) {
    char buf[LORA_CFG_RX_PAYLOAD_LEN * 3 + 2];
    for (int i = 0; i < size; ++i) {
      snprintf(buf + i * 3, 4, "%02x ", (char) payload[i]);
    }
    LOG(LVL_DEBUG, "RX done!, size: %d, rssi: %d, snr: %d, payload: %s", size, rssi, snr, buf);
  }

  memcpy(rx_payload, payload, size);
  rx_payload_len = size;
  rx_rssi = rssi;
  rx_snr = snr;
  _event_flags.set(FLAG_LORA_RX_DONE);
}

void Lora::fhss_change_channel_cb(uint8_t channel) {
  LOG(LVL_DEBUG, "fhss_change_channel_cb callback %d", channel);
}

void Lora::set_tx_config() {
  _radio.set_tx_config(LORA_CFG_MODEM,
                       Config::get<uint32_t>("lora_tx_power"),
                       LORA_CFG_TX_FDEV,
                       Config::get<uint32_t>("lora_bandwidth"),
                       Config::get<uint32_t>("lora_datarate"),
                       Config::get<uint32_t>("lora_coderate"),
                       Config::get<uint32_t>("lora_preamble_len"),
                       Config::get<bool>("lora_fix_len"),
                       Config::get<bool>("lora_crc_on"),
                       Config::get<bool>("lora_freq_hop_on"),
                       Config::get<uint32_t>("lora_hop_period"),
                       Config::get<bool>("lora_iq_inverted"),
                       Config::get<uint32_t>("lora_tx_timeout"));
}

void Lora::set_rx_config() {
  _radio.set_rx_config(LORA_CFG_MODEM,
                       Config::get<uint32_t>("lora_bandwidth"),
                       Config::get<uint32_t>("lora_datarate"),
                       Config::get<uint32_t>("lora_coderate"),
                       LORA_CFG_RX_BANDWITH_AFC,
                       Config::get<uint32_t>("lora_preamble_len"),
                       Config::get<uint32_t>("lora_rx_symb_timeout"),
                       Config::get<bool>("lora_fix_len"),
                       Config::get<uint32_t>("lora_rx_payload_len"),
                       Config::get<bool>("lora_crc_on"),
                       Config::get<bool>("lora_freq_hop_on"),
                       Config::get<uint32_t>("lora_hop_period"),
                       Config::get<bool>("lora_iq_inverted"),
                       Config::get<bool>("lora_rx_continuous"));
}

void Lora::init() {
  _radio_callbacks.tx_done = mbed::callback(this, &Lora::tx_done_cb);
  _radio_callbacks.rx_done = mbed::callback(this, &Lora::rx_done_cb);
  _radio_callbacks.rx_error = mbed::callback(this, &Lora::rx_error_cb);
  _radio_callbacks.tx_timeout = mbed::callback(this, &Lora::tx_timeout_cb);
  _radio_callbacks.rx_timeout = mbed::callback(this, &Lora::rx_timeout_cb);
  _radio_callbacks.fhss_change_channel = mbed::callback(this, &Lora::fhss_change_channel_cb);
  _radio_callbacks.cad_done = mbed::callback(this, &Lora::cad_done_cb);

  _radio.init_radio(&_radio_callbacks);

  _radio.set_channel(Config::get<uint32_t>("lora_carrier_freq"));

  set_tx_config();

  set_rx_config();

  LOG(LVL_DEBUG, "Init radio done!");
}

void Lora::send(uint8_t *data, uint8_t size) {
  if (Config::get<uint32_t>("log_level") == LVL_DEBUG) {
    char buf[LORA_CFG_RX_PAYLOAD_LEN * 3 + 2];
    for (int i = 0; i < size; ++i) {
      snprintf(buf + i * 3, 4, "%02x ", (char) data[i]);
    }
    LOG(LVL_DEBUG, "Send: %s, TOA: %dms", buf, _radio.time_on_air(MODEM_LORA, size));
  }
  _radio.standby();
  _radio.set_max_payload_length(MODEM_LORA, size);
  _radio.send(data, size);
  _event_flags.wait_all(FLAG_LORA_TX_DONE, 3000);
}

mbed_error_status_t Lora::receive() {
  _event_flags.clear();
  _radio.set_max_payload_length(MODEM_LORA, 0xff);
  _radio.receive();
  _rx_timeout.attach(mbed::callback(this, &Lora::rx_timeout_cb), std::chrono::milliseconds(LORA_RX_TIMEOUT_MS));
  uint32_t wait_flags = _event_flags.wait_any(FLAG_LORA_RX_TIMEOUT | FLAG_LORA_RX_DONE);
  _rx_timeout.detach();
  if (wait_flags & FLAG_LORA_RX_TIMEOUT) {
    LOG(LVL_INFO, "RX Timeout!");
    return MBED_ERROR_TIME_OUT;
  }
  return MBED_SUCCESS;
}

void Lora::sleep() {
  _radio.sleep();
}