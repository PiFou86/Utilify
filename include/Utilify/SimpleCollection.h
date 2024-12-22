#pragma once

// vector is not supported in Arduino
#ifdef ARDUINO_AVR_UNO
template <typename ElementType>
class SimpleCollection {
 private:
  ElementType *m_elements;
  unsigned int m_size;
  unsigned int m_capacity;

 public:
  SimpleCollection() : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = 1;
    this->m_elements = new ElementType[this->m_capacity];
  }
  SimpleCollection(const SimpleCollection &other)
      : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = other.m_capacity;
    this->m_size = other.m_size;
    this->m_elements = new ElementType[this->m_capacity];
    for (unsigned int i = 0; i < this->m_size; i++) {
      this->m_elements[i] = other.m_elements[i];
    }
  }
  SimpleCollection(SimpleCollection &&other)
      : m_elements(nullptr), m_size(0), m_capacity(0) {
    this->m_capacity = other.m_capacity;
    this->m_size = other.m_size;
    this->m_elements = other.m_elements;
    other.m_elements = nullptr;
  }
  SimpleCollection &operator=(const SimpleCollection &other) {
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
  SimpleCollection &operator=(SimpleCollection &&other) {
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
  ~SimpleCollection() { delete[] this->m_elements; }

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
#ifdef ESP32
    this->m_elements[this->m_size] = std::move(element);
#else
    this->m_elements[this->m_size] = element;
#endif
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

};
#endif