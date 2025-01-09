#pragma once

#include <Utilify/Action/ActionBase.h>
#include <Utilify/Callback.h>

template <typename T>
class Action : public ActionBase<T> {
 public:
  Action(CallbackWithParam<T> callback) : m_callback(callback) {}

  void execute(const T& arg) override { m_callback(arg); }

 private:
  CallbackWithParam<T> m_callback;
};

template <>
class Action<void> : public ActionBase<void> {
 public:
  Action(Callback callback) : m_callback(callback) {}

  void execute() override { m_callback(); }

 private:
  Callback m_callback;
};
