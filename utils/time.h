#pragma once

/// @brief 'time' manipulation helper functions

#include <stddef.h>
#include <time.h>

// .........1.........2.........
// 12345678901234567890123456789
// 2018.05.15 16:05:01
// 2018.05.15 16:05:01.123
// 2018.05.15 16:05:01.123456
// 2018.05.15 16:05:01.123456789
#define DATE_TIME_STRING_SEC_LEN 19
#define DATE_TIME_STRING_MSEC_LEN 23
#define DATE_TIME_STRING_USEC_LEN 26
#define DATE_TIME_STRING_NSEC_LEN 29

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long long time_sec_t;
typedef unsigned long long time_msec_t;
typedef unsigned long long time_usec_t;
typedef unsigned long long time_nsec_t;

time_sec_t time_sec();
time_msec_t time_msec();
time_usec_t time_usec();
time_nsec_t time_nsec();

void time_sec_to_string(char *s, size_t size, time_sec_t time_sec);
void time_msec_to_string(char *s, size_t size, time_msec_t time_msec);
void time_usec_to_string(char *s, size_t size, time_usec_t time_usec);
void time_nsec_to_string(char *s, size_t size, time_nsec_t time_nsec);

void date_time_string_sec(char *s, size_t size);
void date_time_string_msec(char *s, size_t size);
void date_time_string_usec(char *s, size_t size);
void date_time_string_nsec(char *s, size_t size);

void split_time(struct tm* tm, time_sec_t time_sec);

#ifdef __cplusplus
}
#endif
