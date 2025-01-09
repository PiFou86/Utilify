#pragma once

#ifdef ARDUINO_AVR_UNO
using Callback = void (*)();
template <typename T>
using CallbackWithParam = void (*)(const T&);
#elif defined(ESP32) || defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOWIFIR4)
#include <functional>
using Callback = std::function<void()>;
template <typename T>
using CallbackWithParam = std::function<void(const T&)>;
#else
#error "Unsupported board"
#endif
