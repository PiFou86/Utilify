# Utilify

**Utilify** is a versatile library providing essential utilities for embedded systems, simplifying tasks such as string manipulation and device management. It is designed to work seamlessly with **Arduino** and **ESP32** platforms, making it a valuable addition to your embedded development toolkit.

---

## Features

- Lightweight and efficient utility library.
- Simplifies string manipulation with functions like padding and trimming.
- Device management utilities for embedded platforms.
- Compatible with **Arduino** and **ESP32**.
- Easy to integrate into PlatformIO projects.

---

## Getting Started

### Installation

To add **Utilify** to your PlatformIO project, include the library in your `platformio.ini` file:

```ini
[env:esp32dev]
platform = espressif32
framework = arduino
lib_deps =
    https://github.com/PiFou86/Utilify.git
```

### Basic Usage

Include the library in your project and use its utilities :

```cpp
#include <Arduino.h>

#include <Utilify/StringUtils.h>
#include <Utilify/SimpleCollection.h>
#include <Utilify/callback.h>

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
```

---

## Utilities Overview

### String Manipulation

The library provides several functions to simplify string handling:

- **padLeft**: Pads a string with a specific character to the left.
- **padRight**: Pads a string with a specific character to the right.
- **trim**: Removes leading and trailing whitespace from a string.

### Device Utilities

Retrieve device-specific information, such as unique IDs and configuration details. For example:

```cpp
String deviceId = getId();
Serial.println("Device ID: " + deviceId);
```

---

## Dependencies

No additional dependencies are required, making **Utilify** lightweight and easy to use.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Author

**Pierre-François Léon**  
📧 Email: pierrefrancois.leon@gmail.com  
🔗 [GitHub Profile](https://github.com/PiFou86)
