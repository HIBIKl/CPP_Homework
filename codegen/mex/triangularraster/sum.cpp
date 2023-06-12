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
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "triangularraster_data.h"
#include "coder_array.h"
#include <cstring>

// Variable Definitions
static emlrtRSInfo s_emlrtRSI{
    20,                                                     // lineNo
    "sum",                                                  // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\sum.m" // pathName
};

static emlrtRSInfo t_emlrtRSI{
    99,        // lineNo
    "sumprod", // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m" // pathName
};

static emlrtRSInfo u_emlrtRSI{
    74,                      // lineNo
    "combineVectorElements", // fcnName
    "D:"
    "\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combineVectorElemen"
    "ts.m" // pathName
};

static emlrtRSInfo v_emlrtRSI{
    107,                // lineNo
    "blockedSummation", // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\blockedSummation."
    "m" // pathName
};

static emlrtRSInfo w_emlrtRSI{
    22,                    // lineNo
    "sumMatrixIncludeNaN", // fcnName
    "D:"
    "\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMatrixIncludeNaN"
    ".m" // pathName
};

static emlrtRSInfo x_emlrtRSI{
    42,                 // lineNo
    "sumMatrixColumns", // fcnName
    "D:"
    "\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMatrixIncludeNaN"
    ".m" // pathName
};

static emlrtRSInfo cb_emlrtRSI{
    99,                 // lineNo
    "blockedSummation", // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\blockedSummation."
    "m" // pathName
};

static emlrtRTEInfo u_emlrtRTEI{
    46,        // lineNo
    23,        // colNo
    "sumprod", // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m" // pName
};

static emlrtRTEInfo v_emlrtRTEI{
    76,        // lineNo
    9,         // colNo
    "sumprod", // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m" // pName
};

// Function Definitions
namespace coder {
void sum(const emlrtStack &sp, const ::coder::array<real_T, 2U> &x,
         real_T y_data[], int32_T y_size[2])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &s_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  if ((x.size(0) == 1) && (x.size(1) != 1)) {
    emlrtErrorWithMessageIdR2018a(&st, &u_emlrtRTEI,
                                  "Coder:toolbox:autoDimIncompatibility",
                                  "Coder:toolbox:autoDimIncompatibility", 0);
  }
  if ((x.size(0) == 0) && (x.size(1) == 0)) {
    emlrtErrorWithMessageIdR2018a(&st, &v_emlrtRTEI,
                                  "Coder:toolbox:UnsupportedSpecialEmpty",
                                  "Coder:toolbox:UnsupportedSpecialEmpty", 0);
  }
  b_st.site = &t_emlrtRSI;
  c_st.site = &u_emlrtRSI;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    int32_T loop_ub;
    y_size[0] = 1;
    y_size[1] = static_cast<int16_T>(x.size(1));
    loop_ub = static_cast<int16_T>(x.size(1));
    if (loop_ub - 1 >= 0) {
      std::memset(&y_data[0], 0,
                  static_cast<uint32_T>(loop_ub) * sizeof(real_T));
    }
  } else {
    int32_T loop_ub;
    d_st.site = &v_emlrtRSI;
    e_st.site = &w_emlrtRSI;
    y_size[0] = 1;
    y_size[1] = x.size(1);
    loop_ub = x.size(1);
    for (int32_T col{0}; col < loop_ub; col++) {
      f_st.site = &x_emlrtRSI;
      y_data[col] = sumColumnB(f_st, x, col + 1, x.size(0));
    }
  }
}

real_T sum(const emlrtStack &sp, const real_T x_data[], const int32_T x_size[2])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  real_T y;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &s_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  b_st.site = &t_emlrtRSI;
  c_st.site = &u_emlrtRSI;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    d_st.site = &cb_emlrtRSI;
    e_st.site = &w_emlrtRSI;
    f_st.site = &x_emlrtRSI;
    y = sumColumnB(f_st, x_data, x_size[1]);
  }
  return y;
}

} // namespace coder

// End of code generation (sum.cpp)
