#include <Arduino.h>
#include <Utilify/Action/Action.h>
#include <Utilify/Action/ActionBase.h>
#include <Utilify/BasicVector.h>
#include <Utilify/Callback.h>
#include <Utilify/StringUtils.h>
#include <Utilify/Task/TaskAggregate.h>
#include <Utilify/Task/Timer.h>

class ToggleLEDAction : public ActionBase<void> {
 public:
  ToggleLEDAction(int pin) : m_pin(pin), m_state(false) {
    pinMode(m_pin, OUTPUT);
  }

  void execute() override {
    m_state = !m_state;
    digitalWrite(m_pin, m_state ? HIGH : LOW);
  }

 private:
  int m_pin;
  bool m_state;
};

Timer timer(10_seconds, []() {
  Serial.print("Time : ");
  Serial.print(millis() / 1000.0f);
  Serial.println(" - Hello from timer");
});
Timer timer2(500_mseconds, new ToggleLEDAction(LED_BUILTIN), 0, false);
Timer *timer3 = new Timer(5_seconds, []() {
  Serial.print("Time : ");
  Serial.print(millis() / 1000.0f);
  Serial.println(" - Starting LED blink");
  timer2.start();
}, 1);
TaskAggregate taskAggregate;
void setup() {
#ifdef ARDUINO_AVR_UNO
  Serial.begin(9600);
#elif defined(ESP32) || defined(ARDUINO_UNOR4_MINIMA) || \
    defined(ARDUINO_UNOWIFIR4)
  Serial.begin(115200);
#else
#error "Unsupported board"
#endif

  Serial.println(StringUtils::padLeft("Hello", 10));
  Serial.println(StringUtils::padLeft(String(42), 4, '0'));
  Serial.println(String("0x") + StringUtils::padLeft(String(42), 4, '0'));
  Serial.println(String(F("->")) + StringUtils::center("Hello", 10) +
                 String(F("<-")));

  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  for (size_t i = 0; i < v.size(); i++) {
    Serial.println(v[i]);
  }
  for (int i : v) {
    Serial.println(i);
  }

  Callback cb = []() { Serial.println("Hello from callback"); };
  cb();

  CallbackWithParam<int> cbp = [](const int &i) { Serial.println(i); };
  cbp(42);

  CallbackWithParam<String> cbps = [](const String &s) { Serial.println(s); };
  cbps("Hello from callback with param");

  Action<void> action(cb);
  action.execute();

  Action<int> actioni(cbp);
  actioni.execute(42);

  taskAggregate.addTask(&timer);
  taskAggregate.addTask(&timer2);
  taskAggregate.addTask(timer3);

  timer3->start();
}

void loop() { taskAggregate.tick(); }
