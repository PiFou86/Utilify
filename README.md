# Utilify

**Utilify** is a versatile library providing essential utilities for embedded systems, simplifying tasks such as string manipulation and device management. It is designed to work seamlessly with **Arduino** and **ESP32** platforms, making it a valuable addition to your embedded development toolkit.

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/sirdrako/library/Utilify.svg)](https://registry.platformio.org/libraries/sirdrako/Utilify)

## Features

- Lightweight and efficient utility library.
- Simplifies string manipulation with functions like padding and trimming.
- Device management utilities for embedded platforms.
- Compatible with **Arduino** and **ESP32**.
- Easy to integrate into PlatformIO projects.

## Getting Started

### Installation

To add **Utilify** to your PlatformIO project, include the library in your `platformio.ini` file:

```ini
[env:esp32dev]
platform = espressif32
framework = arduino
lib_deps =
    sirdrako/Utilify
```

### Basic Usage

Include the library in your project and use its utilities :

```cpp
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
Timer timer2(500_mseconds, new ToggleLEDAction(LED_BUILTIN), false);
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

  Serial.println(StringUtils::padLeft("Hello", ' ', 10));
  Serial.println(StringUtils::padLeft(String(42), '0', 4));
  Serial.println(String("0x") + StringUtils::padLeft(String(42), '0', 4));
  Serial.println(String(F("->")) + StringUtils::center("Hello", ' ', 10) +
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
```

This example outputs the following:

```
     Hello
0042
0x0042
->  Hello   <-
1
2
3
1
2
3
Hello from callback
42
Hello from callback with param
Hello from callback
42
Time : 5.05 - Starting LED blink
Time : 10.00 - Hello from timer
Time : 20.00 - Hello from timer
Time : 30.00 - Hello from timer
...
```

## Utilities Overview

### String Manipulation

The library provides several functions to simplify string handling:

- **padLeft**: Pads a string with a specific character to the left.
- **padRight**: Pads a string with a specific character to the right.
- **center**: Centers a string within a specified width.

For example:

```cpp
String paddedString = StringUtils::padLeft("Hello", ' ', 10);
Serial.println(paddedString);
```

### Device Utilities

Retrieve device-specific information, such as unique IDs and configuration details. For example:

```cpp
String deviceId = getId();
Serial.println("Device ID: " + deviceId);
```

### Task Management

Manage tasks and timers with ease using the **Task** and **Timer** classes. For example:

```cpp
Timer timer(10_seconds, []() {
  Serial.print("Time : ");
  Serial.print(millis() / 1000.0f);
  Serial.println(" - Hello from timer");
});
timer.start();
```

## Dependencies

No additional dependencies are required, making **Utilify** lightweight and easy to use.

## Other Libraries

- https://github.com/PiFou86/UtilifyEEPROM :
  A library for managing EEPROM storage on Arduino and ESP32 platforms.
- https://github.com/PiFou86/UtilifyLogger :
  A logging library for Arduino and ESP32 platforms, providing various logging levels and formats.
- https://github.com/PiFou86/UtilifyDigitalInput :
  A library for managing digital inputs on Arduino and ESP32 platforms, providing debouncing and state change detection.
- https://github.com/PiFou86/UtilifyAnalogInput :
  A library for managing analog inputs on Arduino and ESP32 platforms, providing debouncing and state change detection.
- https://github.com/PiFou86/UtilifyCommandInterpreter :
  A command interpreter library for Arduino and ESP32 platforms, allowing easy parsing and execution of commands from serial input.
  
## Author

**Pierre-François Léon**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Profile-blue?logo=linkedin&style=for-the-badge)](https://www.linkedin.com/in/pierrefrancoisleon/)
[![GitHub profile](https://img.shields.io/badge/GitHub-Profile-blue?logo=github&style=for-the-badge)](https://github.com/PiFou86)
