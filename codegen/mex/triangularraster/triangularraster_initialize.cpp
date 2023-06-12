//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// triangularraster_initialize.cpp
//
// Code generation for function 'triangularraster_initialize'
//

// Include files
#include "triangularraster_initialize.h"
#include "_coder_triangularraster_mex.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "triangularraster_data.h"

// Function Declarations
static void triangularraster_once();

// Function Definitions
static void triangularraster_once()
{
  int32_T caseExprEnds_0_0[3]{8353, 7763, 8063};
  int32_T caseStarts_0_0[3]{8344, 7757, 8057};
  int32_T postfix_exprs_0_0[3]{0, 1, -3};
  int32_T postfix_exprs_0_1[3]{0, 1, -3};
  int32_T cond_ends_0_0[2]{2102, 2127};
  int32_T cond_ends_0_1[2]{5625, 5642};
  int32_T cond_starts_0_0[2]{2083, 2108};
  int32_T cond_starts_0_1[2]{5616, 5629};
  int32_T postfix_exprs_0_2[2]{0, -1};
  int32_T postfix_exprs_0_3[2]{0, -1};
  int32_T cond_ends_0_2{5688};
  int32_T cond_ends_0_3{5903};
  int32_T cond_starts_0_2{5679};
  int32_T cond_starts_0_3{5894};
  mex_InitInfAndNan();
  savedTime_not_empty_init();
  // Allocate instance data
  covrtAllocateInstanceData(&emlrtCoverageInstance);
  // Initialize Coverage Information
  covrtScriptInit(
      &emlrtCoverageInstance,
      "D:\\school\\\xe4\xbd\x9c\xe4\xb8\x9a\\C++\\matlab\\triangularraster.m",
      0U, 1U, 38U, 13U, 0U, 0U, 1U, 23U, 0U, 6U, 4U);
  // Initialize Function Information
  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "triangularraster", 769, -1,
               8971);
  // Initialize Basic Block Information
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 37U, 8600, -1, 8663);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 36U, 8474, -1, 8544);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 35U, 8304, -1, 8316);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 34U, 8256, -1, 8267);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 33U, 8097, -1, 8104);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 32U, 8003, -1, 8015);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 31U, 7955, -1, 7966);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 30U, 7796, -1, 7803);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 29U, 7618, -1, 7731);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 28U, 6752, -1, 7503);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 27U, 6624, -1, 6655);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 26U, 6417, -1, 6553);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 25U, 6368, -1, 6388);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 24U, 6312, -1, 6334);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 21U, 5906, -1, 5912);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 23U, 6117, -1, 6206);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 22U, 5933, -1, 6045);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 20U, 5854, -1, 5867);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 19U, 5803, -1, 5816);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 16U, 5644, -1, 5650);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 17U, 5691, -1, 5697);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 18U, 5722, -1, 5740);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 15U, 5554, -1, 5564);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 14U, 5466, -1, 5513);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 13U, 5366, -1, 5389);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 12U, 4938, -1, 5329);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 11U, 4691, -1, 4696);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 10U, 4648, -1, 4654);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 9U, 4508, -1, 4542);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 8U, 3869, -1, 4399);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 7U, 3764, -1, 3791);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 6U, 3476, -1, 3481);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 5U, 3433, -1, 3439);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 4U, 3294, -1, 3328);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 3U, 2568, -1, 3182);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 2U, 2463, -1, 2490);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 1U, 2145, -1, 2255);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 822, -1, 1903);
  // Initialize If Information
  covrtIfInit(&emlrtCoverageInstance, 0U, 0U, 2079, 2128, -1, 4900);
  covrtIfInit(&emlrtCoverageInstance, 0U, 2U, 2511, 2543, -1, 3412);
  covrtIfInit(&emlrtCoverageInstance, 0U, 4U, 3812, 3844, -1, 4626);
  covrtIfInit(&emlrtCoverageInstance, 0U, 5U, 5398, 5411, -1, 6703);
  covrtIfInit(&emlrtCoverageInstance, 0U, 6U, 5613, 5643, 5674, 5701);
  covrtIfInit(&emlrtCoverageInstance, 0U, 7U, 5674, 5689, 5759, 5760);
  covrtIfInit(&emlrtCoverageInstance, 0U, 8U, 5794, 5801, -1, 5820);
  covrtIfInit(&emlrtCoverageInstance, 0U, 9U, 5838, 5853, -1, 5871);
  covrtIfInit(&emlrtCoverageInstance, 0U, 10U, 5889, 5904, 6062, 6226);
  covrtIfInit(&emlrtCoverageInstance, 0U, 11U, 6062, 6077, -1, 6226);
  covrtIfInit(&emlrtCoverageInstance, 0U, 12U, 6270, 6294, 6347, 6404);
  covrtIfInit(&emlrtCoverageInstance, 0U, 1U, 2395, 3459, 2395, 3459);
  covrtIfInit(&emlrtCoverageInstance, 0U, 3U, 3686, 4674, 3686, 4674);
  // Initialize MCDC Information
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 0U, 2082, 2128, 2, 0,
                cond_starts_0_0, cond_ends_0_0, 3, postfix_exprs_0_0);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 1U, 5616, 5643, 2, 2,
                cond_starts_0_1, cond_ends_0_1, 3, postfix_exprs_0_1);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 2U, 5677, 5689, 1, 4,
                &cond_starts_0_2, &cond_ends_0_2, 2, postfix_exprs_0_2);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 3U, 5892, 5904, 1, 5,
                &cond_starts_0_3, &cond_ends_0_3, 2, postfix_exprs_0_3);
  // Initialize For Information
  covrtForInit(&emlrtCoverageInstance, 0U, 0U, 1904, 1925, 4937);
  covrtForInit(&emlrtCoverageInstance, 0U, 1U, 1930, 1951, 4933);
  covrtForInit(&emlrtCoverageInstance, 0U, 2U, 2020, 2040, 4925);
  covrtForInit(&emlrtCoverageInstance, 0U, 3U, 2395, 2416, 3459);
  covrtForInit(&emlrtCoverageInstance, 0U, 4U, 3207, 3218, 3388);
  covrtForInit(&emlrtCoverageInstance, 0U, 5U, 3247, 3261, 3360);
  covrtForInit(&emlrtCoverageInstance, 0U, 6U, 3686, 3711, 4674);
  covrtForInit(&emlrtCoverageInstance, 0U, 7U, 4424, 4435, 4602);
  covrtForInit(&emlrtCoverageInstance, 0U, 8U, 4464, 4475, 4574);
  covrtForInit(&emlrtCoverageInstance, 0U, 9U, 5330, 5341, 6715);
  covrtForInit(&emlrtCoverageInstance, 0U, 10U, 5346, 5357, 6711);
  covrtForInit(&emlrtCoverageInstance, 0U, 11U, 5526, 5537, 6242);
  covrtForInit(&emlrtCoverageInstance, 0U, 12U, 5581, 5592, 5760);
  covrtForInit(&emlrtCoverageInstance, 0U, 13U, 6566, 6587, 6691);
  covrtForInit(&emlrtCoverageInstance, 0U, 14U, 6604, 6624, 6675);
  covrtForInit(&emlrtCoverageInstance, 0U, 15U, 7581, 7612, 8367);
  covrtForInit(&emlrtCoverageInstance, 0U, 16U, 7816, 7835, 8045);
  covrtForInit(&emlrtCoverageInstance, 0U, 17U, 7852, 7876, 7986);
  covrtForInit(&emlrtCoverageInstance, 0U, 18U, 8117, 8136, 8332);
  covrtForInit(&emlrtCoverageInstance, 0U, 19U, 8153, 8177, 8287);
  covrtForInit(&emlrtCoverageInstance, 0U, 20U, 8449, 8469, 8687);
  covrtForInit(&emlrtCoverageInstance, 0U, 21U, 8550, 8571, 8683);
  covrtForInit(&emlrtCoverageInstance, 0U, 22U, 8580, 8600, 8675);
  // Initialize While Information
  // Initialize Switch Information
  covrtSwitchInit(&emlrtCoverageInstance, 0U, 0U, 7737, 7748, 8362, 3U,
                  caseStarts_0_0, caseExprEnds_0_0);
  // Start callback for coverage engine
  covrtScriptStart(&emlrtCoverageInstance, 0U);
}

void triangularraster_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2022b(&st);
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    triangularraster_once();
  }
}

// End of code generation (triangularraster_initialize.cpp)
