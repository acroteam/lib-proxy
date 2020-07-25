#pragma once

/// @brief Task A

#include "task_a_services.h"

#include <thread>

class TaskB;

namespace task_a {

class Context
{
};

class Client
{
private:
  TaskB* taskB_ = nullptr;
  volatile bool shutdown_ = false;
  std::thread thread_;
  static void runProxy(void* self);
  void run();

public:
  ~Client();
  Client();
  void attach(TaskB* taskB);
};

class Server
{
public:
  TaskA_Status TaskA_Service1(TaskA_Service1_Result* r, const char* s);
  TaskA_Status TaskA_Service2(TaskA_Service2_Result* r, long a);
  TaskA_Status TaskA_Service3(TaskA_Service3_Result* r, const TaskA_Service3_Args* a);
};

} // namespace task_a

class TaskA
  : public task_a::Context
  , public task_a::Client
  , public task_a::Server
{
public:
  inline void attach(TaskB* taskB)
  {
    task_a::Client::attach(taskB);
  }
  inline TaskA_Status TaskA_Service2(TaskA_Service2_Result* r, long a)
  {
    return task_a::Server::TaskA_Service2(r, a);
  }
};
