//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster_terminate.cpp
//
// Code generation for function 'triangularraster_terminate'
//

// Include files
#include "triangularraster_terminate.h"
#include "_coder_triangularraster_mex.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"

// Function Definitions
void triangularraster_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  // Free instance data
  covrtFreeInstanceData(&emlrtCoverageInstance);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void triangularraster_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (triangularraster_terminate.cpp)
