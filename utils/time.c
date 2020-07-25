/// @brief 'time' manipulation helper functions

#include "time.h"

#include <stdio.h>
#include <string.h>

void split_time(struct tm* tm, time_sec_t time_sec)
{
  // 'time_t' contains seconds since '1970.01.01 00:00:00'
  time_t time = time_sec;
  if (!gmtime_r(&time, tm))
  {
    memset(tm, 0, sizeof(*tm));
  }
  else
  {
    tm->tm_mon += 1; // gmtime_r() returns 'tm_mon' relative to 'January'
    tm->tm_year += 1900; // gmtime_r() returns 'tm_year' relative to '1900'
  }
}

time_sec_t time_sec()
{
  return time_nsec() / 1000000000ull;
}

time_msec_t time_msec()
{
  return time_nsec() / 1000000ull;
}

time_usec_t time_usec()
{
  return time_nsec() / 1000ull;
}

time_nsec_t time_nsec()
{
  struct timespec ts;
  if (clock_gettime(CLOCK_REALTIME, &ts))
  {
    ts.tv_sec = ts.tv_nsec = 0;
  }
  return ts.tv_sec * 1000000000ull + ts.tv_nsec;
}

void time_sec_to_string(char *s, size_t size, time_sec_t time_sec)
{
  struct tm tm;
  split_time(&tm, time_sec);
  snprintf(s, size, "%04u.%02u.%02u %02u:%02u:%02u", tm.tm_year, tm.tm_mon,
      tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void time_msec_to_string(char *s, size_t size, time_msec_t time_msec)
{
  time_sec_t time_sec = time_msec / 1000ull;
  unsigned msec = time_msec % 1000ull;
  struct tm tm;
  split_time(&tm, time_sec);
  snprintf(s, size, "%04u.%02u.%02u %02u:%02u:%02u.%03u", tm.tm_year,
      tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, msec);
}

void time_usec_to_string(char *s, size_t size, time_usec_t time_usec)
{
  time_sec_t time_sec = time_usec / 1000000ull;
  unsigned usec = time_usec % 1000000ull;
  struct tm tm;
  split_time(&tm, time_sec);
  snprintf(s, size, "%04u.%02u.%02u %02u:%02u:%02u.%06u", tm.tm_year,
      tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, usec);
}

void time_nsec_to_string(char *s, size_t size, time_nsec_t time_nsec)
{
  time_sec_t time_sec = time_nsec / 1000000000ull;
  unsigned nsec = time_nsec % 1000000000ull;
  struct tm tm;
  split_time(&tm, time_sec);
  snprintf(s, size, "%04u.%02u.%02u %02u:%02u:%02u.%09u", tm.tm_year,
      tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, nsec);
}

void date_time_string_sec(char *s, size_t size)
{
  time_sec_to_string(s, size, time_sec());
}

void date_time_string_msec(char *s, size_t size)
{
  time_msec_to_string(s, size, time_msec());
}

void date_time_string_usec(char *s, size_t size)
{
  time_usec_to_string(s, size, time_usec());
}

void date_time_string_nsec(char *s, size_t size)
{
  time_nsec_to_string(s, size, time_nsec());
}
