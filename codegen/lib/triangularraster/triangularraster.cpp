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
#include "sum.h"
#include "tic.h"
#include "toc.h"
#include "triangularraster_data.h"
#include "triangularraster_initialize.h"
#include "coder_array.h"

// Function Definitions
double triangularraster(const coder::array<char, 2U> &f)
{
  coder::array<double, 2U> c_f;
  coder::array<double, 2U> x;
  coder::array<unsigned char, 3U> b_f;
  double x_data[510];
  double Length0;
  double MaxLength;
  double blackNodeNum;
  double num_of_total_mix;
  double num_of_total_triangular;
  int b_loop_ub;
  int f_idx_0;
  int i;
  int istart;
  int j;
  int jend;
  int loop_ub;
  int n;
  if (!isInitialized_triangularraster) {
    triangularraster_initialize();
  }
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
  coder::tic();
  // picture=f;
  coder::imread(f, b_f);
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
  //  n=3
  //  the size of the picture is size * size
  num_of_total_triangular = 0.0;
  for (int var_sp_x{0}; var_sp_x < 255; var_sp_x++) {
    for (int var_sp_y{0}; var_sp_y < 255; var_sp_y++) {
      //          var_sp_x=6;
      //          var_sp_y=4;
      for (int step{0}; step < 255; step++) {
        //      step=2;
        i = (var_sp_x - step) + 256;
        if (i <= 256) {
          istart = (var_sp_y - step) + 256;
          if (istart <= 256) {
            int x_size[2];
            boolean_T b;
            if (var_sp_x + 1 > i) {
              n = 0;
              i = 0;
            } else {
              n = var_sp_x;
            }
            if (var_sp_y + 1 > istart) {
              jend = 0;
              istart = 0;
            } else {
              jend = var_sp_y;
            }
            f_idx_0 = b_f.size(0);
            loop_ub = i - n;
            b_loop_ub = istart - jend;
            c_f.set_size(loop_ub, b_loop_ub);
            for (i = 0; i < b_loop_ub; i++) {
              for (istart = 0; istart < loop_ub; istart++) {
                c_f[istart + c_f.size(0) * i] =
                    b_f[(n + istart) + f_idx_0 * (jend + i)];
              }
            }
            // ***!mcc***************************************************************
            //  k=6
            f_idx_0 = b_f.size(0);
            x.set_size(loop_ub, b_loop_ub);
            for (i = 0; i < b_loop_ub; i++) {
              for (istart = 0; istart < loop_ub; istart++) {
                x[istart + x.size(0) * i] =
                    b_f[(n + istart) + f_idx_0 * (jend + i)];
              }
            }
            b = ((loop_ub == 0) || (b_loop_ub == 0));
            if ((!b) && (loop_ub > 1)) {
              istart = 2;
              n = loop_ub - 2;
              jend = b_loop_ub - 1;
              if (n <= jend) {
                jend = n;
              }
              for (j = 0; j <= jend; j++) {
                for (b_loop_ub = istart; b_loop_ub <= loop_ub; b_loop_ub++) {
                  x[(b_loop_ub + x.size(0) * j) - 1] = 0.0;
                }
                istart++;
              }
            }
            coder::sum(x, x_data, x_size);
            n = x_size[1];
            if (x_size[1] == 0) {
              Length0 = 0.0;
            } else {
              Length0 = x_data[0];
              for (b_loop_ub = 2; b_loop_ub <= n; b_loop_ub++) {
                Length0 += x_data[b_loop_ub - 1];
              }
            }
            if (Length0 == 0.0) {
              num_of_total_triangular++;
              // 存储斜边
              // x3=1;y3=size_temp;
              //                          Q_tri{num_of_total_triangular}={0,x1_abs,y1_abs,x2_abs,y2_abs};
              i = 255 - step;
              for (b_loop_ub = 0; b_loop_ub <= i; b_loop_ub++) {
                istart = 255 - (step + b_loop_ub);
                for (j = 0; j <= istart; j++) {
                  f_idx_0 = b_f.size(0);
                  b_f[(b_loop_ub + var_sp_x) +
                      f_idx_0 * ((b_loop_ub + j) + var_sp_y)] = 8U;
                }
              }
            }
            // ******************************************************************
            // ******************************************************************
            //       k=-6
            n = c_f.size(1);
            if ((!b) && (c_f.size(1) > 1)) {
              jend = 1;
              for (j = 2; j <= n; j++) {
                for (b_loop_ub = 0; b_loop_ub < jend; b_loop_ub++) {
                  c_f[b_loop_ub + c_f.size(0) * (j - 1)] = 0.0;
                }
                if (jend < c_f.size(0)) {
                  jend++;
                }
              }
            }
            coder::sum(c_f, x_data, x_size);
            n = x_size[1];
            if (x_size[1] == 0) {
              Length0 = 0.0;
            } else {
              Length0 = x_data[0];
              for (b_loop_ub = 2; b_loop_ub <= n; b_loop_ub++) {
                Length0 += x_data[b_loop_ub - 1];
              }
            }
            if (Length0 == 0.0) {
              num_of_total_triangular++;
              i = 255 - step;
              for (b_loop_ub = 0; b_loop_ub <= i; b_loop_ub++) {
                for (j = 0; j <= b_loop_ub; j++) {
                  f_idx_0 = b_f.size(0);
                  b_f[(b_loop_ub + var_sp_x) + f_idx_0 * (j + var_sp_y)] = 9U;
                }
              }
            }
            // ******************************************************************
            //  imshow(uint8(f*255))
            //  celldisp(Q)
          }
        }
      }
    }
  }
  //  *************************************************************************
  //     part two
  //  *************************************************************************
  blackNodeNum = 0.0;
  MaxLength = 0.0;
  istart = -1;
  for (loop_ub = 0; loop_ub < 256; loop_ub++) {
    for (int var_sp_x{0}; var_sp_x < 256; var_sp_x++) {
      f_idx_0 = b_f.size(0);
      if (b_f[loop_ub + f_idx_0 * var_sp_x] == 0) {
        double MaxArea;
        double last;
        boolean_T exitg1;
        //  Length=1;Width=1;MaxArea=1;
        MaxArea = 0.0;
        last = 0.0;
        j = 0;
        exitg1 = false;
        while ((!exitg1) && (j <= 255 - var_sp_x)) {
          boolean_T exitg2;
          n = (var_sp_x + j) + 1;
          Length0 = 0.0;
          b_loop_ub = 0;
          exitg2 = false;
          while ((!exitg2) && (b_loop_ub <= 255 - loop_ub)) {
            jend = loop_ub + b_loop_ub;
            if ((n != var_sp_x + 1) &&
                (static_cast<double>(jend - loop_ub) + 1.0 > last)) {
              exitg2 = true;
            } else {
              f_idx_0 = b_f.size(0);
              if (b_f[jend + f_idx_0 * (n - 1)] != 0) {
                exitg2 = true;
              } else {
                Length0++;
                b_loop_ub++;
              }
            }
          }
          // end for k=x:2^n
          if (n == var_sp_x + 1) {
            last = Length0;
          }
          if (Length0 < last) {
            last = Length0;
          }
          f_idx_0 = b_f.size(0);
          if (b_f[loop_ub + f_idx_0 * (n - 1)] != 0) {
            exitg1 = true;
          } else {
            n = (n - var_sp_x) - 1;
            Length0 = last * (static_cast<double>(n) + 1.0);
            if (Length0 > MaxArea) {
              //   if Area>MaxArea
              MaxArea = Length0;
              MaxLength = last;
              istart = n;
            }
            j++;
          }
        }
        //  for j=y:2^n
        blackNodeNum++;
        //              Q{blackNodeNum}={x,y,MaxLength,MaxWidth};
        i = static_cast<int>(
            (((static_cast<double>(loop_ub) + 1.0) + MaxLength) - 1.0) +
            (1.0 - (static_cast<double>(loop_ub) + 1.0)));
        for (n = 0; n < i; n++) {
          unsigned int a;
          a = (static_cast<unsigned int>(loop_ub) +
               static_cast<unsigned int>(n)) +
              1U;
          for (jend = 0; jend <= istart; jend++) {
            f_idx_0 = b_f.size(0);
            b_f[(static_cast<int>(a) + f_idx_0 * (var_sp_x + jend)) - 1] = 7U;
          }
        }
      }
    }
  }
  //  decom_result=org-f
  //  celldisp(Q)
  //  num_of_total_mix= num_of_total_triangular
  num_of_total_mix = blackNodeNum + num_of_total_triangular;
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
  //  %*********************************************** triangulars  are decoded
  // *********************************************** lines and points  are
  // decoded mark_tri_rec; res; diff=sum(sum(res-org))
  //  %************************************************
  //  ************************************
  coder::toc();
  return num_of_total_mix;
}

// End of code generation (triangularraster.cpp)
