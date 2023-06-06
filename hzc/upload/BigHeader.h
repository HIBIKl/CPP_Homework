#pragma once
#include<opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<iostream>
#include<vector>
#include<cmath>
#include <windows.h>
#include "highgui.h"
#include "cxcore.h"
#include "vector"
#include "cv.h"
#include <map>
#include <time.h>
using namespace cv;
using namespace std;

//颜色表
class Color
{
	Point lt;
	Point rb;
	Scalar grey;
public:
	Color() { grey[0] = grey[1] = grey[2] = grey[3] = -1; }
	void setLt(Point lt) { this->lt = lt; }
	void setRb(Point rb) { this->rb = rb; }
	Point getLt() { return lt; }
	Point getRb() { return rb; }
	void setGrey(Scalar grey) { this->grey = grey; }
	Scalar getGrey() { return grey; }
};
//计时
class MyTimer {
private:
	int _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;
public:
	long costTime;            // 花费的时间(精确到微秒)
public:
	MyTimer() {
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		_freq = tmp.QuadPart;
		costTime = 0;
	}
	void Start() {            // 开始计时
		QueryPerformanceCounter(&_begin);
	}
	void End() {                // 结束计时
		QueryPerformanceCounter(&_end);
		costTime = (long)((_end.QuadPart - _begin.QuadPart) * 1000 / _freq);
	}
	void Reset() {            // 计时清0
		costTime = 0;
	}
};

#define INT_MAX 2147483647
struct Location
{
	int x1;
	int x2;
	int y1;
	int y2;
	Location(int ax, int ay, int bx, int by) :x1(ax), y1(ay), x2(bx), y2(by) {};
	Location() {};
};

struct Block
{
	int start_pos;
	int intervals;
};

struct ColorNode
{
	//0普通矩阵，1宽为1矩阵，2长为1矩阵，3孤立点
	int kind, g1, g2, g3, g4;
	ColorNode(int k, int gg1, int gg2 = -1, int gg3 = -1, int gg4 = -1) :kind(k), g1(gg1), g2(gg2), g3(gg3), g4(gg4) {};
	ColorNode() {};
};

void StartNamCut(const IplImage* img, CvMat* markMatrix, CvMat* R, map<unsigned int, ColorNode>& color_list, map<unsigned int, Location>& block_list, int height, int width, double margin, int& num);
Location FindSameBlock(const IplImage* img, CvMat* markMatrix, CvMat* R, int x1, int y1, double margin, double ratio);
bool IsSameBlock(const IplImage* img, int x1, int y1, int x2, int y2, int margin);
void SetMarkMatrix(CvMat* markMatrix, int x1, int y1, int x2, int y2, int value);
void EnCode(CvMat* R, int height, int width, vector<char>& Q);
void Decode(CvMat* R, int height, int width, const vector<char>& Q);
void RestoreImage(IplImage* img, CvMat* markMatrix, CvMat* R, map<unsigned int, ColorNode>& color_list, int height, int width);
void RestoreImageValue(IplImage* img, ColorNode node, int x1, int y1, int x2, int y2);
double PSNR(IplImage* img, IplImage* newImg);
double BPP(map<unsigned int, ColorNode>& color_list, int xn, int yn, vector<char>& Q);


bool isSameBlock(Mat f,Mat mark, Point lt, Point rb,int xgm);
void mark(Mat &mark, Point lt, Point rb);
void EnCode(Mat &R, int height, int width, vector<char> &Q);
void Decode(Mat &R, int height, int width, const vector<char> &Q);
Point REHelper(Mat f, Mat mark, int M, int N, Point start, int xgm);
void RNAMCEncoding(Mat f, Mat &R, Mat &markMatrix, int M, int N, vector<Color> &p, vector<char> &q, int xgm);
void RDHelper(Mat& R, Color p1);
void RNAMCDecoding(Mat& R, int M, int N, vector<Color> p, vector<char> q);
double PSNR(Mat f, Mat R, int M, int N);
double BPP(vector<Color> p, int M, int N, vector<char> q);
void segmentDisplay(Mat &display, vector<Color> p);