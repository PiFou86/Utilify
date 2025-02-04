#pragma once

#include <Arduino.h>

#include <Utilify/Action/ActionBase.h>
#include <Utilify/Callback.h>
#include <Utilify/Task/TaskBase.h>

class Timer : public TaskBase {
 public:
  Timer(unsigned long interval, ActionBase<void>* action, unsigned int repeatLimit = 0, bool autoStart = true);
  Timer(unsigned long interval, Callback callback, unsigned int repeatLimit = 0, bool autoStart = true);

  void start();
  void stop();

  void tick() override;

  void callback(Callback callback);
  void callback(ActionBase<void>* action);

  void interval(unsigned long interval);

  void repeatLimit(unsigned int repeatLimit);

 private:
  unsigned long m_interval;
  unsigned long m_nextTime;
  bool m_autoStart;
  bool m_running;
  Callback m_callback;
  ActionBase<void>* m_action;
  unsigned int m_repeatCount;
  unsigned int m_repeatLimit;
};

inline constexpr unsigned long operator"" _mseconds(unsigned long long ms) {
  return ms;
}

inline constexpr unsigned long operator"" _seconds(unsigned long long s) {
  return s * 1000;
}

inline constexpr unsigned long operator"" _minutes(unsigned long long minutes) {
  return minutes * 60 * 1000;
}

inline constexpr unsigned long operator"" _hours(unsigned long long h) {
  return h * 60 * 60 * 1000;
}
