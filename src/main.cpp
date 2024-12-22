#include <Arduino.h>

#include "Utilify/StringUtils.h"

void setup() { 
    Serial.begin(9600);
    Serial.println(StringUtils::padLeft("Hello", ' ', 10));
    Serial.println(StringUtils::padLeft(String(42), '0', 4));
    Serial.println(StringUtils::padLeft("0x" + String(42), '0', 4));
}

void loop() { ; }