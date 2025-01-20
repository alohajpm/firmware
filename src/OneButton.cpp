/*
  OneButton.cpp - Library for detecting clicks and releases of a single button.
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

#include "OneButton.h"

#include <Arduino.h>

// ----- Constructor -----

// _pin _activeLow _pullupActive
OneButton::OneButton(int pin, bool activeLow /* = true */, bool pullupActive /* = true */) {
  _pin = pin;
  _activeLow = activeLow;
  _pullupActive = pullupActive;

}  // OneButton


// explicitly set the number of millisec that have to pass by before a click is assumed as safe.
void OneButton::setClickTicks(int ticks) {
  _clickTicks = ticks;
}  // setClickTicks


void OneButton::setClicksMore(int clicks) {
  _nClicksTarget = clicks;
}  // setClicksMore


// explicitly set the number of millisec that have to pass by before a long button press is detected.
void OneButton::setPressTicks(int ticks) {
  _pressTicks = ticks;
}  // setPressTicks


// save function for click event
void OneButton::attachClick(void (*function)()) {
  _clickFunc = function;
}  // attachClick


// save function for doubleClick event
void OneButton::attachDoubleClick(void (*function)()) {
  _doubleClickFunc = function;
}  // attachDoubleClick


// save function for multiClick event
void OneButton::attachMultiClick(void (*function)(int)) {
  _multiClickFunc = function;
}  // attachMultiClick


// save function for longPressStart event
void OneButton::attachLongPressStart(void (*function)()) {
  _longPressStartFunc = function;
}  // attachLongPressStart


// save function for longPressing event
void OneButton::attachLongPressing(void (*function)(int)) {
  _longPressingFunc = function;
}  // attachLongPressing


// save function for longPressStop event
void OneButton::attachLongPressStop(void (*function)(int)) {
  _longPressStopFunc = function;
}  // attachLongPressStop


// save function for during long press event
void OneButton::attachDuringLongPress(void (*function)(int)) {
  _duringLongPressFunc = function;
}  // attachDuringLongPress


/**
 * @brief Check input of the configured pin and then advance the finite state
 * machine (FSM).
 */
void OneButton::tick(bool activeLevel) {
  if (_pin >= 0) {
    if (activeLevel) {
      // hardware button is pressed.
      checkPressed();
    } else {
      // hardware button is released.
      checkReleased();
    }  // if
  }    // if
}  // OneButton.tick


void OneButton::tick() {
  int buttonLevel = digitalRead(_pin);
  tick(buttonLevel == _activeLow);
}


/**
 * @brief Check to see if the button has been pressed
 */
void OneButton::checkPressed(void) {
  unsigned long now = millis();

  if (_bState == BSTATE_IDLE) {
    // start of a button down sequence
    _bState = BSTATE_PRESSED;
    _startTime = now;  // remember starting time
    _nClicks = 0;      // reset double click counter
    _longPressTime = 0;

  } else if (_bState == BSTATE_PRESSED) {
    // waiting for stable state
    if ((_longPressTime == 0) && (_startTime + _pressTicks < now)) {
      _longPressTime = now;  // remember long press time
      _bState = BSTATE_LONGPRESSED;
      if (_longPressStartFunc) _longPressStartFunc();

    } else if ((_longPressTime > 0) && (_longPressTime + 100 < now)) {
      _longPressTime = now;
      if (_longPressingFunc) _longPressingFunc(now - _startTime);
    }

  } else if (_bState == BSTATE_LONGPRESSED) {
    // waiting for release of button
    if (_longPressingFunc) _longPressingFunc(now - _startTime);

  } else if (_bState == BSTATE_FINISHED) {
    // waiting for click sequence to start
    _bState = BSTATE_PRESSED;
    _startTime = now;  // remember starting time
    _nClicks = 0;      // reset double click counter
    _longPressTime = 0;

  }  // if
}  // OneButton.checkPressed()


/**
 * @brief Check to see if the button has been released
 */
void OneButton::checkReleased(void) {
  unsigned long now = millis();

  if (_bState == BSTATE_PRESSED) {
    // button was released after short press
    _clickTime = now;  // remember time of click.
    _nClicks++;        // count one more click
    if (_nClicks == _nClicksTarget) {
      // sequence finished
      _bState = BSTATE_FINISHED;
      if (_multiClickFunc) {
        _multiClickFunc(_nClicks);
      } else if (_doubleClickFunc) {
        _doubleClickFunc();
      } else if (_clickFunc) {
        _clickFunc();
      }  // if

    } else {
      _bState = BSTATE_IDLE;
    }  // if

  } else if (_bState == BSTATE_LONGPRESSED) {
    // button was released after long press
    _bState = BSTATE_IDLE;
    if (_longPressStopFunc) _longPressStopFunc(now - _startTime);

  } else if (_bState == BSTATE_FINISHED) {
    if (_clickTime + _clickTicks < now) {
      // restart click sequence
      _bState = BSTATE_IDLE;
      _nClicks = 0;
    }  // if
  }    // if
}  // OneButton.checkReleased()


// save function for click event
OneButton &OneButton::attach(clickFunc_t f) {
  _clickFunc = f;
  return *this;
}  // attach


// save function for doubleClick event
OneButton &OneButton::attach(doubleClickFunc_t f) {
  _doubleClickFunc = f;
  return *this;
}  // attach


// save function for multiClick event
OneButton &OneButton::attach(multiClickFunc_t f) {
  _multiClickFunc = f;
  return *this;
}  // attach


// save function for longPressStart event
OneButton &OneButton::attach(longPressStartFunc_t f) {
  _longPressStartFunc = f;
  return *this;
}  // attach


// save function for longPressing event
OneButton &OneButton::attach(longPressingFunc_t f) {
  _longPressingFunc = f;
  return *this;
}  // attach


// save function for longPressStop event
OneButton &OneButton::attach(longPressStopFunc_t f) {
  _longPressStopFunc = f;
  return *this;
}  // attach


// save function for during long press event
OneButton &OneButton::attach(duringLongPressFunc_t f) {
  _duringLongPressFunc = f;
  return *this;
}  // attach


void OneButton::reset(void) {
  _pin = -1;                // indicates: not configured.
  _bState = BSTATE_IDLE;    // reset state
  _startTime = 0;           // start time for longpress
  _clickTime = 0;           // start time for click counting
  _longPressTime = 0;       // start time for longpress
  _nClicks = 0;
}

/**
 * @brief return the current state of the button or the FSM
 * @return OneButton_State
 */
OneButton_State OneButton::getState(void) {
  return (_bState);
}


/**
 * @brief return the number of clicks detected by the state machine.
 * 
 * @return int
 */
int OneButton::getClicks(void) {
  return (_nClicks);
}


/**
 * @brief return the number of ticks the button was last pressed.
 * 
 * @return int
 */
int OneButton::getTimeSinceLastEvent(void) {
  return (millis() - _startTime);
}


/**
 * @brief return the number of ticks the button was last released.
 * 
 * @return int
 */
int OneButton::getTimeSinceLastRelease(void) {
  return (millis() - _clickTime);
}


/**
 * @brief return the number of ticks the button was last pressed.
 * 
 * @return int
 */
int OneButton::getTimeSinceLastPress(void) {
  return (millis() - _longPressTime);
}


/**
   @brief Check if the button is pressed.
   @brief This function is true when the button input reports true and the time has not expired.
   @return true when the button is pressed, false otherwise.
 */
bool OneButton::isPressed(void) {
  return ((_pin != -1) && (_bState != BSTATE_IDLE));
}  // isPressed()

// end.