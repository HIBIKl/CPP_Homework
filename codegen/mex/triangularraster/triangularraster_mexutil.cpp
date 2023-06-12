//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster_mexutil.cpp
//
// Code generation for function 'triangularraster_mexutil'
//

// Include files
#include "triangularraster_mexutil.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"

// Function Definitions
const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

const mxArray *feval(const emlrtStack &sp, const mxArray *m1, const mxArray *m2,
                     const mxArray *m3, const mxArray *m4,
                     emlrtMCInfo &location)
{
  const mxArray *pArrays[4];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  return emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 1, &m, 4, &pArrays[0],
                               "feval", true, &location);
}

// End of code generation (triangularraster_mexutil.cpp)
