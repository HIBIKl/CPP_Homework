#pragma once
#include<opencv.hpp>
#include <opencv2\imgproc\types_c.h> //û�õ�ͷ�ļ�
#include<iostream>
#include<vector>
#include<cmath>
//����windows.h
//#include <windows.h>
#include <time.h>

//using namespace cv;
using namespace std;

//��ɫ��
class algorithmColor
{
    cv::Point lt;
    cv::Point rb;
    cv::Scalar grey;
public:
    algorithmColor() { grey[0] = grey[1] = grey[2] = grey[3] = -1; }
    void setLt(cv::Point lt) { this->lt = lt; }
    void setRb(cv::Point rb) { this->rb = rb; }
    cv::Point getLt() { return lt; }
    cv::Point getRb() { return rb; }
    void setGrey(cv::Scalar grey) { this->grey = grey; }
    cv::Scalar getGrey() { return grey; }
};

//����ACCESS_MASK��ͻ
//��ʱ
//class MyTimer {
//private:
//    int _freq;
//    LARGE_INTEGER _begin;
//    LARGE_INTEGER _end;
//public:
//    long costTime;            // ���ѵ�ʱ��(��ȷ��΢��)
//public:
//    MyTimer() {
//        LARGE_INTEGER tmp;
//        QueryPerformanceFrequency(&tmp);
//        _freq = tmp.QuadPart;
//        costTime = 0;
//    }
//    void Start() {            // ��ʼ��ʱ
//        QueryPerformanceCounter(&_begin);
//    }
//    void End() {                // ������ʱ
//        QueryPerformanceCounter(&_end);
//        costTime = (long)((_end.QuadPart - _begin.QuadPart) * 1000 / _freq);
//    }
//    void Reset() {            // ��ʱ��0
//        costTime = 0;
//    }
//};


int diag_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4);
int hori_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4);


bool isSameBlock(cv::Mat f, cv::Mat mark, cv::Point lt, cv::Point rb, int xgm);
void mark(cv::Mat& mark, cv::Point lt, cv::Point rb);
void EnCode(cv::Mat& R, int height, int width, vector<char>& Q);
void Decode(cv::Mat& R, int height, int width, const vector<char>& Q);
cv::Point REHelper_Diagonal(cv::Mat f, cv::Mat mark, int M, int N, cv::Point start, int xgm);
cv::Point REHelper_Horizonal(cv::Mat f, cv::Mat mark, int M, int N, cv::Point start, int xgm);
void RNAMCEncoding_Diagonal(cv::Mat f, cv::Mat& R, cv::Mat& Matrix, int M, int N, vector<algorithmColor>& p, vector<char>& q, int xgm);
void RNAMCEncoding_Horizonal(cv::Mat f, cv::Mat& R, cv::Mat& Matrix, int M, int N, vector<algorithmColor>& p, vector<char>& q, int xgm);
void RDHelper(cv::Mat& R, algorithmColor p1);
void RNAMCDecoding(cv::Mat& R, int M, int N, vector<algorithmColor> p, vector<char> q);
double PSNR(cv::Mat f, cv::Mat R, int M, int N);
double BPP(vector<algorithmColor> p, int M, int N, vector<char> q);
void segmentDisplay(cv::Mat& display, vector<algorithmColor> p);
