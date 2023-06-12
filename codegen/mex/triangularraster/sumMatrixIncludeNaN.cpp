//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// sumMatrixIncludeNaN.cpp
//
// Code generation for function 'sumMatrixIncludeNaN'
//

// Include files
#include "sumMatrixIncludeNaN.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo r_emlrtRSI{
    20,                               // lineNo
    "eml_int_forloop_overflow_check", // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_overflow_"
    "check.m" // pathName
};

static emlrtRSInfo ab_emlrtRSI{
    178,          // lineNo
    "sumColumnB", // fcnName
    "D:"
    "\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMatrixIncludeNaN"
    ".m" // pathName
};

static emlrtRSInfo bb_emlrtRSI{
    210,         // lineNo
    "sumColumn", // fcnName
    "D:"
    "\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMatrixIncludeNaN"
    ".m" // pathName
};

// Function Definitions
namespace coder {
real_T sumColumnB(const emlrtStack &sp, const ::coder::array<real_T, 2U> &x,
                  int32_T col, int32_T vlen)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  real_T y;
  int32_T i;
  int32_T i0;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &ab_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  i0 = (col - 1) * x.size(0);
  y = x[i0];
  b_st.site = &bb_emlrtRSI;
  if (vlen - 1 > 2147483646) {
    c_st.site = &r_emlrtRSI;
    check_forloop_overflow_error(c_st);
  }
  i = static_cast<uint16_T>(vlen - 1);
  for (int32_T k{0}; k < i; k++) {
    y += x[(i0 + k) + 1];
  }
  return y;
}

real_T sumColumnB(const emlrtStack &sp, const real_T x_data[], int32_T vlen)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  real_T y;
  int32_T i;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &ab_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  y = x_data[0];
  b_st.site = &bb_emlrtRSI;
  if (vlen - 1 > 2147483646) {
    c_st.site = &r_emlrtRSI;
    check_forloop_overflow_error(c_st);
  }
  i = static_cast<uint16_T>(vlen - 1);
  for (int32_T k{0}; k < i; k++) {
    y += x_data[k + 1];
  }
  return y;
}

} // namespace coder

// End of code generation (sumMatrixIncludeNaN.cpp)
