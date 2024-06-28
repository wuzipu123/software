
#ifndef CONTROLLER_FORMATSDSTATE_H
#define CONTROLLER_FORMATSDSTATE_H

#include "State.h"
#include "SDCard.h"

/**
 * State to format the SD card
 */
class FormatSDState : public State {
public:
  /**
   * Create a FormatSDState
   *
   * @param led_indicator Reference to the LedIndicator to set the LED behavior
   * @param sd_card       Reference to the SDCard to format
   */
  explicit FormatSDState(LedIndicator &led_indicator, SDCard &sd_card);

  /**
   * Default destructor
   */
  ~FormatSDState() override = default;

  /**
   * Format the SD card by calling SDCard::format()
   *
   * @return State::Result::SUCCESS if formatting suceeded,\n
   *         State::Result::SD_CARD_ERROR otherwise
   */
  State::Result handle() override;

private:
  /**
   * Reference to the SDCard which should be formatted
   */
  SDCard &_sd_card;
};


#endif //CONTROLLER_FORMATSDSTATE_H
