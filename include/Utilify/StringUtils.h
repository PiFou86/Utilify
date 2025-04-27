#pragma once

#include <Arduino.h>

class StringUtils {
public:
  static String padLeft(const String &value, unsigned int length, char padChar = ' ');
  static String padRight(const String &value, unsigned int length, char padChar = ' ');
  static String center(const String &value, unsigned int length, char padChar = ' ');
};
