//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_triangularraster_api.h
//
// Code generation for function 'triangularraster'
//

#ifndef _CODER_TRIANGULARRASTER_API_H
#define _CODER_TRIANGULARRASTER_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
real_T triangularraster(coder::array<char_T, 2U> *f);

void triangularraster_api(const mxArray *prhs, const mxArray **plhs);

void triangularraster_atexit();

void triangularraster_initialize();

void triangularraster_terminate();

void triangularraster_xil_shutdown();

void triangularraster_xil_terminate();

#endif
// End of code generation (_coder_triangularraster_api.h)
