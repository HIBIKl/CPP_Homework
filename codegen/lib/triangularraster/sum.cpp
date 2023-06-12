//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sum.cpp
//
// Code generation for function 'sum'
//

// Include files
#include "sum.h"
#include "coder_array.h"
#include <cstring>

// Function Definitions
namespace coder {
void sum(const ::coder::array<double, 2U> &x, double y_data[], int y_size[2])
{
  int vlen;
  vlen = x.size(0);
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y_size[0] = 1;
    y_size[1] = static_cast<short>(x.size(1));
    vlen = static_cast<short>(x.size(1));
    if (vlen - 1 >= 0) {
      std::memset(&y_data[0], 0,
                  static_cast<unsigned int>(vlen) * sizeof(double));
    }
  } else {
    int i;
    i = x.size(1);
    y_size[0] = 1;
    y_size[1] = x.size(1);
    for (int xi{0}; xi < i; xi++) {
      int xpageoffset;
      xpageoffset = xi * x.size(0);
      y_data[xi] = x[xpageoffset];
      for (int k{2}; k <= vlen; k++) {
        y_data[xi] += x[(xpageoffset + k) - 1];
      }
    }
  }
}

} // namespace coder

// End of code generation (sum.cpp)
