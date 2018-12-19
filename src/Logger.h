#include <stdint.h>
#include "Arduino.h"
#include <QList.h>

//define __POMODORO_DEBUG

#ifndef HAKKUINO_LOGGER_H
#define HAKKUINO_LOGGER_H

class Logger {
private:
  boolean _isDebug;
  boolean _isTrace;
  QList<String>* _filters;
  static Logger* instance;
public:
  static Logger* getLogger();
  Logger();
  void log(String msg);
  #ifdef __POMODORO_DEBUG
  void debug(String methodName, String msg);
  #endif
  #ifdef __POMODORO_TRACE
  void trace(String methodName, String msg);
  #endif
  boolean isDebug();
  boolean isTrace();
  void setDebug(boolean value);
  void setTrace(boolean value);
  QList<String>* getFilters(); 
};

//extern Logger Log;

#ifdef __POMODORO_DEBUG
#define DEBUG(text) Logger::getLogger()->debug(__PRETTY_FUNCTION__, text)
#else
#define DEBUG(text) //Logger::getLogger()->debug(text)
#endif
#ifdef __POMODORO_TRACE
#define TRACE(text) Logger::getLogger()->trace(__PRETTY_FUNCTION__, text)
#else
#define TRACE(text) //Logger::getLogger()->trace(text)
#endif

#endif