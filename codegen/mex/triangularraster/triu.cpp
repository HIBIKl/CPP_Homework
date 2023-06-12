//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triu.cpp
//
// Code generation for function 'triu'
//

// Include files
#include "triu.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
void triu(::coder::array<real_T, 2U> &x)
{
  int32_T m;
  m = x.size(0);
  if ((x.size(0) != 0) && (x.size(1) != 0) && (x.size(0) > 1)) {
    int32_T istart;
    int32_T jend;
    istart = 2;
    if (x.size(0) - 2 < x.size(1) - 1) {
      jend = x.size(0) - 1;
    } else {
      jend = x.size(1);
    }
    for (int32_T j{0}; j < jend; j++) {
      for (int32_T i{istart}; i <= m; i++) {
        x[(i + x.size(0) * j) - 1] = 0.0;
      }
      istart++;
    }
  }
}

} // namespace coder

// End of code generation (triu.cpp)
