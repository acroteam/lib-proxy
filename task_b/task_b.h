#pragma once

/// @brief Task B

#include "task_b_services.h"

#include <thread>

class TaskA;

namespace task_b {

class Context
{
};

class Client
{
private:
  TaskA* taskA_ = nullptr;
  volatile bool shutdown_ = false;
  std::thread thread_;
  static void runProxy(void* self);
  void run();

public:
  ~Client();
  Client();
  void attach(TaskA* taskA);
};

class Server
{
public:
  TaskB_Status TaskB_Service1(TaskB_Service1_Result* r, const char* s);
  TaskB_Status TaskB_Service2(TaskB_Service2_Result* r, long a);
  TaskB_Status TaskB_Service3(TaskB_Service3_Result* r, const TaskB_Service3_Args* a);
};

} // namespace task_b

class TaskB
  : public task_b::Context
  , public task_b::Client
  , public task_b::Server
{
public:
  inline void attach(TaskA* taskA)
  {
    task_b::Client::attach(taskA);
  }
  inline TaskB_Status TaskB_Service2(TaskB_Service2_Result* r, long a)
  {
    return task_b::Server::TaskB_Service2(r, a);
  }
};
