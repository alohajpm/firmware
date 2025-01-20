/*
  ThreadController.h - Implementation of in-object threading, using the
  Threading functions provided by the Arduino core (or wiring extensions)
  Created by Luiz H. Cassettari, March 28, 2015.
  Released into the public domain.
*/
#ifndef ThreadController_h
#define ThreadController_h

#include "Thread.h"

#define MAX_THREADS 8

class ThreadController {

  protected:
    static Thread * _threads[MAX_THREADS];
    static int _total;

  public:

    ThreadController();
    virtual ~ThreadController();

    static bool add(Thread *thread);
    static void remove(Thread *thread);
    static void remove(int id);
    static void run();
    static Thread * get(int id);
    static Thread * get(const char * name);
    static int size();

};

#endif