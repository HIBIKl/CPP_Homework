//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sum.h
//
// Code generation for function 'sum'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
namespace coder {
void sum(const emlrtStack &sp, const ::coder::array<real_T, 2U> &x,
         real_T y_data[], int32_T y_size[2]);

real_T sum(const emlrtStack &sp, const real_T x_data[],
           const int32_T x_size[2]);

} // namespace coder

// End of code generation (sum.h)
