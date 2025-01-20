/*
  Thread.h - Library for in-object threading, using the
  Threading functions provided by the Arduino core (or wiring extensions)
  Created by Luiz H. Cassettari, March 28, 2015.
  Released into the public domain.
*/
#ifndef Thread_h
#define Thread_h

#include <Arduino.h>

class Thread {
  friend class ThreadController;

  protected:
    const char * _name;
    int _id;
    bool _enabled;
    bool _running;
    void (*_callback)();
    void (*_onRun)();
    void (*_onYield)();
    void (*_onDisable)();
    void (*_onEnable)();
    void (*_onDestroy)();
    void (*_onTerminate)();
    void (*_onCheck)();

    // static int __nextId; // not implemented due to a possible bug on core

  public:
    Thread();

    void setInterval(long interval);
    long getInterval();

    void setIterations(int iterations);
    int getIterations();

    void setRuns(int runs);
    int getRuns();

    virtual void setup();
    virtual void run();
    virtual void loop();

    void start();
    void start(long interval);

    void onRun( void (*callback)() );
    void onYield( void (*callback)() );
    void onDisable( void (*callback)() );
    void onEnable( void (*callback)() );
    void onDestroy( void (*callback)() );
    void onTerminate( void (*callback)() );
    void onCheck( void (*callback)() );

    void detach( void (*callback)() );

    void yield();
    void disable();
    void enable();
    bool isEnabled();
    bool isRunning();

    void setName(const char * name);
    const char * getName();
    
    int getId();
    
    virtual ~Thread();

  private:
    long _interval;
    int _iterations;
    int _runs;
    long _previous;
    bool _ran;
};

#endif