#include <Arduino.h>

#include "Utilify/StringUtil.h"

void setup() { 
    Serial.begin(9600);
    Serial.println(StringUtil::padLeft("Hello", ' ', 10));
    Serial.println(StringUtil::padLeft(String(42), '0', 4));
    Serial.println(StringUtil::padLeft("0x" + String(42), '0', 4));
}

void loop() { ; }