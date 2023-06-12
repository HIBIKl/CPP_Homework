//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// timeKeeper.cpp
//
// Code generation for function 'timeKeeper'
//

// Include files
#include "timeKeeper.h"
#include "triangularraster_data.h"
#include "coder_posix_time.h"

// Variable Definitions
static coderTimespec savedTime;

static boolean_T savedTime_not_empty;

// Function Definitions
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec)
{
  if (!savedTime_not_empty) {
    coderTimespec b_timespec;
    if (!freq_not_empty) {
      freq_not_empty = true;
      coderInitTimeFunctions(&freq);
    }
    coderTimeClockGettimeMonotonic(&b_timespec, freq);
    savedTime_not_empty = true;
  }
  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

double timeKeeper(double &outTime_tv_nsec)
{
  double outTime_tv_sec;
  outTime_tv_sec = savedTime.tv_sec;
  outTime_tv_nsec = savedTime.tv_nsec;
  return outTime_tv_sec;
}

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init()
{
  savedTime_not_empty = false;
}

// End of code generation (timeKeeper.cpp)
