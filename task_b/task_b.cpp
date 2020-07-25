#include "task_b.h"

/// @brief Task B

#include "debug.h"
#include "task_a.h"

#include <chrono>               // std::chrono::milliseconds()
#include <thread>               // std::this_thread::sleep_for()

namespace task_b {

TaskB_Status Server::TaskB_Service2(TaskB_Service2_Result* r, long a)
{
  if (!r) { return TaskB_InternalError; }
  if (0 == (a % 31)) { return TaskB_IoError; }
  *r = a + 13;
  return TaskB_OK;
}

void Client::attach(TaskA* taskA)
{
  taskA_ = taskA;
}

void Client::runProxy(void* self)
{
  static_cast<Client*>(self)->run();
}

void Client::run()
{
  DPRINTF("thread %s",  "started");
  while (!shutdown_) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (taskA_) {
      static long a = 0;
      TaskA_Service2_Result r;
      auto taskA_Status = taskA_->TaskA_Service2(&r, ++a);
      if (TaskA_OK != taskA_Status) {
        WPRINTF("%s() failure %i", "TaskA_Service2", taskA_Status);
      } else {
        DPRINTF("%s() result %li", "TaskA_Service2", r);
      }
    }
  }
  DPRINTF("thread %s",  "finished");
}

Client::Client()
  : thread_(std::thread(runProxy, this))
{
  DPRINTF("");
}

Client::~Client()
{
  DPRINTF("starting shutdown");
  shutdown_ = true;
  thread_.join();
  DPRINTF("shutdown finished");
}

} // namespace task_b
