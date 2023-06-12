//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// timeKeeper.h
//
// Code generation for function 'timeKeeper'
//

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

double timeKeeper(double &outTime_tv_nsec);

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init();

#endif
// End of code generation (timeKeeper.h)
