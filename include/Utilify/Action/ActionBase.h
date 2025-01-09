#pragma once

template <typename T>
class ActionBase {
 public:
  virtual ~ActionBase() = default;
  virtual void execute(const T&) = 0;
};

template <>
class ActionBase<void> {
 public:
  virtual ~ActionBase() = default;
  virtual void execute() = 0;
};
