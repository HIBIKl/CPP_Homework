//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// toc.cpp
//
// Code generation for function 'toc'
//

// Include files
#include "toc.h"
#include "timeKeeper.h"
#include "triangularraster_data.h"
#include "coder_posix_time.h"
#include <cstdio>

// Function Definitions
namespace coder {
void toc()
{
  coderTimespec b_timespec;
  double tstart_tv_nsec;
  double tstart_tv_sec;
  tstart_tv_sec = internal::b_time::impl::timeKeeper(tstart_tv_nsec);
  if (!freq_not_empty) {
    freq_not_empty = true;
    coderInitTimeFunctions(&freq);
  }
  coderTimeClockGettimeMonotonic(&b_timespec, freq);
  std::printf("Elapsed time is %f seconds\n",
              (b_timespec.tv_sec - tstart_tv_sec) +
                  (b_timespec.tv_nsec - tstart_tv_nsec) / 1.0E+9);
  std::fflush(stdout);
}

} // namespace coder

// End of code generation (toc.cpp)
