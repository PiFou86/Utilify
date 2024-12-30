#pragma once

#ifdef ARDUINO_AVR_UNO
typedef void (*Callback)();
#else
#include <functional>
typedef std::function<void()> Callback;
#endif
