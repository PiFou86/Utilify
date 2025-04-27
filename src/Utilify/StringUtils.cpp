#include "Utilify/StringUtils.h"

String StringUtils::padLeft(const String &value, unsigned int length, char padChar) {
  String result = value;
  while (result.length() < length) {
    result = padChar + result;
  }
  return result;
}

String StringUtils::padRight(const String &value, unsigned int length, char padChar) {
  String result = value;
  while (result.length() < length) {
    result += padChar;
  }
  return result;
}

String StringUtils::center(const String &value, unsigned int length, char padChar) {
    if (value.length() >= length) {
        return value; // Si la longueur est déjà suffisante
    }

    unsigned int totalPadding = length - value.length(); // Total des caractères de padding nécessaires
    unsigned int leftPadding = totalPadding / 2;        // Moitié pour le côté gauche
    unsigned int rightPadding = totalPadding - leftPadding; // Le reste pour le côté droit

    String result = value;
    while (leftPadding-- > 0) {
        result = padChar + result;
    }
    while (rightPadding-- > 0) {
        result += padChar;
    }

    return result;
}
