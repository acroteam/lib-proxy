#pragma once

/// @brief services provided by Task A

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  TaskA_OK,
  TaskA_InternalError,
  TaskA_IoError,
} TaskA_Status;

typedef int  TaskA_Service1_Result;
typedef long TaskA_Service2_Result;
typedef struct {
  signed int  si;
  signed long sl;
} TaskA_Service3_Result;
typedef struct {
  unsigned int  ui;
  unsigned long ul;
} TaskA_Service3_Args;

TaskA_Status TaskA_Service1(TaskA_Service1_Result* r, const char* s);
TaskA_Status TaskA_Service2(TaskA_Service2_Result* r, long a);
TaskA_Status TaskA_Service3(TaskA_Service3_Result* r, const TaskA_Service3_Args* a);

#ifdef __cplusplus
}
#endif
