#include "Led.h"

Led::Led(PinName pin) : _behavior(Behavior::OFF),
                        _led(pin, State::OFF),
                        _period(1.0),
                        _ticker_on_attached(false),
                        _ticker_off_attached(false) {
}

void Led::set_behavior(Led::Behavior behavior) {
  _behavior = behavior;
  _ticker_on.detach();
  _ticker_off.detach();

  switch (behavior) {
    case Behavior::ON:
      _led = State::ON;
      break;
    case Behavior::OFF:
      _led = State::OFF;
      break;
    case Behavior::BLINK_250MS:
      _set_tickers(0.0, 0.25, 0.125);
      break;
    case Behavior::BLINK_1S:
      _set_tickers(0.0, 1.0, 0.25);
      break;
    case Behavior::BLINK_5S:
      _set_tickers(0.0, 5.0, 0.25);
      break;
    case Behavior::BLINK_15S:
      _set_tickers(0.0, 15.0, 0.25);
      break;
    case Behavior::BLINK_INV_2S:
      _set_tickers(0.0, 2.0, 1.75);
      break;
    default:
      _led = State::OFF;
      break;
  }
}

void Led::_set_tickers(float time_shift, float period, float on_time) {
  _period = period;
  _ticker_on_attached = false;
  _ticker_off_attached = false;

  if (time_shift < 0.01) {
    _led = State::ON;
    _ticker_on.attach(mbed::callback(this, &Led::_turn_on), _period);
    _ticker_on_attached = true;
    _ticker_off.attach(mbed::callback(this, &Led::_turn_off), on_time);
    return;
  }

  _led = State::OFF;
  _ticker_on.attach(mbed::callback(this, &Led::_turn_on), time_shift);
  _ticker_off.attach(mbed::callback(this, &Led::_turn_off), time_shift + on_time);
}

void Led::_turn_on() {
  if (!_ticker_on_attached) {
    _ticker_on.detach();
    _ticker_on.attach(mbed::callback(this, &Led::_turn_on), _period);
    _ticker_on_attached = true;
  }
  _led = State::ON;
}

void Led::_turn_off() {
  if (!_ticker_off_attached) {
    _ticker_off.detach();
    _ticker_off.attach(mbed::callback(this, &Led::_turn_off), _period);
    _ticker_off_attached = true;
  }
  _led = State::OFF;
}

Led::Behavior Led::get_behavior() const {
  return _behavior;
}
