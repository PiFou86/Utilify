#pragma once

#include <Utilify/Task/TaskBase.h>
#include <Utilify/BasicVector.h>

class TaskAggregate : public TaskBase {
 public:
  TaskAggregate() = default;

  inline void addTask(TaskBase* task) { m_tasks.push_back(task); }

  inline void tick() override {
    for (TaskBase* task : m_tasks) {
      task->tick();
    }
  }

 private:
  vector<TaskBase*> m_tasks;
};
