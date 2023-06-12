//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster_mexutil.h
//
// Code generation for function 'triangularraster_mexutil'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
const mxArray *emlrt_marshallOut(const real_T u);

const mxArray *feval(const emlrtStack &sp, const mxArray *m1, const mxArray *m2,
                     const mxArray *m3, const mxArray *m4,
                     emlrtMCInfo &location);

// End of code generation (triangularraster_mexutil.h)
