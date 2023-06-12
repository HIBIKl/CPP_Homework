//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// tril.cpp
//
// Code generation for function 'tril'
//

// Include files
#include "tril.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
void tril(::coder::array<real_T, 2U> &x)
{
  int32_T n;
  n = x.size(1);
  if ((x.size(0) != 0) && (x.size(1) != 0) && (x.size(1) > 1)) {
    int32_T iend;
    iend = 1;
    for (int32_T j{2}; j <= n; j++) {
      for (int32_T i{0}; i < iend; i++) {
        x[i + x.size(0) * (j - 1)] = 0.0;
      }
      if (iend < x.size(0)) {
        iend++;
      }
    }
  }
}

} // namespace coder

// End of code generation (tril.cpp)
