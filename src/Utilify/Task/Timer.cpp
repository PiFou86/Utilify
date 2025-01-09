#include <Utilify/Task/Timer.h>

Timer::Timer(unsigned long interval, ActionBase<void>* action, bool autoStart)
    : m_interval(interval),
      m_autoStart(autoStart),
      m_running(false),
      m_callback(nullptr),
      m_action(action) {
  if (m_autoStart) {
    start();
  }
}

Timer::Timer(unsigned long interval, Callback callback, bool autoStart)
    : m_interval(interval),
      m_autoStart(autoStart),
      m_running(false),
      m_callback(callback),
      m_action(nullptr) {
  if (m_autoStart) {
    start();
  }
}

void Timer::start() {
  m_nextTime = millis() + m_interval;
  m_running = true;
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
    }
  }
}

void Timer::callback(Callback callback) {
  m_callback = callback;
  m_action = nullptr;
}

void Timer::action(ActionBase<void>* action) {
  m_action = action;
  m_callback = nullptr;
}

void Timer::interval(unsigned long interval) {
  m_interval = interval;
  if (m_running) {
    start();
  }
}
