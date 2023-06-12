//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster.cpp
//
// Code generation for function 'triangularraster'
//

// Include files
#include "triangularraster.h"
#include "imread.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "tic.h"
#include "toc.h"
#include "triangularraster_data.h"
#include "triangularraster_mexutil.h"
#include "tril.h"
#include "triu.h"
#include "coder_array.h"
#include <cstring>

// Type Definitions
struct cell_wrap_0 {
  real_T f1[5];
};

struct cell_wrap_1 {
  real_T f1[4];
};

// Variable Definitions
static emlrtRTEInfo emlrtRTEI{
    207,                // lineNo
    2,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRSInfo emlrtRSI{
    23,                 // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo b_emlrtRSI{
    26,                 // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo d_emlrtRSI{
    78,                 // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo f_emlrtRSI{
    105,                // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo g_emlrtRSI{
    285,                // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtMCInfo emlrtMCI{
    279,                // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtMCInfo b_emlrtMCI{
    279,                // lineNo
    24,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtMCInfo c_emlrtMCI{
    280,                // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtMCInfo d_emlrtMCI{
    281,                // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtMCInfo e_emlrtMCI{
    281,                // lineNo
    24,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtBCInfo emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    265,                // lineNo
    16,                 // colNo
    "Q",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo b_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    264,                // lineNo
    17,                 // colNo
    "Q",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo c_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    263,                // lineNo
    9,                  // colNo
    "Q",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo d_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    262,                // lineNo
    9,                  // colNo
    "Q",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo e_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    230,                // lineNo
    18,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo f_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    229,                // lineNo
    18,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo g_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    228,                // lineNo
    18,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo h_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    227,                // lineNo
    18,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo i_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    226,                // lineNo
    16,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo j_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    70,                 // lineNo
    21,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo k_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    70,                 // lineNo
    30,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo l_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    70,                 // lineNo
    44,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo m_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    70,                 // lineNo
    53,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtRTEInfo b_emlrtRTEI{
    102,                // lineNo
    23,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtECInfo emlrtECI{
    1,                  // nDims
    137,                // lineNo
    14,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtECInfo b_emlrtECI{
    2,                  // nDims
    137,                // lineNo
    14,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtECInfo c_emlrtECI{
    3,                  // nDims
    137,                // lineNo
    14,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo c_emlrtRTEI{
    191,                // lineNo
    19,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo d_emlrtRTEI{
    224,                // lineNo
    7,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtDCInfo emlrtDCI{
    232,                // lineNo
    12,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    1 // checkKind
};

static emlrtRTEInfo e_emlrtRTEI{
    235,                // lineNo
    19,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo f_emlrtRTEI{
    236,                // lineNo
    23,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo g_emlrtRTEI{
    246,                // lineNo
    19,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo h_emlrtRTEI{
    247,                // lineNo
    23,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo i_emlrtRTEI{
    261,                // lineNo
    7,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo j_emlrtRTEI{
    267,                // lineNo
    11,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo k_emlrtRTEI{
    268,                // lineNo
    15,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtBCInfo n_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    238,                // lineNo
    25,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtDCInfo b_emlrtDCI{
    238,                // lineNo
    27,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    1 // checkKind
};

static emlrtBCInfo o_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    238,                // lineNo
    27,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtBCInfo p_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    249,                // lineNo
    25,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtBCInfo q_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    249,                // lineNo
    27,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtBCInfo r_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    270,                // lineNo
    17,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtBCInfo s_emlrtBCI{
    1,                  // iFirst
    256,                // iLast
    270,                // lineNo
    19,                 // colNo
    "res",              // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    3 // checkKind
};

static emlrtBCInfo t_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    158,                // lineNo
    14,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo u_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    158,                // lineNo
    16,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo v_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    166,                // lineNo
    28,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo w_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    166,                // lineNo
    30,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo x_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    171,                // lineNo
    24,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo y_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    171,                // lineNo
    26,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo ab_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    193,                // lineNo
    23,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo bb_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    193,                // lineNo
    25,                 // colNo
    "f",                // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo cb_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    115,                // lineNo
    25,                 // colNo
    "Q_tri",            // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtDCInfo c_emlrtDCI{
    115,                // lineNo
    25,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    1 // checkKind
};

static emlrtBCInfo db_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    92,                 // lineNo
    38,                 // colNo
    "mark",             // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo eb_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    92,                 // lineNo
    51,                 // colNo
    "mark",             // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo fb_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    118,                // lineNo
    38,                 // colNo
    "mark",             // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtBCInfo gb_emlrtBCI{
    -1,                 // iFirst
    -1,                 // iLast
    118,                // lineNo
    51,                 // colNo
    "mark",             // aName
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m", // pName
    0 // checkKind
};

static emlrtRTEInfo y_emlrtRTEI{
    54,                 // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo ab_emlrtRTEI{
    55,                 // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo bb_emlrtRTEI{
    57,                 // lineNo
    1,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo cb_emlrtRTEI{
    70,                 // lineNo
    17,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo db_emlrtRTEI{
    77,                 // lineNo
    21,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo eb_emlrtRTEI{
    22,                 // lineNo
    30,                 // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRTEInfo fb_emlrtRTEI{
    279,                // lineNo
    8,                  // colNo
    "triangularraster", // fName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pName
};

static emlrtRSInfo ib_emlrtRSI{
    279,                // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo jb_emlrtRSI{
    281,                // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

static emlrtRSInfo kb_emlrtRSI{
    280,                // lineNo
    "triangularraster", // fcnName
    "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m" // pathName
};

// Function Declarations
static const mxArray *b_emlrt_marshallOut(const emlrtStack &sp,
                                          const char_T u[18]);

static const mxArray *emlrt_marshallOut(const coder::array<uint8_T, 3U> &u);

static const mxArray *emlrt_marshallOut(const uint8_T u[65536]);

static const mxArray *emlrt_marshallOut(const emlrtStack &sp,
                                        const char_T u[15]);

static void figure(const emlrtStack &sp, emlrtMCInfo &location);

static void imshow(const emlrtStack &sp, const mxArray *m,
                   emlrtMCInfo &location);

static void title(const emlrtStack &sp, const mxArray *m,
                  emlrtMCInfo &location);

// Function Definitions
static const mxArray *b_emlrt_marshallOut(const emlrtStack &sp,
                                          const char_T u[18])
{
  static const int32_T iv[2]{1, 18};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 18, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const coder::array<uint8_T, 3U> &u)
{
  const mxArray *m;
  const mxArray *y;
  int32_T iv[3];
  int32_T i;
  uint8_T *pData;
  y = nullptr;
  iv[0] = u.size(0);
  iv[1] = u.size(1);
  iv[2] = u.size(2);
  m = emlrtCreateNumericArray(3, &iv[0], mxUINT8_CLASS, mxREAL);
  pData = static_cast<uint8_T *>(emlrtMxGetData(m));
  i = 0;
  for (int32_T b_i{0}; b_i < u.size(2); b_i++) {
    for (int32_T c_i{0}; c_i < u.size(1); c_i++) {
      for (int32_T d_i{0}; d_i < u.size(0); d_i++) {
        pData[i] = u[(d_i + u.size(0) * c_i) + u.size(0) * u.size(1) * b_i];
        i++;
      }
    }
  }
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const uint8_T u[65536])
{
  static const int32_T iv[2]{256, 256};
  const mxArray *m;
  const mxArray *y;
  int32_T i;
  uint8_T *pData;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxUINT8_CLASS, mxREAL);
  pData = static_cast<uint8_T *>(emlrtMxGetData(m));
  i = 0;
  for (int32_T b_i{0}; b_i < 256; b_i++) {
    for (int32_T c_i{0}; c_i < 256; c_i++) {
      pData[i + c_i] = u[c_i + (b_i << 8)];
    }
    i += 256;
  }
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const emlrtStack &sp,
                                        const char_T u[15])
{
  static const int32_T iv[2]{1, 15};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtConstCTX)&sp, 15, m, &u[0]);
  emlrtAssign(&y, m);
  return y;
}

static void figure(const emlrtStack &sp, emlrtMCInfo &location)
{
  emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 0, nullptr, 0, nullptr, "figure",
                        true, &location);
}

static void imshow(const emlrtStack &sp, const mxArray *m,
                   emlrtMCInfo &location)
{
  const mxArray *pArray;
  pArray = m;
  emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 0, nullptr, 1, &pArray, "imshow",
                        true, &location);
}

static void title(const emlrtStack &sp, const mxArray *m, emlrtMCInfo &location)
{
  const mxArray *pArray;
  pArray = m;
  emlrtCallMATLABR2012b((emlrtConstCTX)&sp, 0, nullptr, 1, &pArray, "title",
                        true, &location);
}

real_T triangularraster(const emlrtStack *sp, const coder::array<char_T, 2U> &f)
{
  static const char_T cv1[18]{'r', 'e', 's', 't', 'r', 'u', 'c', 't', 'e',
                              'd', ' ', 'p', 'i', 'c', 't', 'u', 'r', 'e'};
  static const char_T b_cv[15]{'o', 'r', 'i', 'g', 'n', 'a', 'l', ' ',
                               'p', 'i', 'c', 't', 'u', 'r', 'e'};
  coder::array<cell_wrap_0, 2U> Q_tri;
  coder::array<cell_wrap_1, 2U> Q;
  coder::array<real_T, 2U> c_f;
  coder::array<real_T, 2U> upper_triangular;
  coder::array<uint8_T, 3U> b_f;
  coder::array<uint8_T, 3U> org;
  emlrtStack st;
  real_T tmp_data[510];
  real_T Length0;
  real_T MaxArea;
  real_T MaxLength;
  real_T blackNodeNum;
  real_T d;
  real_T last;
  real_T num_of_total_mix;
  real_T num_of_total_triangular;
  int32_T MaxWidth;
  int32_T b_loop_ub;
  int32_T f_idx_0;
  int32_T f_tmp;
  int32_T i;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T j;
  int32_T k;
  int32_T loop_ub;
  int32_T loop_ub_tmp;
  int8_T res[65536];
  uint8_T b_res[65536];
  st.prev = sp;
  st.tls = sp->tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)sp);
  covrtLogFcn(&emlrtCoverageInstance, 0, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 0);
  //  Use: compute "blackNodeNum"
  //  Only for binary bmp
  //  [Q]=triangularraster(3,'fivestar8_binary.bmp');
  //  [Q]=triangularraster(4,'fivestar16_binary.bmp');
  //  [Q]=triangularraster(5,'fivestar32_binary.bmp');
  //  [Q]=triangularraster(6,'fivestar64_binary.bmp');
  //  [Q]=triangularraster(7,'fivestar128_binary.bmp');
  //  [Q]=triangularraster(8,'fivestar256_binary.bmp');
  //  [Q]=triangularraster(9,'fivestar512_binary.bmp');
  //  [Q]=triangularraster(3,'sixstar8_binary.bmp');
  //  [Q]=triangularraster(4,'sixstar16_binary.bmp');
  //  [Q]=triangularraster(5,'sixstar32_binary.bmp');
  //  [Q]=triangularraster(6,'sixstar64_binary.bmp');
  //  [Q]=triangularraster(7,'sixstar128_binary.bmp');
  //  [Q]=triangularraster(8,'sixstar256_binary.bmp');
  //  [Q]=triangularraster(9,'sixstar512_binary.bmp');
  st.site = &emlrtRSI;
  coder::tic(st);
  // picture=f;
  st.site = &b_emlrtRSI;
  coder::imread(st, f, b_f);
  //  f=zeros(8,8)
  //
  //  f =[
  //      1     0     0     0     0     0     0     1
  //      1     0     0     0     0     0     0     0
  //      1     1     1     0     0     0     0     0
  //      1     1     1     1     0     0     0     0
  //      0     1     1     0     0     0     0     0
  //      0     0     1     0     1     0     0     0
  //      0     0     0     0     0     0     1     0
  //  ]
  //  % f=[
  //       1     1     1     1     1     1     1     1
  //       1     1     1     0     0     1     1     1
  //       1     0     0     0     0     0     0     1
  //       1     1     0     0     0     0     1     1
  //       1     1     0     1     1     0     1     1
  //       1     1     1     1     1     1     1     1
  //   ]
  //  f=ones(8,8)
  org.set_size(&y_emlrtRTEI, sp, b_f.size(0), b_f.size(1), b_f.size(2));
  loop_ub_tmp = b_f.size(0) * b_f.size(1) * b_f.size(2);
  for (i = 0; i < loop_ub_tmp; i++) {
    org[i] = b_f[i];
  }
  Q_tri.set_size(&ab_emlrtRTEI, sp, 1, 0);
  //  n=3
  Q.set_size(&bb_emlrtRTEI, sp, 1, 0);
  //  the size of the picture is size * size
  num_of_total_triangular = 0.0;
  for (int32_T var_sp_x{0}; var_sp_x < 255; var_sp_x++) {
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 0, 1);
    for (int32_T var_sp_y{0}; var_sp_y < 255; var_sp_y++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 1, 1);
      //          var_sp_x=6;
      //          var_sp_y=4;
      for (int32_T step{0}; step < 255; step++) {
        boolean_T guard1;
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 2, 1);
        //      step=2;
        i = (var_sp_x - step) + 256;
        guard1 = false;
        if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 0, i <= 256)) {
          i1 = (var_sp_y - step) + 256;
          if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 1, i1 <= 256)) {
            int32_T tmp_size[2];
            covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 0, true);
            covrtLogIf(&emlrtCoverageInstance, 0, 0, 0, true);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 1);
            if (var_sp_x + 1 > i) {
              i2 = 0;
              i3 = 0;
            } else {
              if (var_sp_x + 1 > b_f.size(0)) {
                emlrtDynamicBoundsCheckR2012b(var_sp_x + 1, 1, b_f.size(0),
                                              &j_emlrtBCI, (emlrtConstCTX)sp);
              }
              i2 = var_sp_x;
              if (i > b_f.size(0)) {
                emlrtDynamicBoundsCheckR2012b(i, 1, b_f.size(0), &k_emlrtBCI,
                                              (emlrtConstCTX)sp);
              }
              i3 = i;
            }
            if (var_sp_y + 1 > i1) {
              MaxWidth = 0;
              k = 0;
            } else {
              k = b_f.size(1) * b_f.size(2);
              if (var_sp_y + 1 > k) {
                emlrtDynamicBoundsCheckR2012b(var_sp_y + 1, 1, k, &l_emlrtBCI,
                                              (emlrtConstCTX)sp);
              }
              MaxWidth = var_sp_y;
              if (i1 > k) {
                emlrtDynamicBoundsCheckR2012b(i1, 1, k, &m_emlrtBCI,
                                              (emlrtConstCTX)sp);
              }
              k = i1;
            }
            f_idx_0 = b_f.size(0);
            loop_ub = i3 - i2;
            b_loop_ub = k - MaxWidth;
            c_f.set_size(&cb_emlrtRTEI, sp, loop_ub, b_loop_ub);
            for (i3 = 0; i3 < b_loop_ub; i3++) {
              for (k = 0; k < loop_ub; k++) {
                c_f[k + c_f.size(0) * i3] =
                    b_f[(i2 + k) + f_idx_0 * (MaxWidth + i3)];
              }
            }
            // ***!mcc***************************************************************
            covrtLogFor(&emlrtCoverageInstance, 0, 0, 3, 1);
            covrtLogIf(&emlrtCoverageInstance, 0, 0, 1, true);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 2);
            //  k=6
            upper_triangular.set_size(&db_emlrtRTEI, sp, c_f.size(0),
                                      c_f.size(1));
            loop_ub = c_f.size(0) * c_f.size(1);
            for (i2 = 0; i2 < loop_ub; i2++) {
              upper_triangular[i2] = c_f[i2];
            }
            coder::triu(upper_triangular);
            st.site = &d_emlrtRSI;
            coder::sum(st, upper_triangular, tmp_data, tmp_size);
            st.site = &d_emlrtRSI;
            if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 2,
                           coder::sum(st, tmp_data, tmp_size) == 0.0)) {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 3);
              num_of_total_triangular++;
              // 存储斜边
              // x3=1;y3=size_temp;
              //                          Q_tri{num_of_total_triangular}={0,x1_abs,y1_abs,x2_abs,y2_abs};
              loop_ub = Q_tri.size(1) + 1;
              Q_tri.set_size(&eb_emlrtRTEI, sp, 1, Q_tri.size(1) + 1);
              Q_tri[loop_ub - 1].f1[0] = 0.0;
              Q_tri[Q_tri.size(1) - 1].f1[1] =
                  static_cast<real_T>(var_sp_x) + 1.0;
              Q_tri[Q_tri.size(1) - 1].f1[2] =
                  static_cast<real_T>(var_sp_y) + 1.0;
              Q_tri[Q_tri.size(1) - 1].f1[3] = i;
              Q_tri[Q_tri.size(1) - 1].f1[4] = i1;
              i2 = 255 - step;
              for (loop_ub = 0; loop_ub <= i2; loop_ub++) {
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 4, 1);
                i3 = 255 - (step + loop_ub);
                for (j = 0; j <= i3; j++) {
                  covrtLogFor(&emlrtCoverageInstance, 0, 0, 5, 1);
                  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 4);
                  f_idx_0 = b_f.size(0);
                  f_tmp = b_f.size(1) * b_f.size(2);
                  k = (loop_ub + var_sp_x) + 1;
                  if (k > b_f.size(0)) {
                    emlrtDynamicBoundsCheckR2012b(
                        k, 1, b_f.size(0), &db_emlrtBCI, (emlrtConstCTX)sp);
                  }
                  MaxWidth = ((loop_ub + j) + var_sp_y) + 1;
                  if (MaxWidth > f_tmp) {
                    emlrtDynamicBoundsCheckR2012b(
                        MaxWidth, 1, f_tmp, &eb_emlrtBCI, (emlrtConstCTX)sp);
                  }
                  b_f[(k + f_idx_0 * (MaxWidth - 1)) - 1] = 8U;
                  if (*emlrtBreakCheckR2012bFlagVar != 0) {
                    emlrtBreakCheckR2012b((emlrtConstCTX)sp);
                  }
                }
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 5, 0);
                if (*emlrtBreakCheckR2012bFlagVar != 0) {
                  emlrtBreakCheckR2012b((emlrtConstCTX)sp);
                }
              }
              covrtLogFor(&emlrtCoverageInstance, 0, 0, 4, 0);
            }
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 5);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 6);
            // ******************************************************************
            // ******************************************************************
            emlrtForLoopVectorCheckR2021a(
                0.0, -1.0, -((-static_cast<real_T>(step) + 255.0) + 1.0) + 2.0,
                mxDOUBLE_CLASS, 255 - step, &b_emlrtRTEI, (emlrtConstCTX)sp);
            covrtLogFor(&emlrtCoverageInstance, 0, 0, 6, 1);
            covrtLogIf(&emlrtCoverageInstance, 0, 0, 3, true);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 7);
            //       k=-6
            coder::tril(c_f);
            st.site = &f_emlrtRSI;
            coder::sum(st, c_f, tmp_data, tmp_size);
            st.site = &f_emlrtRSI;
            if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 4,
                           coder::sum(st, tmp_data, tmp_size) == 0.0)) {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 8);
              num_of_total_triangular++;
              if (num_of_total_triangular !=
                  static_cast<int32_T>(num_of_total_triangular)) {
                emlrtIntegerCheckR2012b(num_of_total_triangular, &c_emlrtDCI,
                                        (emlrtConstCTX)sp);
              }
              if ((static_cast<int32_T>(num_of_total_triangular) - 1 < 0) ||
                  (static_cast<int32_T>(num_of_total_triangular) - 1 >
                   Q_tri.size(1) - 1)) {
                emlrtDynamicBoundsCheckR2012b(
                    static_cast<int32_T>(num_of_total_triangular) - 1, 0,
                    Q_tri.size(1) - 1, &cb_emlrtBCI, (emlrtConstCTX)sp);
              }
              Q_tri[static_cast<int32_T>(num_of_total_triangular) - 1].f1[0] =
                  1.0;
              if (num_of_total_triangular !=
                  static_cast<int32_T>(num_of_total_triangular)) {
                emlrtIntegerCheckR2012b(num_of_total_triangular, &c_emlrtDCI,
                                        (emlrtConstCTX)sp);
              }
              if ((static_cast<int32_T>(num_of_total_triangular) - 1 < 0) ||
                  (static_cast<int32_T>(num_of_total_triangular) - 1 >
                   Q_tri.size(1) - 1)) {
                emlrtDynamicBoundsCheckR2012b(
                    static_cast<int32_T>(num_of_total_triangular) - 1, 0,
                    Q_tri.size(1) - 1, &cb_emlrtBCI, (emlrtConstCTX)sp);
              }
              Q_tri[static_cast<int32_T>(num_of_total_triangular) - 1].f1[1] =
                  static_cast<real_T>(var_sp_x) + 1.0;
              if (num_of_total_triangular !=
                  static_cast<int32_T>(num_of_total_triangular)) {
                emlrtIntegerCheckR2012b(num_of_total_triangular, &c_emlrtDCI,
                                        (emlrtConstCTX)sp);
              }
              if ((static_cast<int32_T>(num_of_total_triangular) - 1 < 0) ||
                  (static_cast<int32_T>(num_of_total_triangular) - 1 >
                   Q_tri.size(1) - 1)) {
                emlrtDynamicBoundsCheckR2012b(
                    static_cast<int32_T>(num_of_total_triangular) - 1, 0,
                    Q_tri.size(1) - 1, &cb_emlrtBCI, (emlrtConstCTX)sp);
              }
              Q_tri[static_cast<int32_T>(num_of_total_triangular) - 1].f1[2] =
                  static_cast<real_T>(var_sp_y) + 1.0;
              if (num_of_total_triangular !=
                  static_cast<int32_T>(num_of_total_triangular)) {
                emlrtIntegerCheckR2012b(num_of_total_triangular, &c_emlrtDCI,
                                        (emlrtConstCTX)sp);
              }
              if ((static_cast<int32_T>(num_of_total_triangular) - 1 < 0) ||
                  (static_cast<int32_T>(num_of_total_triangular) - 1 >
                   Q_tri.size(1) - 1)) {
                emlrtDynamicBoundsCheckR2012b(
                    static_cast<int32_T>(num_of_total_triangular) - 1, 0,
                    Q_tri.size(1) - 1, &cb_emlrtBCI, (emlrtConstCTX)sp);
              }
              Q_tri[static_cast<int32_T>(num_of_total_triangular) - 1].f1[3] =
                  i;
              if (num_of_total_triangular !=
                  static_cast<int32_T>(num_of_total_triangular)) {
                emlrtIntegerCheckR2012b(num_of_total_triangular, &c_emlrtDCI,
                                        (emlrtConstCTX)sp);
              }
              if ((static_cast<int32_T>(num_of_total_triangular) - 1 < 0) ||
                  (static_cast<int32_T>(num_of_total_triangular) - 1 >
                   Q_tri.size(1) - 1)) {
                emlrtDynamicBoundsCheckR2012b(
                    static_cast<int32_T>(num_of_total_triangular) - 1, 0,
                    Q_tri.size(1) - 1, &cb_emlrtBCI, (emlrtConstCTX)sp);
              }
              Q_tri[static_cast<int32_T>(num_of_total_triangular) - 1].f1[4] =
                  i1;
              i = 255 - step;
              for (loop_ub = 0; loop_ub <= i; loop_ub++) {
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 7, 1);
                i1 = (loop_ub + var_sp_x) + 1;
                for (j = 0; j <= loop_ub; j++) {
                  covrtLogFor(&emlrtCoverageInstance, 0, 0, 8, 1);
                  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 9);
                  f_idx_0 = b_f.size(0);
                  f_tmp = b_f.size(1) * b_f.size(2);
                  if (i1 > b_f.size(0)) {
                    emlrtDynamicBoundsCheckR2012b(
                        i1, 1, b_f.size(0), &fb_emlrtBCI, (emlrtConstCTX)sp);
                  }
                  i2 = (j + var_sp_y) + 1;
                  if (i2 > f_tmp) {
                    emlrtDynamicBoundsCheckR2012b(i2, 1, f_tmp, &gb_emlrtBCI,
                                                  (emlrtConstCTX)sp);
                  }
                  b_f[(i1 + f_idx_0 * (i2 - 1)) - 1] = 9U;
                  if (*emlrtBreakCheckR2012bFlagVar != 0) {
                    emlrtBreakCheckR2012b((emlrtConstCTX)sp);
                  }
                }
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 8, 0);
                if (*emlrtBreakCheckR2012bFlagVar != 0) {
                  emlrtBreakCheckR2012b((emlrtConstCTX)sp);
                }
              }
              covrtLogFor(&emlrtCoverageInstance, 0, 0, 7, 0);
            }
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 10);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 11);
            // ******************************************************************
            //  imshow(uint8(f*255))
            //  celldisp(Q)
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 0, false);
          covrtLogIf(&emlrtCoverageInstance, 0, 0, 0, false);
        }
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b((emlrtConstCTX)sp);
        }
      }
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 2, 0);
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtConstCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 1, 0);
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 0, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 12);
  if ((org.size(0) != b_f.size(0)) &&
      ((org.size(0) != 1) && (b_f.size(0) != 1))) {
    emlrtDimSizeImpxCheckR2021b(org.size(0), b_f.size(0), &emlrtECI,
                                (emlrtConstCTX)sp);
  }
  if ((org.size(1) != b_f.size(1)) &&
      ((org.size(1) != 1) && (b_f.size(1) != 1))) {
    emlrtDimSizeImpxCheckR2021b(org.size(1), b_f.size(1), &b_emlrtECI,
                                (emlrtConstCTX)sp);
  }
  if ((org.size(2) != b_f.size(2)) &&
      ((org.size(2) != 1) && (b_f.size(2) != 1))) {
    emlrtDimSizeImpxCheckR2021b(org.size(2), b_f.size(2), &c_emlrtECI,
                                (emlrtConstCTX)sp);
  }
  //  *************************************************************************
  //     part two
  //  *************************************************************************
  blackNodeNum = 0.0;
  MaxLength = 0.0;
  MaxWidth = 0;
  for (int32_T var_sp_x{0}; var_sp_x < 256; var_sp_x++) {
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 9, 1);
    for (int32_T var_sp_y{0}; var_sp_y < 256; var_sp_y++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 10, 1);
      covrtLogBasicBlock(&emlrtCoverageInstance, 0, 13);
      f_idx_0 = b_f.size(0);
      f_tmp = b_f.size(1) * b_f.size(2);
      if (var_sp_x + 1 > b_f.size(0)) {
        emlrtDynamicBoundsCheckR2012b(var_sp_x + 1, 1, b_f.size(0), &t_emlrtBCI,
                                      (emlrtConstCTX)sp);
      }
      if (var_sp_y + 1 > f_tmp) {
        emlrtDynamicBoundsCheckR2012b(var_sp_y + 1, 1, f_tmp, &u_emlrtBCI,
                                      (emlrtConstCTX)sp);
      }
      if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 5,
                     b_f[var_sp_x + f_idx_0 * var_sp_y] == 0)) {
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 14);
        //  Length=1;Width=1;MaxArea=1;
        MaxArea = 0.0;
        last = 0.0;
        j = 0;
        int32_T exitg1;
        do {
          exitg1 = 0;
          if (j <= 255 - var_sp_y) {
            loop_ub = (var_sp_y + j) + 1;
            covrtLogFor(&emlrtCoverageInstance, 0, 0, 11, 1);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 15);
            Length0 = 0.0;
            k = 0;
            int32_T exitg2;
            do {
              exitg2 = 0;
              if (k <= 255 - var_sp_x) {
                b_loop_ub = (var_sp_x + k) + 1;
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 12, 1);
                if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 2,
                                 loop_ub != var_sp_y + 1) &&
                    covrtLogCond(&emlrtCoverageInstance, 0, 0, 3,
                                 (static_cast<real_T>(b_loop_ub - var_sp_x) -
                                  1.0) + 1.0 >
                                     last)) {
                  covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 1, true);
                  covrtLogIf(&emlrtCoverageInstance, 0, 0, 6, true);
                  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 16);
                  exitg2 = 1;
                } else {
                  covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 1, false);
                  covrtLogIf(&emlrtCoverageInstance, 0, 0, 6, false);
                  f_idx_0 = b_f.size(0);
                  if (b_loop_ub > b_f.size(0)) {
                    emlrtDynamicBoundsCheckR2012b(b_loop_ub, 1, b_f.size(0),
                                                  &v_emlrtBCI,
                                                  (emlrtConstCTX)sp);
                  }
                  if (loop_ub > f_tmp) {
                    emlrtDynamicBoundsCheckR2012b(
                        loop_ub, 1, f_tmp, &w_emlrtBCI, (emlrtConstCTX)sp);
                  }
                  if (covrtLogIf(
                          &emlrtCoverageInstance, 0, 0, 7,
                          covrtLogMcdc(
                              &emlrtCoverageInstance, 0, 0, 2,
                              !covrtLogCond(
                                  &emlrtCoverageInstance, 0, 0, 4,
                                  b_f[(b_loop_ub + f_idx_0 * (loop_ub - 1)) -
                                      1] == 0)))) {
                    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 17);
                    exitg2 = 1;
                  } else {
                    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 18);
                    Length0++;
                    k++;
                    if (*emlrtBreakCheckR2012bFlagVar != 0) {
                      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
                    }
                  }
                }
              } else {
                covrtLogFor(&emlrtCoverageInstance, 0, 0, 12, 0);
                exitg2 = 1;
              }
            } while (exitg2 == 0);
            // end for k=x:2^n
            if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 8,
                           loop_ub == var_sp_y + 1)) {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 19);
              last = Length0;
            }
            if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 9, Length0 < last)) {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 20);
              last = Length0;
            }
            f_idx_0 = b_f.size(0);
            if (var_sp_x + 1 > b_f.size(0)) {
              emlrtDynamicBoundsCheckR2012b(var_sp_x + 1, 1, b_f.size(0),
                                            &x_emlrtBCI, (emlrtConstCTX)sp);
            }
            if (loop_ub > f_tmp) {
              emlrtDynamicBoundsCheckR2012b(loop_ub, 1, f_tmp, &y_emlrtBCI,
                                            (emlrtConstCTX)sp);
            }
            if (covrtLogIf(
                    &emlrtCoverageInstance, 0, 0, 10,
                    covrtLogMcdc(
                        &emlrtCoverageInstance, 0, 0, 3,
                        !covrtLogCond(&emlrtCoverageInstance, 0, 0, 5,
                                      b_f[var_sp_x + f_idx_0 * (loop_ub - 1)] ==
                                          0)))) {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 21);
              exitg1 = 1;
            } else {
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 22);
              loop_ub -= var_sp_y;
              Length0 = last * ((static_cast<real_T>(loop_ub) - 1.0) + 1.0);
              if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 11,
                             Length0 > MaxArea)) {
                covrtLogBasicBlock(&emlrtCoverageInstance, 0, 23);
                //   if Area>MaxArea
                MaxArea = Length0;
                MaxLength = last;
                MaxWidth = loop_ub;
              }
              j++;
              if (*emlrtBreakCheckR2012bFlagVar != 0) {
                emlrtBreakCheckR2012b((emlrtConstCTX)sp);
              }
            }
          } else {
            covrtLogFor(&emlrtCoverageInstance, 0, 0, 11, 0);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
        //  for j=y:2^n
        if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 12,
                       MaxLength * static_cast<real_T>(MaxWidth) == 1.0)) {
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 24);
        } else {
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 25);
        }
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 26);
        blackNodeNum++;
        //              Q{blackNodeNum}={x,y,MaxLength,MaxWidth};
        loop_ub = Q.size(1) + 1;
        Q.set_size(&eb_emlrtRTEI, sp, 1, Q.size(1) + 1);
        Q[loop_ub - 1].f1[0] = static_cast<real_T>(var_sp_x) + 1.0;
        Q[Q.size(1) - 1].f1[1] = static_cast<real_T>(var_sp_y) + 1.0;
        Q[Q.size(1) - 1].f1[2] = MaxLength;
        Q[Q.size(1) - 1].f1[3] = MaxWidth;
        d = ((static_cast<real_T>(var_sp_x) + 1.0) + MaxLength) - 1.0;
        i = static_cast<int32_T>(d +
                                 (1.0 - (static_cast<real_T>(var_sp_x) + 1.0)));
        emlrtForLoopVectorCheckR2021a(static_cast<real_T>(var_sp_x) + 1.0, 1.0,
                                      d, mxDOUBLE_CLASS, i, &c_emlrtRTEI,
                                      (emlrtConstCTX)sp);
        for (loop_ub = 0; loop_ub < i; loop_ub++) {
          MaxArea = static_cast<real_T>(static_cast<uint32_T>(var_sp_x) +
                                        static_cast<uint32_T>(loop_ub)) +
                    1.0;
          covrtLogFor(&emlrtCoverageInstance, 0, 0, 13, 1);
          for (b_loop_ub = 0; b_loop_ub < MaxWidth; b_loop_ub++) {
            covrtLogFor(&emlrtCoverageInstance, 0, 0, 14, 1);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 27);
            f_idx_0 = b_f.size(0);
            f_tmp = b_f.size(1) * b_f.size(2);
            if ((static_cast<int32_T>(MaxArea) < 1) ||
                (static_cast<int32_T>(MaxArea) > b_f.size(0))) {
              emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(MaxArea), 1,
                                            b_f.size(0), &ab_emlrtBCI,
                                            (emlrtConstCTX)sp);
            }
            i1 = (var_sp_y + b_loop_ub) + 1;
            if (i1 > f_tmp) {
              emlrtDynamicBoundsCheckR2012b(i1, 1, f_tmp, &bb_emlrtBCI,
                                            (emlrtConstCTX)sp);
            }
            b_f[(static_cast<int32_T>(MaxArea) + f_idx_0 * (i1 - 1)) - 1] = 7U;
            if (*emlrtBreakCheckR2012bFlagVar != 0) {
              emlrtBreakCheckR2012b((emlrtConstCTX)sp);
            }
          }
          covrtLogFor(&emlrtCoverageInstance, 0, 0, 14, 0);
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b((emlrtConstCTX)sp);
          }
        }
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 13, 0);
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtConstCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 10, 0);
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 9, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 28);
  //  decom_result=org-f
  //  celldisp(Q)
  //  num_of_total_mix= num_of_total_triangular
  num_of_total_mix = blackNodeNum + num_of_total_triangular;
  emlrtDisplayR2012b(emlrt_marshallOut(num_of_total_mix), "num_of_total_mix",
                     &emlrtRTEI, (emlrtCTX)sp);
  // triangular_ratio=4^n/(point_num*n + line_num*2*n +
  // num_of_total_triangular*(2*n+1))
  //  %rect_node_num=rectangleraster2(n,picture)
  //  %rect_ratio=4^n/(2*n*rect_node_num)
  //
  //  %quad_node_num=quadtreezyp2(picture)
  //  %quadtree_ratio=4^n/((3*n-1)*quad_node_num)
  //
  //  %ratio_triangular_to_quadtree=triangular_ratio/quadtree_ratio
  //  %ratio_rectangle_to_quadtree=rect_ratio/quadtree_ratio
  //  完全不知道为什么这段代码放在这，没有任何rectangleraster2的信息
  // ************************************************  The following is the
  // decoder ! ************************************
  std::memset(&res[0], 1, 65536U * sizeof(int8_T));
  //  %*********************************************** triangulars  are decoded
  i = static_cast<int32_T>(num_of_total_triangular);
  emlrtForLoopVectorCheckR2021a(1.0, 1.0, num_of_total_triangular,
                                mxDOUBLE_CLASS,
                                static_cast<int32_T>(num_of_total_triangular),
                                &d_emlrtRTEI, (emlrtConstCTX)sp);
  for (k = 0; k < i; k++) {
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 15, 1);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 29);
    if (k > Q_tri.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(k, 0, Q_tri.size(1) - 1, &i_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (k > Q_tri.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(k, 0, Q_tri.size(1) - 1, &h_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    Length0 = Q_tri[k].f1[1];
    if (k > Q_tri.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(k, 0, Q_tri.size(1) - 1, &g_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    MaxArea = Q_tri[k].f1[2];
    if (k > Q_tri.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(k, 0, Q_tri.size(1) - 1, &f_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (k > Q_tri.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(k, 0, Q_tri.size(1) - 1, &e_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    last = Q_tri[k].f1[4];
    d = Q_tri[k].f1[0];
    if (d != static_cast<int32_T>(d)) {
      emlrtIntegerCheckR2012b(d, &emlrtDCI, (emlrtConstCTX)sp);
    }
    switch (static_cast<int32_T>(d)) {
    case 0: {
      covrtLogSwitch(&emlrtCoverageInstance, 0, 0, 0, 1);
      covrtLogBasicBlock(&emlrtCoverageInstance, 0, 30);
      //  upper triangular
      MaxLength = 0.0;
      i1 = static_cast<int32_T>(Q_tri[k].f1[3] + (1.0 - Q_tri[k].f1[1]));
      emlrtForLoopVectorCheckR2021a(Q_tri[k].f1[1], 1.0, Q_tri[k].f1[3],
                                    mxDOUBLE_CLASS, i1, &e_emlrtRTEI,
                                    (emlrtConstCTX)sp);
      for (loop_ub = 0; loop_ub < i1; loop_ub++) {
        num_of_total_triangular = Length0 + static_cast<real_T>(loop_ub);
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 16, 1);
        d = MaxArea + MaxLength;
        i2 = static_cast<int32_T>(last + (1.0 - d));
        emlrtForLoopVectorCheckR2021a(d, 1.0, last, mxDOUBLE_CLASS, i2,
                                      &f_emlrtRTEI, (emlrtConstCTX)sp);
        for (j = 0; j < i2; j++) {
          real_T d1;
          covrtLogFor(&emlrtCoverageInstance, 0, 0, 17, 1);
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 31);
          //                          res(i,j)=8;
          if ((static_cast<int32_T>(num_of_total_triangular) < 1) ||
              (static_cast<int32_T>(num_of_total_triangular) > 256)) {
            emlrtDynamicBoundsCheckR2012b(
                static_cast<int32_T>(num_of_total_triangular), 1, 256,
                &n_emlrtBCI, (emlrtConstCTX)sp);
          }
          d1 = d + static_cast<real_T>(j);
          if (d1 != static_cast<int32_T>(d1)) {
            emlrtIntegerCheckR2012b(d1, &b_emlrtDCI, (emlrtConstCTX)sp);
          }
          if ((static_cast<int32_T>(d1) < 1) ||
              (static_cast<int32_T>(d1) > 256)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(d1), 1, 256,
                                          &o_emlrtBCI, (emlrtConstCTX)sp);
          }
          res[(static_cast<int32_T>(num_of_total_triangular) +
               ((static_cast<int32_T>(d1) - 1) << 8)) -
              1] = 0;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b((emlrtConstCTX)sp);
          }
        }
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 17, 0);
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 32);
        MaxLength++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b((emlrtConstCTX)sp);
        }
      }
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 16, 0);
    } break;
    case 1:
      covrtLogSwitch(&emlrtCoverageInstance, 0, 0, 0, 2);
      covrtLogBasicBlock(&emlrtCoverageInstance, 0, 33);
      //  lower triangular
      MaxLength = 0.0;
      i1 = static_cast<int32_T>(Q_tri[k].f1[3] + (1.0 - Q_tri[k].f1[1]));
      emlrtForLoopVectorCheckR2021a(Q_tri[k].f1[1], 1.0, Q_tri[k].f1[3],
                                    mxDOUBLE_CLASS, i1, &g_emlrtRTEI,
                                    (emlrtConstCTX)sp);
      for (loop_ub = 0; loop_ub < i1; loop_ub++) {
        num_of_total_triangular = Length0 + static_cast<real_T>(loop_ub);
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 18, 1);
        d = MaxArea + MaxLength;
        i2 = static_cast<int32_T>(d + (1.0 - MaxArea));
        emlrtForLoopVectorCheckR2021a(MaxArea, 1.0, d, mxDOUBLE_CLASS, i2,
                                      &h_emlrtRTEI, (emlrtConstCTX)sp);
        for (j = 0; j < i2; j++) {
          covrtLogFor(&emlrtCoverageInstance, 0, 0, 19, 1);
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 34);
          //                          res(i,j)=9;
          if ((static_cast<int32_T>(num_of_total_triangular) < 1) ||
              (static_cast<int32_T>(num_of_total_triangular) > 256)) {
            emlrtDynamicBoundsCheckR2012b(
                static_cast<int32_T>(num_of_total_triangular), 1, 256,
                &p_emlrtBCI, (emlrtConstCTX)sp);
          }
          i3 = static_cast<int32_T>(MaxArea + static_cast<real_T>(j));
          if ((i3 < 1) || (i3 > 256)) {
            emlrtDynamicBoundsCheckR2012b(i3, 1, 256, &q_emlrtBCI,
                                          (emlrtConstCTX)sp);
          }
          res[(static_cast<int32_T>(num_of_total_triangular) +
               ((i3 - 1) << 8)) -
              1] = 0;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b((emlrtConstCTX)sp);
          }
        }
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 19, 0);
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 35);
        MaxLength++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b((emlrtConstCTX)sp);
        }
      }
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 18, 0);
      break;
    default:
      covrtLogSwitch(&emlrtCoverageInstance, 0, 0, 0, 0);
      break;
    }
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 15, 0);
  // *********************************************** lines and points  are
  // decoded
  i = static_cast<int32_T>(blackNodeNum);
  emlrtForLoopVectorCheckR2021a(1.0, 1.0, blackNodeNum, mxDOUBLE_CLASS,
                                static_cast<int32_T>(blackNodeNum),
                                &i_emlrtRTEI, (emlrtConstCTX)sp);
  for (j = 0; j < i; j++) {
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 20, 1);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 36);
    if (j > Q.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(j, 0, Q.size(1) - 1, &d_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (j > Q.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(j, 0, Q.size(1) - 1, &c_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    Length0 = Q[j].f1[1];
    if (j > Q.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(j, 0, Q.size(1) - 1, &b_emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    if (j > Q.size(1) - 1) {
      emlrtDynamicBoundsCheckR2012b(j, 0, Q.size(1) - 1, &emlrtBCI,
                                    (emlrtConstCTX)sp);
    }
    d = (Q[j].f1[0] + Q[j].f1[2]) - 1.0;
    i1 = static_cast<int32_T>(d + (1.0 - Q[j].f1[0]));
    emlrtForLoopVectorCheckR2021a(Q[j].f1[0], 1.0, d, mxDOUBLE_CLASS, i1,
                                  &j_emlrtRTEI, (emlrtConstCTX)sp);
    for (loop_ub = 0; loop_ub < i1; loop_ub++) {
      MaxArea = Q[j].f1[0] + static_cast<real_T>(loop_ub);
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 21, 1);
      d = (Length0 + Q[j].f1[3]) - 1.0;
      i2 = static_cast<int32_T>(d + (1.0 - Length0));
      emlrtForLoopVectorCheckR2021a(Length0, 1.0, d, mxDOUBLE_CLASS, i2,
                                    &k_emlrtRTEI, (emlrtConstCTX)sp);
      for (b_loop_ub = 0; b_loop_ub < i2; b_loop_ub++) {
        covrtLogFor(&emlrtCoverageInstance, 0, 0, 22, 1);
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 37);
        //              res(a,b)=7;
        if ((static_cast<int32_T>(MaxArea) < 1) ||
            (static_cast<int32_T>(MaxArea) > 256)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(MaxArea), 1, 256,
                                        &r_emlrtBCI, (emlrtConstCTX)sp);
        }
        i3 = static_cast<int32_T>(Length0 + static_cast<real_T>(b_loop_ub));
        if ((i3 < 1) || (i3 > 256)) {
          emlrtDynamicBoundsCheckR2012b(i3, 1, 256, &s_emlrtBCI,
                                        (emlrtConstCTX)sp);
        }
        res[(static_cast<int32_T>(MaxArea) + ((i3 - 1) << 8)) - 1] = 0;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b((emlrtConstCTX)sp);
        }
      }
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 22, 0);
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtConstCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 21, 0);
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtConstCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 20, 0);
  // mark_tri_rec;
  // res;
  // diff=sum(sum(res-org))
  b_f.set_size(&fb_emlrtRTEI, sp, org.size(0), org.size(1), org.size(2));
  for (i = 0; i < loop_ub_tmp; i++) {
    uint8_T u;
    i1 = org[i] * 255;
    if (i1 < 256) {
      u = static_cast<uint8_T>(i1);
    } else {
      u = MAX_uint8_T;
    }
    b_f[i] = u;
  }
  st.site = &ib_emlrtRSI;
  imshow(st, emlrt_marshallOut(b_f), emlrtMCI);
  st.site = &ib_emlrtRSI;
  title(st, emlrt_marshallOut(st, b_cv), b_emlrtMCI);
  st.site = &kb_emlrtRSI;
  figure(st, c_emlrtMCI);
  for (i = 0; i < 65536; i++) {
    b_res[i] = static_cast<uint8_T>(static_cast<uint32_T>(res[i]) * 255U);
  }
  st.site = &jb_emlrtRSI;
  imshow(st, emlrt_marshallOut(b_res), d_emlrtMCI);
  st.site = &jb_emlrtRSI;
  title(st, b_emlrt_marshallOut(st, cv1), e_emlrtMCI);
  //  %************************************************
  //  ************************************
  st.site = &g_emlrtRSI;
  coder::toc(st);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)sp);
  return num_of_total_mix;
}

// End of code generation (triangularraster.cpp)
