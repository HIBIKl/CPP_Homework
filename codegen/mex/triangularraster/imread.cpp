//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// imread.cpp
//
// Code generation for function 'imread'
//

// Include files
#include "imread.h"
#include "rt_nonfinite.h"
#include "triangularraster_data.h"
#include "warning.h"
#include "coder_array.h"
#include "libmwjpegreader.h"

// Variable Definitions
static emlrtRSInfo m_emlrtRSI{
    35,                                                         // lineNo
    "imread",                                                   // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pathName
};

static emlrtRSInfo n_emlrtRSI{
    94,                                                         // lineNo
    "imread",                                                   // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pathName
};

static emlrtRSInfo p_emlrtRSI{
    166,                                                        // lineNo
    "imread",                                                   // fcnName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pathName
};

static emlrtRTEInfo m_emlrtRTEI{
    62,                                                         // lineNo
    17,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo n_emlrtRTEI{
    64,                                                         // lineNo
    13,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo o_emlrtRTEI{
    67,                                                         // lineNo
    13,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo p_emlrtRTEI{
    70,                                                         // lineNo
    13,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo q_emlrtRTEI{
    123,                                                        // lineNo
    13,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo r_emlrtRTEI{
    125,                                                        // lineNo
    9,                                                          // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo s_emlrtRTEI{
    130,                                                        // lineNo
    9,                                                          // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo t_emlrtRTEI{
    136,                                                        // lineNo
    13,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtDCInfo d_emlrtDCI{
    105,                                                         // lineNo
    37,                                                          // colNo
    "imread",                                                    // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m", // pName
    4                                                            // checkKind
};

static emlrtDCInfo e_emlrtDCI{
    103,                                                         // lineNo
    37,                                                          // colNo
    "imread",                                                    // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m", // pName
    4                                                            // checkKind
};

static emlrtRTEInfo gb_emlrtRTEI{
    37,                                                         // lineNo
    18,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo hb_emlrtRTEI{
    105,                                                        // lineNo
    26,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

static emlrtRTEInfo ib_emlrtRTEI{
    103,                                                        // lineNo
    26,                                                         // colNo
    "imread",                                                   // fName
    "D:\\matlab\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" // pName
};

// Function Definitions
namespace coder {
void imread(const emlrtStack &sp, const ::coder::array<char_T, 2U> &varargin_1,
            ::coder::array<uint8_T, 3U> &X)
{
  array<char_T, 2U> fname_tmp;
  emlrtStack st;
  real_T outDimsInit[3];
  real_T outDims_data[3];
  real_T libjpegMsgCode;
  int32_T outNumDims;
  char_T libjpegWarnBuffer[200];
  int8_T colorSpaceStatus;
  int8_T errWarnType;
  int8_T fileStatus;
  int8_T libjpegReadDone;
  int8_T runtimeFileDimsConsistency;
  st.prev = &sp;
  st.tls = sp.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtConstCTX)&sp);
  st.site = &m_emlrtRSI;
  fname_tmp.set_size(&gb_emlrtRTEI, &st, 1, varargin_1.size(1) + 1);
  outNumDims = varargin_1.size(1);
  for (int32_T i{0}; i < outNumDims; i++) {
    fname_tmp[i] = varargin_1[i];
  }
  fname_tmp[varargin_1.size(1)] = '\x00';
  outDimsInit[0] = 0.0;
  outDimsInit[1] = 0.0;
  outDimsInit[2] = 0.0;
  for (int32_T i{0}; i < 200; i++) {
    libjpegWarnBuffer[i] = ' ';
  }
  jpegreader_getimagesize(&fname_tmp[0], &outDimsInit[0], &fileStatus,
                          &colorSpaceStatus, &libjpegMsgCode,
                          &libjpegWarnBuffer[0], &errWarnType);
  if (outDimsInit[2] == 3.0) {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outDims_data[2] = 3.0;
    outNumDims = 3;
  } else {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outNumDims = 2;
  }
  if ((fileStatus == -1) || (colorSpaceStatus == -2) ||
      (colorSpaceStatus == -1) || (errWarnType == -1)) {
    if (fileStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &sp, &m_emlrtRTEI, "MATLAB:imagesci:imread:codegenFileOpenError",
          "MATLAB:imagesci:imread:codegenFileOpenError", 3, 4,
          varargin_1.size(1), &varargin_1[0]);
    }
    if (colorSpaceStatus == -2) {
      emlrtErrorWithMessageIdR2018a(&sp, &n_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:cmykColorSpace",
                                    "MATLAB:imagesci:jpg:cmykColorSpace", 0);
    }
    if (colorSpaceStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &sp, &o_emlrtRTEI, "MATLAB:imagesci:jpg:unsupportedJpegColorSpace",
          "MATLAB:imagesci:jpg:unsupportedJpegColorSpace", 0);
    }
    if (errWarnType == -1) {
      emlrtErrorWithMessageIdR2018a(&sp, &p_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
  }
  if (errWarnType == -2) {
    st.site = &n_emlrtRSI;
    internal::warning(st, libjpegWarnBuffer);
  }
  if (outNumDims == 3) {
    if (!(outDims_data[0] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[0], &e_emlrtDCI,
                                  (emlrtConstCTX)&sp);
    }
    if (!(outDims_data[1] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[1], &e_emlrtDCI,
                                  (emlrtConstCTX)&sp);
    }
    X.set_size(&ib_emlrtRTEI, &sp, static_cast<int32_T>(outDims_data[0]),
               static_cast<int32_T>(outDims_data[1]), 3);
  } else {
    if (!(outDims_data[0] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[0], &d_emlrtDCI,
                                  (emlrtConstCTX)&sp);
    }
    if (!(outDims_data[1] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[1], &d_emlrtDCI,
                                  (emlrtConstCTX)&sp);
    }
    X.set_size(&hb_emlrtRTEI, &sp, static_cast<int32_T>(outDims_data[0]),
               static_cast<int32_T>(outDims_data[1]), 1);
  }
  jpegreader_uint8(&fname_tmp[0], &X[0], &outDims_data[0],
                   static_cast<real_T>(outNumDims), &fileStatus,
                   &libjpegReadDone, &libjpegMsgCode, &libjpegWarnBuffer[0],
                   &errWarnType, &runtimeFileDimsConsistency);
  if ((fileStatus == -1) || (libjpegReadDone == 0) || (errWarnType == -1) ||
      (runtimeFileDimsConsistency == 0)) {
    if (fileStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &sp, &q_emlrtRTEI, "MATLAB:imagesci:imread:codegenFileOpenError",
          "MATLAB:imagesci:imread:codegenFileOpenError", 3, 4,
          varargin_1.size(1), &varargin_1[0]);
    }
    if (errWarnType == -1) {
      emlrtErrorWithMessageIdR2018a(&sp, &r_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
    if (libjpegReadDone != 1) {
      emlrtErrorWithMessageIdR2018a(&sp, &s_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
    if (runtimeFileDimsConsistency == 0) {
      emlrtErrorWithMessageIdR2018a(
          &sp, &t_emlrtRTEI, "MATLAB:imagesci:jpg:runtimeDimsInconsistent",
          "MATLAB:imagesci:jpg:runtimeDimsInconsistent", 3, 4,
          varargin_1.size(1), &varargin_1[0]);
    }
  }
  if (errWarnType == -2) {
    st.site = &p_emlrtRSI;
    internal::warning(st, libjpegWarnBuffer);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtConstCTX)&sp);
}

} // namespace coder

// End of code generation (imread.cpp)
