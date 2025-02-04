#include <Utilify/Task/Timer.h>

Timer::Timer(unsigned long interval, ActionBase<void>* action,
             unsigned int repeatLimit, bool autoStart)
    : m_interval(interval),
      m_autoStart(autoStart),
      m_running(false),
      m_callback(nullptr),
      m_action(action),
      m_repeatCount(0),
      m_repeatLimit(repeatLimit) {
  if (m_autoStart) {
    start();
  }
}

Timer::Timer(unsigned long interval, Callback callback,
             unsigned int repeatLimit, bool autoStart)
    : m_interval(interval),
      m_autoStart(autoStart),
      m_running(false),
      m_callback(callback),
      m_action(nullptr),
      m_repeatCount(0),
      m_repeatLimit(repeatLimit) {
  if (m_autoStart) {
    start();
  }
}

void Timer::start() {
  m_nextTime = millis() + m_interval;
  m_running = true;
  m_repeatCount = 0;
}

void Timer::stop() { m_running = false; }

void Timer::tick() {
  if (m_running) {
    unsigned long now = millis();
    if (now >= m_nextTime) {
      while (now >= this->m_nextTime) {
        this->m_nextTime += this->m_interval;
      }

      if (m_action) {
        m_action->execute();
      } else if (m_callback) {
        m_callback();
      }

      m_repeatCount++;
      if (m_repeatLimit > 0 && m_repeatCount >= m_repeatLimit) {
        m_running = false;
      }
    }
  }
}

void Timer::callback(Callback callback) {
  m_callback = callback;
  m_action = nullptr;
}

void Timer::callback(ActionBase<void>* action) {
  m_action = action;
  m_callback = nullptr;
}

void Timer::interval(unsigned long interval) {
  m_interval = interval;
  if (m_running) {
    start();
  }
}

void Timer::repeatLimit(unsigned int repeatLimit) {
  m_repeatLimit = repeatLimit;
}