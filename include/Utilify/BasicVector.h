#pragma once

// vector is not supported in Arduino
#ifdef ARDUINO_AVR_UNO
template <typename ElementType>
class BasicVector {
 private:
  ElementType *m_elements;
  unsigned int m_size;
  unsigned int m_capacity;

 public:
  BasicVector() : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = 1;
    this->m_elements = new ElementType[this->m_capacity];
  }
  BasicVector(const BasicVector &other)
      : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = other.m_capacity;
    this->m_size = other.m_size;
    this->m_elements = new ElementType[this->m_capacity];
    for (unsigned int i = 0; i < this->m_size; i++) {
      this->m_elements[i] = other.m_elements[i];
    }
  }
  BasicVector(BasicVector &&other)
      : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = other.m_capacity;
    this->m_size = other.m_size;
    this->m_elements = other.m_elements;
    other.m_elements = nullptr;
  }
  BasicVector &operator=(const BasicVector &other) {
    if (this != &other) {
      this->m_capacity = other.m_capacity;
      this->m_size = other.m_size;
      if (this->m_elements != nullptr) {
        delete[] this->m_elements;
      }
      this->m_elements = new ElementType[this->m_capacity];
      for (unsigned int i = 0; i < this->m_size; i++) {
        this->m_elements[i] = other.m_elements[i];
      }
    }
    return *this;
  }
  BasicVector &operator=(BasicVector &&other) {
    if (this != &other) {
      this->m_capacity = other.m_capacity;
      this->m_size = other.m_size;
      if (this->m_elements != nullptr) {
        delete[] this->m_elements;
      }
      this->m_elements = other.m_elements;
      other.m_elements = nullptr;
    }
    return *this;
  }
  ~BasicVector() { delete[] this->m_elements; }

  void push_back(const ElementType &element) {
    if (this->m_size == this->m_capacity) {
      this->resize(this->m_capacity * 2);
    }
    this->m_elements[this->m_size] = element;
    this->m_size++;
  }
  void push_back(ElementType &&element) {
    if (this->m_size == this->m_capacity) {
      this->resize(this->m_capacity * 2);
    }

    this->m_elements[this->m_size] = element;
    this->m_size++;
  }

  ElementType &operator[](unsigned int index) {
    return this->m_elements[index];
  }

  void resize(unsigned int newCapacity) {
    ElementType *newElements = new ElementType[newCapacity];
    for (unsigned int i = 0; i < this->m_size; i++) {
      newElements[i] = this->m_elements[i];
    }
    delete[] this->m_elements;
    this->m_elements = newElements;
    this->m_capacity = newCapacity;
  }
  unsigned int size() const { return this->m_size; }
  unsigned int capacity() const { return this->m_capacity; }
  void clear() {
    this->m_size = 0;
  }
  bool empty() const {
    return this->m_size == 0;
  }
  ElementType *begin() { return this->m_elements; }
  ElementType *end() { return this->m_elements + this->m_size; }
};

// replace std::vector with SimpleCollection
template<typename T>
using vector = BasicVector<T>;

#elif defined(ESP32) || defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOWIFIR4)
#include <vector>
template<typename T>
using vector = std::vector<T>;
#else
#error "Unsupported board"
#endif