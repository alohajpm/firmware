/*
  Thread.cpp - Implementation of in-object threading, using the
  Threading functions provided by the Arduino core (or wiring extensions)
  Created by Luiz H. Cassettari, March 28, 2015.
  Released into the public domain.
*/

#include "Thread.h"
#include "ThreadController.h"

// int Thread::__nextId = 0; // not implemented due to a possible bug on core

Thread::Thread() {
  _id = 0; //__nextId++;
  _enabled = false;
  _running = false;
  _interval = 0;
  _iterations = 0; // run forever
  _runs = 0;
  _onRun = NULL;
  _onYield = NULL;
  _onDisable = NULL;
  _onEnable = NULL;
  _onDestroy = NULL;
  _onTerminate = NULL;
  _onCheck = NULL;
  _previous = 0;
  _ran = false;
}

void Thread::setInterval(long interval) {
  _interval = interval;
  _previous = 0;
}

long Thread::getInterval() {
  return _interval;
}

void Thread::setIterations(int iterations) {
  _iterations = iterations;
}

int Thread::getIterations() {
  return _iterations;
}

void Thread::setRuns(int runs) {
  _runs = runs;
}

int Thread::getRuns() {
  return _runs;
}

void Thread::setup() {}
void Thread::loop() {}

void Thread::run() {
  if (_onCheck != NULL) _onCheck();
  if (_enabled && (millis() - _previous >= (unsigned long)_interval)) {
    _previous = millis();
    _ran = true;
    _running = true;
    if (_onRun != NULL) {
      _onRun();
    }
    this->loop();
    if (_iterations > 0) {
      _runs++;
      if (_runs == _iterations) {
        _enabled = false;
        if (_onTerminate != NULL) _onTerminate();
      }
    }
    _running = false;
    if (_onYield != NULL) {
      _onYield();
    }
  }
}

void Thread::onRun( void (*callback)() ) {
  _onRun = callback;
}

void Thread::onYield( void (*callback)() ) {
  _onYield = callback;
}

void Thread::onDisable( void (*callback)() ) {
  _onDisable = callback;
}

void Thread::onEnable( void (*callback)() ) {
  _onEnable = callback;
}

void Thread::onDestroy( void (*callback)() ) {
  _onDestroy = callback;
}

void Thread::onTerminate( void (*callback)() ) {
  _onTerminate = callback;
}

void Thread::onCheck( void (*callback)() ) {
  _onCheck = callback;
}

void Thread::detach( void (*callback)() ) {
  if (_onRun == callback) _onRun = NULL;
  if (_onYield == callback) _onYield = NULL;
  if (_onDisable == callback) _onDisable = NULL;
  if (_onEnable == callback) _onEnable = NULL;
  if (_onDestroy == callback) _onDestroy = NULL;
  if (_onTerminate == callback) _onTerminate = NULL;
  if (_onCheck == callback) _onCheck = NULL;
}

void Thread::yield() {
  if (_onYield != NULL) {
    _onYield();
  }
}

void Thread::start() {
  setInterval(0);
  this->enable();
  if (!ThreadController.add(this)) delete this;
}

void Thread::start(long interval) {
  setInterval(interval);
  this->enable();
  if (!ThreadController.add(this)) delete this;
}

void Thread::enable() {
  if (!_enabled) {
    _enabled = true;
    _previous = millis();
    if (_onEnable != NULL) _onEnable();
  }
}

void Thread::disable() {
  if (_enabled) {
    _enabled = false;
    if (_onDisable != NULL) _onDisable();
  }
}

bool Thread::isEnabled() {
  return _enabled