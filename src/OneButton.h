/*
  OneButton.h - Library for detecting clicks and releases of a single button.
  Created by Matthias Hertel, matthias@িন্দা.de
  Copyright 2014-2022 Matthias Hertel.
  This work is licensed under a BSD style license. See here for license details:
  https://www.mathertel.de/License.aspx

  This library is implemented for the Arduino environment and is using the input pin features
  and a timer implementation.
  More information on: https://www.mathertel.de/Arduino/OneButtonLibrary.aspx

  History:
  24.05.2014 created
  04.09.2014 state machine explicit, all function calls inside, added longpress
  05.05.2015 added parameters, up to 4 buttons on one timer possible.
  15.05.2015 Simplified functions for one button on one timer.
  05.07.2015 Changed to using interrupts to detect preload and pressed states.
  02.12.2016 changed to new Style (state machine in class).
  21.08.2022 changed to c++ library.
  23.08.2022 renamed the class OneButton to avoid collisions with other libraries.
*/

#pragma once

#include <Arduino.h>

// ----- State definitions -----
// These states only change after a clickTime or a longPressTime.
// * No input event is known (idle).
// * Some time a button is in the pressed state.
// * Sequence of presses (clicks) is finished (doubleclick, trippleclick).
// * A button is pressed for long duration.

enum OneButton_State {
  BSTATE_IDLE = 0,
  BSTATE_PRESSED,
  BSTATE_FINISHED,
  BSTATE_LONGPRESSED
};

class OneButton {
public:
  /**
   * @brief Construct a new OneButton object
   * 
   * @param pin The pin that is attached to the button. Active LOW.
   * @param activeLow true when LOW is the active state of the button.
   * @param pullupActive Enable internal pullup resistor for the pin when activeLow is true.
   */
  OneButton(int pin, bool activeLow = true, bool pullupActive = true);

  // ----- Set runtime parameters -----

  /**
   * @brief set the interval time for detecting double and triple clicks.
   * @param clickTicks [in millis]
   */
  void setClickTicks(int clickTicks);

  /**
   * @brief set the number of clicks to detect a multi click.
   * @param nClicks up to 10, default is 2.
   */
  void setClicksMore(int nClicks = 2);

  /**
   * @brief set the duration for a long press.
   * @param pressTicks [in millis]
   */
  void setPressTicks(int pressTicks);

  // ----- Set callback routines -----

  /**
   * @brief attach a function to be called when even one click occurs.
   * @param f (callback function for click events)
   */
  void attachClick(void (*f)());

  /**
   * @brief attach a function to be called when a doubleclick occurs.
   * @param f (callback function for doubleclick events)
   */
  void attachDoubleClick(void (*f)());

  /**
   * @brief attach a function to be called when multiple clicks occur.
   * @param f (callback function for multi-click events with click count parameter)
   */
  void attachMultiClick(void (*f)(int));

  /**
   * @brief attach a function to be called when a long press occurs.
   * @param f (callback function for long press events)
   */
  void attachLongPressStart(void (*f)());

  /**
   * @brief attach a function to be called when a long press occurs.
   * @param f (callback function for long press events with duration parameter)
   */
  void attachLongPressing(void (*f)(int));

  /**
   * @brief attach a function to be called when a long press is released.
   * @param f (callback function for long press release events with duration parameter)
   */
  void attachLongPressStop(void (*f)(int));

  /**
   * @brief attach a function to be called when a during press occurs.
   * @param f (callback function for during press events with duration parameter)
   */
  void attachDuringLongPress(void (*f)(int));

  /**
   * @brief call this method in the loop() function.
   * 
   * @param forceState (can be used to trigger the event function when the state is changed outside.)
   */
  void tick(bool forceState = false);

  /**
   * @brief Reset the internal state machine.
   * 
   */
  void reset(void);

  /**
   * @brief return true when the button was pressed.
   */
  bool isPressed(void);

  /**
   * @brief return the state of the button or internal state.
   */
  OneButton_State getState(void);

  /**
   * @brief return the number of clicks that were detected.
   */
  int getClicks(void);

  /**
   * @brief return the time in millis since the last event.
   */
  int getTimeSinceLastEvent(void);

  /**
   * @brief return the time in millis since the last press event.
   */
  int getTimeSinceLastPress(void);

  /**
   * @brief return the time in millis since the last release event.
   */
  int getTimeSinceLastRelease(void);

protected:
  void checkPressed(void);
  void checkReleased(void);

  // ----- internal variables and constants
  int _pin;                      // Arduino pin where button is connected
  bool _activeLow;               // true: the button is active on low level
  bool _pullupActive;            // true: use internal pullup resistor for the button pin.
  bool _state = false;           // current state of the button (pressed / released)
  unsigned long _startTime = 0;  // the time when the button was pressed for the first time.
  int _longPressTime = 0;        // the time of the last long press detection.
  int _clickTime = 0;            // the time of the last click detection.
  int _nClicks = 0;              // the current number of clicks detected.

  OneButton_State _bState = BSTATE_IDLE;  // the internal state from last tick.

  int _clickTicks = 400;    // number of millisec that have to pass by before a click is detected.
  int _pressTicks = 800;    // number of millisec that have to pass by before a long button press is detected.
  int _nClicksTarget = 2;   // number of clicks to detect a multi click.

  // ----- function pointers for callbacks
  void (*_clickFunc)() = nullptr;
  void (*_doubleClickFunc)() = nullptr;
  void (*_multiClickFunc)(int) = nullptr;
  void (*_longPressStartFunc)() = nullptr;
  void (*_longPressingFunc)(int) = nullptr;
  void (*_longPressStopFunc)(int) = nullptr;
};

// end.