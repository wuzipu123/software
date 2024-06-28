#include "mbed.h"
#include "SX126X_LoRaRadio.h"
#include "ns_cmdline.h"

#define LORA_CFG_CARRIER_FREQ     868000000

#define LORA_CFG_MODEM            MODEM_LORA
#define LORA_CFG_BANDWIDTH        0
#define LORA_CFG_DATARATE         12
#define LORA_CFG_CODERATE         1
#define LORA_CFG_PREAMBLE_LEN     8
#define LORA_CFG_FIX_LEN          false
#define LORA_CFG_CRC_ON           true
#define LORA_CFG_FREQ_HOP_ON      false
#define LORA_CFG_HOP_PERIOD       4
#define LORA_CFG_IQ_INVERTED      false

#define LORA_CFG_TX_POWER         0
#define LORA_CFG_TX_FDEV          25000
#define LORA_CFG_TX_TIMEOUT       3000

#define LORA_CFG_RX_BANDWITH_AFC  0
#define LORA_CFG_RX_SYMB_TIMEOUT  255
#define LORA_CFG_RX_PAYLOAD_LEN   255
#define LORA_CFG_RX_CONTINUOUS    true

#define EVENT_FLAG_BUTTON         (1U<<0)
#define EVENT_FLAG_RX_PING        (1U<<1)
#define EVENT_FLAG_TX_DONE        (1U<<2)

EventFlags flags;
radio_events_t radio_cbs;
DigitalOut green_led(MBED_CONF_APP_STATE_LED_GREEN, false);
DigitalOut red_led(MBED_CONF_APP_STATE_LED_RED, false);
Timeout red_led_timeout;
Timeout green_led_timeout;

SX126X_LoRaRadio radio(MBED_CONF_APP_SPI_MOSI,
                       MBED_CONF_APP_SPI_MISO,
                       MBED_CONF_APP_SPI_CLK,
                       MBED_CONF_APP_LORA_CHIP_SELECT,
                       MBED_CONF_APP_LORA_RESET,
                       MBED_CONF_APP_LORA_DIO1,
                       MBED_CONF_APP_LORA_BUSY,
                       MBED_CONF_APP_LORA_FREQUENCY_SELECT,
                       MBED_CONF_APP_LORA_DEVICE_SELECT,
                       MBED_CONF_APP_LORA_XTAL_SELECT,
                       MBED_CONF_APP_LORA_ANTENNA_SWITCH);

void green_led_off() {
  green_led = false;
}

void red_led_off() {
  red_led = false;
}

void tx_done_cb() {
  cmd_printf("TX done callback!\n");
  flags.set(EVENT_FLAG_TX_DONE);
}

void rx_error_cb() {
  cmd_printf("RX error callback!\n");
}

void tx_timeout_cb() {
  cmd_printf("TX timeout callback!\n");
}

void rx_timeout_cb() {
  cmd_printf("RX timeout callback!\n");
}

void cad_done_cb(bool arg) {
  cmd_printf("CAD callback! %s\n", arg ? "true" : "false");
}

void rx_done_cb(const uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  cmd_printf("RX done!, size: %d, rssi: %d, snr: %d, payload: ", size, rssi, snr);
  for (int i = 0; i < size; ++i) {
    cmd_printf("%02x ", (char) payload[i]);
  }
  cmd_printf("\n");
  green_led = true;
  green_led_timeout.attach(&green_led_off, std::chrono::milliseconds(500));
  if (size >= 4) {
    if (memcmp("PING", payload, 4) == 0) {
      flags.set(EVENT_FLAG_RX_PING);
    }
  }
}

void fhss_change_channel_cb(uint8_t channel) {
  cmd_printf("fhss_change_channel_cb callback %d\n", channel);
}

void init_radio() {
  radio_cbs.tx_done = mbed::callback(&tx_done_cb);
  radio_cbs.rx_done = mbed::callback(&rx_done_cb);
  radio_cbs.rx_error = mbed::callback(&rx_error_cb);
  radio_cbs.tx_timeout = mbed::callback(&tx_timeout_cb);
  radio_cbs.rx_timeout = mbed::callback(&rx_timeout_cb);
  radio_cbs.fhss_change_channel = mbed::callback(&fhss_change_channel_cb);
  radio_cbs.cad_done = mbed::callback(&cad_done_cb);

  radio.init_radio(&radio_cbs);

  radio.standby();

  radio.set_tx_config(LORA_CFG_MODEM,
                      LORA_CFG_TX_POWER,
                      LORA_CFG_TX_FDEV,
                      LORA_CFG_BANDWIDTH,
                      LORA_CFG_DATARATE,
                      LORA_CFG_CODERATE,
                      LORA_CFG_PREAMBLE_LEN,
                      LORA_CFG_FIX_LEN,
                      LORA_CFG_CRC_ON,
                      LORA_CFG_FREQ_HOP_ON,
                      LORA_CFG_HOP_PERIOD,
                      LORA_CFG_IQ_INVERTED,
                      LORA_CFG_TX_TIMEOUT);

  radio.set_rx_config(LORA_CFG_MODEM,
                      LORA_CFG_BANDWIDTH,
                      LORA_CFG_DATARATE,
                      LORA_CFG_CODERATE,
                      LORA_CFG_RX_BANDWITH_AFC,
                      LORA_CFG_PREAMBLE_LEN,
                      LORA_CFG_RX_SYMB_TIMEOUT,
                      LORA_CFG_FIX_LEN,
                      LORA_CFG_RX_PAYLOAD_LEN,
                      LORA_CFG_CRC_ON,
                      LORA_CFG_FREQ_HOP_ON,
                      LORA_CFG_HOP_PERIOD,
                      LORA_CFG_IQ_INVERTED,
                      LORA_CFG_RX_CONTINUOUS);

  radio.set_channel(LORA_CFG_CARRIER_FREQ);

  cmd_printf("Init radio done! Radio status: 0x%02x\n", radio.get_status());
}
void send_packet(uint8_t *data, uint8_t size) {
  cmd_printf("Send ");
  for (int i = 0; i < size; ++i) {
    cmd_printf("%02x ", (char)data[i]);
  }
  cmd_printf("\n");
  radio.set_max_payload_length(MODEM_LORA, size);
  radio.send(data, size);
  flags.wait_any(EVENT_FLAG_TX_DONE, 3000);
  red_led = true;
  red_led_timeout.attach(&red_led_off, std::chrono::milliseconds(500));
}

void radio_sleep() {
  radio.sleep();
}

void button_pressed() {
  flags.set(EVENT_FLAG_BUTTON);
}

int ping_pong() {
  InterruptIn button(MBED_CONF_APP_BUTTON_1);
  button.fall(&button_pressed);

  init_radio();

  while (true) {
    radio.receive();
    uint32_t wait_flags = flags.wait_any(EVENT_FLAG_BUTTON | EVENT_FLAG_RX_PING);
    if (wait_flags & EVENT_FLAG_BUTTON) {
      send_packet((uint8_t *)"PING", 4);
      //uint8_t buf[] = {0xff, 0x26, 0xa9, 0x20, 0x42, 0xd6, 0x84, 0x47, 0x27, 0x10, 0x7b, 0x5c, 0x59, 0x80, 0x73};
      //send_packet((uint8_t *)buf, 15);
    } else if (wait_flags & EVENT_FLAG_RX_PING) {
      send_packet((uint8_t *)"PONG", 4);
    }
  }
}