//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// timeKeeper.cpp
//
// Code generation for function 'timeKeeper'
//

// Include files
#include "timeKeeper.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "emlrt.h"

// Variable Definitions
static emlrtTimespec savedTime;

static boolean_T savedTime_not_empty;

static emlrtRSInfo l_emlrtRSI{
    13,           // lineNo
    "timeKeeper", // fcnName
    "D:\\matlab\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+internal\\+"
    "time\\+impl\\timeKeeper.m" // pathName
};

static emlrtRTEInfo w_emlrtRTEI{
    11,           // lineNo
    9,            // colNo
    "timeKeeper", // fName
    "D:\\matlab\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+internal\\+"
    "time\\+impl\\timeKeeper.m" // pName
};

// Function Definitions
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
void timeKeeper(const emlrtStack &sp, const emlrtTimespec newTime)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack st;
  st.prev = &sp;
  st.tls = sp.tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  if (!savedTime_not_empty) {
    int32_T status;
    st.site = &l_emlrtRSI;
    b_st.site = &i_emlrtRSI;
    c_st.site = &j_emlrtRSI;
    status = emlrtClockGettimeMonotonic(&savedTime);
    d_st.site = &k_emlrtRSI;
    if (status != 0) {
      emlrtErrorWithMessageIdR2018a(
          &d_st, &l_emlrtRTEI, "Coder:toolbox:CoderTimeCallFailed",
          "Coder:toolbox:CoderTimeCallFailed", 5, 4, 26, &cv[0], 12, status);
    }
    savedTime_not_empty = true;
  }
  savedTime = newTime;
}

real_T timeKeeper(const emlrtStack &sp, real_T &outTime_tv_nsec)
{
  real_T outTime_tv_sec;
  if (!savedTime_not_empty) {
    emlrtErrorWithMessageIdR2018a(&sp, &w_emlrtRTEI,
                                  "MATLAB:toc:callTicFirstNoInputs",
                                  "MATLAB:toc:callTicFirstNoInputs", 0);
  }
  outTime_tv_sec = savedTime.tv_sec;
  outTime_tv_nsec = savedTime.tv_nsec;
  return outTime_tv_sec;
}

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init()
{
  savedTime_not_empty = false;
}

// End of code generation (timeKeeper.cpp)
