#pragma once

/// @brief services provided by Task B

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  TaskB_OK,
  TaskB_InternalError,
  TaskB_IoError,
} TaskB_Status;

typedef int  TaskB_Service1_Result;
typedef long TaskB_Service2_Result;
typedef struct {
  signed int  si;
  signed long sl;
} TaskB_Service3_Result;
typedef struct {
  unsigned int  ui;
  unsigned long ul;
} TaskB_Service3_Args;

TaskB_Status TaskB_Service1(TaskB_Service1_Result* r, const char* s);
TaskB_Status TaskB_Service2(TaskB_Service2_Result* r, long a);
TaskB_Status TaskB_Service3(TaskB_Service3_Result* r, const TaskB_Service3_Args* a);

#ifdef __cplusplus
}
#endif
