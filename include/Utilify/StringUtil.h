#pragma once

#include <Arduino.h>

class StringUtil {
public:
  static String padLeft(const String &value, char padChar, unsigned int length);
  static String padRight(const String &value, char padChar, unsigned int length);
  static String center(const String &value, char padChar, unsigned int length);
};
