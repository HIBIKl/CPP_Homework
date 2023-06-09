#pragma once

#include "highgui.h"
#include "cxcore.h"
#include "vector"
#include "cv.h"
#include "ctime"
#include "iostream"
#include "math.h"
#include <iomanip>
#include <fstream>

//stdafx.h
//#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

//targetver.h
// 以下宏定义要求的最低平台。要求的最低平台
// 是具有运行应用程序所需功能的 Windows、Internet Explorer 等产品的
// 最早版本。通过在指定版本及更低版本的平台上启用所有可用的功能，宏可以
// 正常工作。

// 如果必须要针对低于以下指定版本的平台，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

using namespace cv;
using namespace std;
extern int reg_num;
extern int bitnum ;
extern int cur_block ;
extern double thresU ;
extern double thresVar ;
struct colorListStandard//标准矩形颜色表
{
	uchar g1,g2,g3,g4;
};

struct doubleCoordinate{
	int x1;
	int y1;
	int x2;
	int y2;
};//左上角及右下角坐标


struct treeNode {
	uchar confirm;   //标识0或1
	treeNode* parent;
	treeNode* nwchild;
	treeNode* nechild;
};//定义树的结点结构



bool JudgeSameBlock ( double epsilon , IplImage *&img1 , int x1 , int y1 ,int x2 , int y2 );//判断矩形是否为同类块

void BuildTreeT (   IplImage* &img1 , treeNode* &root , vector<colorListStandard> &P, vector<doubleCoordinate> &C, int &num , double epsilon , int x1 , int y1 ,int x2 , int y2 );//分割原图.建立二叉树T.颜色表P


double STC_PSNR ( IplImage *&img1 , IplImage *&imggest );  //计算PSNR
double BPP ( vector<colorListStandard> &P  ,int M , int N , vector<char> &Q );  //计算BPP

void InitialNode (treeNode* &a);//初始化树结点
void InsertNode (treeNode* &root);//插入孩子结点
void LevelOrder(vector<char> &Q , treeNode* root );//层次遍历


inline double Gst(int g2,int g1,int w)
{
    return (g2-g1)/(w-1.0);
}

inline double Gsb(int g4,int g3,int w)
{
    return (g4-g3)/(w-1.0);
}

inline double Gsl(int g3,int g1,int h)
{
    return (g3-g1)/(h-1.0);
}

inline double Gsr(int g4,int g2,int h)
{
    return (g4-g2)/(h-1.0);
}

inline double C1(int w)
{
    return (2*w-1)/(6*(w-1.0));
}

inline double C2(int h)
{
    return (2*h-1)/(6*(h-1.0));
}

inline double D1(int g1,int g2,int g3,int g4,int w,int h)
{
    return (g4-g3-g2+g1)/((w-1.0)*(h-1));
}

inline double Ubi(colorListStandard color , doubleCoordinate coor)
{
  if (coor.x1<coor.x2 && coor.y1<coor.y2)
    return (color.g1+color.g2+color.g3+color.g4)/4.0;
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return color.g1;
  else if (coor.y1 == coor.y2)
    return (color.g1+color.g2)/2.0;
  else if (coor.x1 == coor.x2)
    return (color.g1+color.g3)/2.0;
}

inline double Squaresumbi(colorListStandard color , doubleCoordinate coor)
{

  int w = coor.x2-coor.x1+1;
  int h = coor.y2-coor.y1+1;
  double c1 = C1(w);
  double c2 = C2(h);

  if (coor.x1<coor.x2 && coor.y1<coor.y2)
    return w*h*((0.5-c1-c2)*(color.g1*color.g4+color.g2*color.g3)+c1*(color.g2*color.g4+color.g1*color.g3)+c2*(color.g3*color.g4+color.g1*color.g2)+c1*c2*(color.g4-color.g3-color.g2+color.g1)*(color.g4-color.g3-color.g2+color.g1));
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return w*h*color.g1*color.g1;
  else if (coor.y1 == coor.y2)
    return w*h*(color.g1*color.g2+c1*(color.g2-color.g1)*(color.g2-color.g1));
  else if (coor.x1 == coor.x2)
    return w*h*(color.g1*color.g3+c2*(color.g3-color.g1)*(color.g3-color.g1));
}


inline double Varbi(colorListStandard color , doubleCoordinate coor)
{

  int w = coor.x2-coor.x1+1;
  int h = coor.y2-coor.y1+1;
  double c1 = C1(w);
  double c2 = C2(h);

  if (coor.x1<coor.x2 && coor.y1<coor.y2)
  {
    double ubi = Ubi(color,coor);
    return ((0.5-c1-c2)*(color.g1*color.g4+color.g2*color.g3)+c1*(color.g2*color.g4+color.g1*color.g3)+c2*(color.g3*color.g4+color.g1*color.g2)+c1*c2*(color.g4-color.g3-color.g2+color.g1)*(color.g4-color.g3-color.g2+color.g1)-ubi*ubi);
  }
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return 0;
  else if (coor.y1 == coor.y2)
    return (c1-0.25)*(color.g2-color.g1)*(color.g2-color.g1);
  else if (coor.x1 == coor.x2)
    return (c2-0.25)*(color.g3-color.g1)*(color.g3-color.g1);
}

inline double Uc(int na , int nb , double ua , double ub)
{
  return (na*ua+nb*ub)/(na+nb);

}

inline double Varc(int na , int nb , double vara , double varb,double ua,double ub)
{
  return (na*vara+nb*varb)/(na+nb) + (na*nb*(ua-ub)*(ua-ub))/((na+nb)*(na+nb));

}

struct Corner_Vertex
{
	int x;
	int y;
	Corner_Vertex* Next;
};
struct Edge;
struct Region
{
  double Mean;
  double Var;
  int Size;//边长
  Region* Father;
  int Count;//子孙区域数量
  int SegmentCount;//number of edges shared by the waveform
  Edge* EdgeLink;
};
struct Edge
{
	Edge* PreLink;
	Edge* SucLink;
	Region* Reg;
	Corner_Vertex* First;
	Corner_Vertex* Last;
};

struct Segment
{
	Segment* PreLink;
	Segment* SucLink;
	int Length;
    Edge* ActiveELink;
};


void Region_Segm(Segment* UpperLeft , Segment* &UpperRight , Segment* &PreLowerLeft , int Xleft , int Yupper , int Length , int Width, Region** all_region , vector<colorListStandard> &P , vector<doubleCoordinate> &C  , vector<char> Q,int &num);
inline char Get_bit( vector<char> &Q)
{
	return Q[bitnum++];
}

void SPLIT(Segment* UpperLeft  , int Size,int direction);

void Leaf_Operation(Segment* UpperLeft , Segment* &UpperRight , Segment* &PreLowerLeft , int Xleft , int Yupper , int Length , int Width , vector<colorListStandard> &P , vector<doubleCoordinate> &C ,  Region** all_region);
Region* FindParent(Region *p);
void MakeImggest ( IplImage* &imggest ,  vector<colorListStandard> &P , vector<doubleCoordinate> C , Region** all_region );//建立gest图像

