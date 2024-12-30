#include <Arduino.h>

#include <Utilify/StringUtils.h>
#include <Utilify/BasicVector.h>
#include <Utilify/Callback.h>

void setup() { 
    Serial.begin(9600);
    Serial.println(StringUtils::padLeft("Hello", ' ', 10));
    Serial.println(StringUtils::padLeft(String(42), '0', 4));
    Serial.println(StringUtils::padLeft("0x" + String(42), '0', 4));

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
}

void loop() { ; }
