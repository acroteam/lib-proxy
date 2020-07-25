/// @brief 'setup_signal_handlers()' test

#include "task_a.h"
#include "task_b.h"

#include "debug.h"              // DPRINTFx()
#include "global.h"
#include "signal_handlers.h"
#include "time.h"

#include <chrono>               // std::chrono::milliseconds()
#include <exception>            // std::exception
#include <memory>               // shared_ptr<>
#include <thread>               // std::this_thread::sleep_for()

int main(/*int argc, char* argv[]*/)
{
  int status;
  IPRINTF("version %u.%u.%u", MAJOR_VERSION, MINOR_VERSION, BUILD_NUMBER);
  {
    char date_time_string[DATE_TIME_STRING_SEC_LEN+1];
    date_time_string_sec(date_time_string, sizeof(date_time_string));
    IPRINTF("Starting (%s UTC)", date_time_string);
  }
  {
    try
    {
      if (!setup_signal_handlers())
      {
        EPRINTF("'%s()' failure", "setup_signal_handlers");
        status = -1;
      }
      else
      {
        TaskA taskA;
        TaskB taskB;

        taskA.attach(&taskB);
        taskB.attach(&taskA);

        IPRINTF("started");

        while (!global::shutdown)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        status = 0;
      }
    }
    catch (const std::exception& e)
    {
      IPRINTF("exception: %s", e.what());
      status = -1;
    }
    catch (...)
    {
      IPRINTF("unexpected exception");
      status = -1;
    }
  }
  IPRINTF("finished");
  return status;
}
