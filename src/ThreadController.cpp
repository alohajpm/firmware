/*
  ThreadController.cpp - Implementation of in-object threading, using the
  Threading functions provided by the Arduino core (or wiring extensions)
  Created by Luiz H. Cassettari, March 28, 2015.
  Released into the public domain.
*/

#include "ThreadController.h"

Thread *ThreadController::_threads[MAX_THREADS];
int ThreadController::_total = 0;

ThreadController::ThreadController() {}

ThreadController::~ThreadController() {}

bool ThreadController::add(Thread *thread) {
  if (_total < MAX_THREADS) {
    thread->_id = _total;
    _threads[_total] = thread;
    _total++;
    return true;
  }
  return false;
}

void ThreadController::remove(Thread *thread) {
  if (_total > 0) {
    int id = thread->getId();
    if (_threads[id] == thread) {
      for (int i = id; i < _total - 1; i++)
        _threads[i] = _threads[i + 1];
      _total--;
    }
  }
}

void ThreadController::remove(int id) {
  if (_total > 0 && id < _total && id > -1) {
    for (int i = id; i < _total - 1; i++)
      _threads[i] = _threads[i + 1];
    _total--;
  }
}

void ThreadController::run() {
  for (int i = 0; i < _total; i++)
    _threads[i]->run();
}

Thread * ThreadController::get(int id) {
  if (_total > 0 && id < _total && id > -1) {
    return _threads[id];
  }
  return NULL;
}

Thread * ThreadController::get(const char * name) {
  if (_total > 0) {
    for (int i = 0; i < _total; i++)
      if (strcmp(_threads[i]->getName(), name)==0) return _threads[i];
  }
  return NULL;
}

int ThreadController::size() {
  return _total;
}