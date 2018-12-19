#include "Logger.h"
#include <QList.h>

Logger* Logger::instance;

Logger* Logger::getLogger()
{
  if (Logger::instance == NULL)
  {
    Logger::instance = new Logger();
  }
  return Logger::instance;
}

Logger::Logger()
{
  #ifdef __POMODORO_TRACE
  this->_isTrace = true;
  #else
  this->_isTrace = false;
  #endif
  #ifdef __POMODORO_DEBUG
  this->_isDebug = true;
  #else
  this->_isDebug = false;
  #endif
  this->_filters=new QList<String>();
}

void Logger::log(String msg)
{
  Serial.println("[INFO] " + msg);
}

#ifdef __POMODORO_TRACE
void Logger::trace(String methodName, String msg)
{
  if (this->isTrace())
  {
    Serial.print("[TRACE]");
    Serial.print("[");
    Serial.print(methodName);
    Serial.print("] ");
    Serial.println(msg);
  }
}
#endif

#ifdef __POMODORO_DEBUG
void Logger::debug(String methodName, String msg)
{
  if (this->isDebug())
  {
    boolean display=false;
    if (this->_filters->size() > 0){
      
      for(int i = 0; i < this->getFilters()->size(); i++)
      {
        if (methodName.indexOf(this->getFilters()->get(i)) > 0 ){
          display=true;
          break;
        }
      }
      
    }
    else {
      display=true;
    }
    if (display)
    {
      Serial.print("[DEBUG]");
      Serial.print("[");
      Serial.print(methodName);
      Serial.print("] ");
      Serial.println(msg);
    }
  }
}
#endif

boolean Logger::isDebug()
{
  return this->_isDebug;
}
boolean Logger::isTrace()
{
  return this->_isTrace;
}
void Logger::setDebug(boolean value)
{
  this->_isDebug = value;
}
void Logger::setTrace(boolean value)
{
  this->_isTrace = value;
}

QList<String>* Logger::getFilters()
{
  return this->_filters;
}