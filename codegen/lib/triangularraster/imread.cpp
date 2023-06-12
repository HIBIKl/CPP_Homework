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
#include "coder_array.h"
#include "libmwjpegreader.h"

// Function Definitions
namespace coder {
void imread(const ::coder::array<char, 2U> &varargin_1,
            ::coder::array<unsigned char, 3U> &X)
{
  array<char, 2U> fname_tmp;
  double outDimsInit[3];
  double outDims_data[3];
  double libjpegMsgCode;
  int outNumDims;
  char libjpegWarnBuffer[200];
  signed char colorSpaceStatus;
  signed char errWarnType;
  signed char fileStatus;
  signed char libjpegReadDone;
  signed char runtimeFileDimsConsistency;
  fname_tmp.set_size(1, varargin_1.size(1) + 1);
  outNumDims = varargin_1.size(1);
  for (int i{0}; i < outNumDims; i++) {
    fname_tmp[i] = varargin_1[i];
  }
  fname_tmp[varargin_1.size(1)] = '\x00';
  outDimsInit[0] = 0.0;
  outDimsInit[1] = 0.0;
  outDimsInit[2] = 0.0;
  for (int i{0}; i < 200; i++) {
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
    if (outNumDims == 3) {
      X.set_size(0, 0, 0);
    } else {
      X.set_size(0, 0, 1);
    }
  } else {
    if (outNumDims == 3) {
      X.set_size(static_cast<int>(outDims_data[0]),
                 static_cast<int>(outDims_data[1]), 3);
    } else {
      X.set_size(static_cast<int>(outDims_data[0]),
                 static_cast<int>(outDims_data[1]), 1);
    }
    jpegreader_uint8(&fname_tmp[0], &X[0], &outDims_data[0],
                     static_cast<double>(outNumDims), &fileStatus,
                     &libjpegReadDone, &libjpegMsgCode, &libjpegWarnBuffer[0],
                     &errWarnType, &runtimeFileDimsConsistency);
    if ((fileStatus == -1) || (libjpegReadDone == 0) || (errWarnType == -1) ||
        (runtimeFileDimsConsistency == 0)) {
      if (outNumDims == 3) {
        X.set_size(0, 0, 0);
      } else {
        X.set_size(0, 0, 1);
      }
    }
  }
}

} // namespace coder

// End of code generation (imread.cpp)
