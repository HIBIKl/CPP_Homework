//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster_internal_types.h
//
// Code generation for function 'triangularraster'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "triangularraster_types.h"
#include "emlrt.h"

// Type Definitions
struct rtDesignRangeCheckInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

struct rtRunTimeErrorInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

// End of code generation (triangularraster_internal_types.h)
