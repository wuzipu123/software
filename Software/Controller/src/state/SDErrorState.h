
#ifndef CONTROLLER_SDERRORSTATE_H
#define CONTROLLER_SDERRORSTATE_H

#include "State.h"
#include "EventFlags.h"
#include "SDCard.h"

/**
 * State that is entered if an SD error occurs or the SD card is full.
 */
class SDErrorState : public State {
public:
  /**
   * Create a SDErrorState
   *
   * @param led_indicator       Reference to the LedIndicator to set the LED behavior
   * @param sd_card             Reference to the SDCard to check why this state was entered
   * @param control_event_flags Reference to the control event flags to react on button presses and incoming commands.
   */
  SDErrorState(LedIndicator &led_indicator, SDCard &sd_card, rtos::EventFlags &control_event_flags);

  /**
   * Set the #_led_indicator behavior whether the SD card is full or it
   * behaves faulty.
   * Then wait for a button press to reset the controller or to format the SD card
   *
   * @return State::Result::RESET_PRESSED if the #CONTROL_FLAG_RESET was set,\n
   *         State::Result::FORMAT_SD_PRESSED if the #CONTROL_FLAG_FORMAT_SD was set
   */
  State::Result handle() override;

private:
  /**
   * Reference to the SD card
   */
  SDCard &_sd_card;

  /**
   * Reference to the control event flags object to wait for control events to occur
   */
  rtos::EventFlags &_control_event_flags;
};


#endif //CONTROLLER_SDERRORSTATE_H
