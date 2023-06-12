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
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "triangularraster_data.h"
#include "triangularraster_mexutil.h"
#include "emlrt.h"
#include <cstdio>

// Variable Definitions
static emlrtRSInfo eb_emlrtRSI{
    31,                                                     // lineNo
    "toc",                                                  // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\timefun\\toc.m" // pathName
};

static emlrtRSInfo fb_emlrtRSI{
    36,                                                     // lineNo
    "toc",                                                  // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\timefun\\toc.m" // pathName
};

static emlrtRSInfo gb_emlrtRSI{
    43,                                                     // lineNo
    "toc",                                                  // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\timefun\\toc.m" // pathName
};

static emlrtRSInfo hb_emlrtRSI{
    38,                                                       // lineNo
    "fprintf",                                                // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m" // pathName
};

static emlrtMCInfo h_emlrtMCI{
    66,                                                       // lineNo
    18,                                                       // colNo
    "fprintf",                                                // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m" // pName
};

static emlrtRSInfo mb_emlrtRSI{
    66,                                                       // lineNo
    "fprintf",                                                // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\iofun\\fprintf.m" // pathName
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T emlrt_marshallIn(const emlrtStack &sp,
                               const mxArray *a__output_of_feval_,
                               const char_T *identifier);

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

static real_T emlrt_marshallIn(const emlrtStack &sp,
                               const mxArray *a__output_of_feval_,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(a__output_of_feval_), &thisId);
  emlrtDestroyArray(&a__output_of_feval_);
  return y;
}

static real_T emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

namespace coder {
void toc(const emlrtStack &sp)
{
  static const int32_T iv[2]{1, 7};
  static const int32_T iv1[2]{1, 28};
  static const char_T b_u[28]{'E', 'l', 'a', 'p', 's', 'e', 'd',  ' ', 't', 'i',
                              'm', 'e', ' ', 'i', 's', ' ', '%',  'f', ' ', 's',
                              'e', 'c', 'o', 'n', 'd', 's', '\\', 'n'};
  static const char_T u[7]{'f', 'p', 'r', 'i', 'n', 't', 'f'};
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  emlrtTimespec tnow;
  const mxArray *b_y;
  const mxArray *m;
  const mxArray *y;
  real_T tstart_tv_nsec;
  real_T tstart_tv_sec;
  int32_T status;
  st.prev = &sp;
  st.tls = sp.tls;
  st.site = &eb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  tstart_tv_sec = internal::b_time::impl::timeKeeper(st, tstart_tv_nsec);
  st.site = &fb_emlrtRSI;
  b_st.site = &i_emlrtRSI;
  c_st.site = &j_emlrtRSI;
  status = emlrtClockGettimeMonotonic(&tnow);
  d_st.site = &k_emlrtRSI;
  if (status != 0) {
    emlrtErrorWithMessageIdR2018a(
        &d_st, &l_emlrtRTEI, "Coder:toolbox:CoderTimeCallFailed",
        "Coder:toolbox:CoderTimeCallFailed", 5, 4, 26, &cv[0], 12, status);
  }
  st.site = &gb_emlrtRSI;
  b_st.site = &hb_emlrtRSI;
  y = nullptr;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a(&b_st, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = nullptr;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a(&b_st, 28, m, &b_u[0]);
  emlrtAssign(&b_y, m);
  c_st.site = &mb_emlrtRSI;
  emlrt_marshallIn(
      c_st,
      feval(c_st, y, emlrt_marshallOut(1.0), b_y,
            emlrt_marshallOut((tnow.tv_sec - tstart_tv_sec) +
                              (tnow.tv_nsec - tstart_tv_nsec) / 1.0E+9),
            h_emlrtMCI),
      "<output of feval>");
}

} // namespace coder

// End of code generation (toc.cpp)
