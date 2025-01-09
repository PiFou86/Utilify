#pragma once

class TaskBase {
 public:
  virtual ~TaskBase() = default;
  virtual void tick() = 0;
};
