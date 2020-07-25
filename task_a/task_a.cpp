#include "task_a.h"

/// @brief Task A

#include "debug.h"
#include "task_b.h"

#include <chrono>               // std::chrono::milliseconds()
#include <thread>               // std::this_thread::sleep_for()

namespace task_a {

TaskA_Status Server::TaskA_Service2(TaskA_Service2_Result* r, long a)
{
  if (!r) { return TaskA_InternalError; }
  if (0 == (a % 13)) { return TaskA_IoError; }
  *r = a + 31;
  return TaskA_OK;
}

void Client::attach(TaskB* taskB)
{
  taskB_ = taskB;
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
    if (taskB_) {
      static long a = 0;
      TaskB_Service2_Result r;
      auto taskB_Status = taskB_->TaskB_Service2(&r, ++a);
      if (TaskB_OK != taskB_Status) {
        WPRINTF("%s() failure %i", "TaskB_Service2", taskB_Status);
      } else {
        DPRINTF("%s() result %li", "TaskB_Service2", r);
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

} // namespace task_a
