//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// warning.cpp
//
// Code generation for function 'warning'
//

// Include files
#include "warning.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "triangularraster_mexutil.h"

// Variable Definitions
static emlrtMCInfo f_emlrtMCI{
    14,        // lineNo
    25,        // colNo
    "warning", // fName
    "D:\\matlab\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" // pName
};

static emlrtMCInfo g_emlrtMCI{
    14,        // lineNo
    9,         // colNo
    "warning", // fName
    "D:\\matlab\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" // pName
};

static emlrtRSInfo lb_emlrtRSI{
    14,        // lineNo
    "warning", // fcnName
    "D:\\matlab\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" // pathName
};

// Function Declarations
static void feval(const emlrtStack &sp, const mxArray *m, const mxArray *m1,
                  emlrtMCInfo &location);

// Function Definitions
static void feval(const emlrtStack &sp, const mxArray *m, const mxArray *m1,
                  emlrtMCInfo &location)
{
  const mxArray *pArrays[2];
  pArrays[0] = m;
  pArrays[1] = m1;
  emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 0, nullptr, 2, &pArrays[0], "feval",
                        true, &location);
}

namespace coder {
namespace internal {
void warning(const emlrtStack &sp, const char_T varargin_2[200])
{
  static const int32_T iv[2]{1, 7};
  static const int32_T iv1[2]{1, 7};
  static const int32_T iv2[2]{1, 41};
  static const int32_T iv3[2]{1, 200};
  static const char_T msgID[41]{
      'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'm', 'a', 'g', 'e', 's', 'c',
      'i', ':', 'j', 'p', 'g', ':', 'u', 'n', 'h', 'a', 'n', 'd', 'l', 'e',
      'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'E', 'r', 'r', 'o', 'r'};
  static const char_T b_u[7]{'m', 'e', 's', 's', 'a', 'g', 'e'};
  static const char_T u[7]{'w', 'a', 'r', 'n', 'i', 'n', 'g'};
  emlrtStack st;
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *m;
  const mxArray *y;
  st.prev = &sp;
  st.tls = sp.tls;
  y = nullptr;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = nullptr;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 7, m, &b_u[0]);
  emlrtAssign(&b_y, m);
  c_y = nullptr;
  m = emlrtCreateCharArray(2, &iv2[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 41, m, &msgID[0]);
  emlrtAssign(&c_y, m);
  d_y = nullptr;
  m = emlrtCreateCharArray(2, &iv3[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 200, m, &varargin_2[0]);
  emlrtAssign(&d_y, m);
  st.site = &lb_emlrtRSI;
  feval(st, y, feval(st, b_y, c_y, emlrt_marshallOut(8.0), d_y, f_emlrtMCI),
        g_emlrtMCI);
}

} // namespace internal
} // namespace coder

// End of code generation (warning.cpp)
