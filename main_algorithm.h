#ifndef MAIN_ALGORITHM_H
#define MAIN_ALGORITHM_H
#pragma once
#include <opencv.hpp>
#include <opencv2\imgproc\types_c.h> //没用的头文件
#include <iostream>
#include <vector>
#include <cmath>
#include "vector"
#include <map>
#include <time.h>
#include "math.h"
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <tchar.h>

// 如果必须要针对低于以下指定版本的平台，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif
using namespace cv;
using namespace std;

//---------------第一层类，包括算法的前置定义---------------
class structAndVariables
{
protected:
    //结构体及变量
    int reg_num;
    int bitnum;
    int cur_block;
    double thresU;
    double thresVar;
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
    //IBR PART
    struct Location
    {
        int x1;
        int x2;
        int y1;
        int y2;
        Location(int ax,int ay,int bx,int by):x1(ax),y1(ay),x2(bx),y2(by){};
        Location(){};
    };
    struct Block
    {
        int start_pos;
        int intervals;
    };
    struct ColorNode
    {
        //0普通矩阵，1宽为1矩阵，2长为1矩阵，3孤立点
        int kind,g1,g2,g3,g4;
        ColorNode(int k,int gg1,int gg2=-1,int gg3=-1,int gg4=-1):kind(k),g1(gg1),g2(gg2),g3(gg3),g4(gg4){};
        ColorNode(){};
    };
    //TNAM PART
    //颜色表
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

};
//---------------第二层类，包括算法的各种函数---------------
//STC
class STC :public structAndVariables
{
private:

    //内联函数
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

    inline char Get_bit( vector<char> &Q)
    {
        return Q[bitnum++];
    }
public:
    int reg_num = 0;
    int bitnum = 0;
    double thresU = 0;
    double thresVar = 0;
    int cur_block = -1;
    //Tree.cpp
    void InitialNode(treeNode*& a)//初始化树结点
    {
        a->parent = NULL; a->nwchild = NULL; a->nechild = NULL; a->confirm = '0';
    }

    void InsertNode(treeNode*& root)//插入孩子结点
    {
        root->nwchild = new treeNode; InitialNode(root->nwchild); root->nwchild->parent = root;
        root->nechild = new treeNode; InitialNode(root->nechild); root->nechild->parent = root;
    }

    void LevelOrder(vector<char>& Q, treeNode* root)//层次遍历
    {
        Q.push_back(root->confirm);
        if (root->nwchild != NULL)
        {
            LevelOrder(Q, root->nwchild);
        }
        if (root->nechild != NULL)
        {
            LevelOrder(Q, root->nechild);
        }
    }

    //PSNR.cpp
    double STC_PSNR(IplImage*& img1, IplImage*& imggest) //计算PSNR

    {
        int M = img1->height;
        int N = img1->width;

        double temp = 0;
        double temp1 = 0;

        for (int y = 0; y < M; y++)
        {
            uchar* ptr1 = (uchar*)(img1->imageData + y * img1->widthStep);
            uchar* ptrg = (uchar*)(imggest->imageData + y * imggest->widthStep);

            for (int x = 0; x < N; x++)
            {
                temp += pow((double)(ptr1[x] - ptrg[x]), 2);
            }
        }


        temp1 = 10 * log10(255.0 * 255 * M * N / temp);
        return (temp1);


    }

    //MakeImggest.cpp
    void MakeImggest(IplImage*& imggest, vector<colorListStandard>& P, vector<doubleCoordinate> C, Region** all_region)//建立gest图像
    {
        uchar g1 = 0, g2 = 0, g3 = 0, g4 = 0;
        for (unsigned int i = 0; i < P.size(); i++)
        {
            g1 = P[i].g1; g2 = P[i].g2;
            g3 = P[i].g3; g4 = P[i].g4;
            int x1 = C[i].x1, x2 = C[i].x2;
            int y1 = C[i].y1, y2 = C[i].y2;

            if (x1 == x2 && y1 == y2)
            {
                uchar* ptr = (uchar*)(imggest->imageData + y1 * imggest->widthStep);
                ptr[x1] = g1;
            }
            else if (x1 == x2)
            {
                for (int y = y1; y <= y2; y++)
                {
                    double i1 = (double)(y - y1) / (double)(y2 - y1);
                    (imggest->imageData + imggest->widthStep * y)[x1] = (int)(g1 + (g2 - g1) * i1);

                }
            }
            else if (y1 == y2)
            {
                for (int x = x1; x <= x2; x++)
                {
                    double i2 = (double)(x - x1) / (double)(x2 - x1);
                    (imggest->imageData + y1 * imggest->widthStep)[x] = (int)(g1 + (g2 - g1) * i2);
                }
            }
            else
            {
                for (int y = y1; y <= y2; y++)
                {
                    uchar* ptr = (uchar*)(imggest->imageData + y * imggest->widthStep);

                    for (int x = x1; x <= x2; x++)
                    {
                        double i1 = (double)(y - C[i].y1) / (C[i].y2 - C[i].y1);
                        double i2 = (double)(x - C[i].x1) / (C[i].x2 - C[i].x1);
                        double g5 = g1 + (g2 - g1) * i2;
                        double g6 = g3 + (g4 - g3) * i2;
                        ptr[x] = g5 + (g6 - g5) * i1;
                    }
                }
            }

        }
    }

    //JudgeSameBlock.cpp
    bool JudgeSameBlock(double epsilon, IplImage*& img1, int x1, int y1, int x2, int y2)//判断矩形是否为同类块zyp
    {

        uchar* ptrtemp = (uchar*)(img1->imageData + y1 * img1->widthStep);
        uchar g1 = ptrtemp[x1], g2 = ptrtemp[x2];
        ptrtemp = (uchar*)(img1->imageData + y2 * img1->widthStep);
        uchar g3 = ptrtemp[x1], g4 = ptrtemp[x2];

        for (int y = y1; y <= y2; y++)
        {
            uchar* ptr = (uchar*)(img1->imageData + y * img1->widthStep);

            for (int x = x1; x <= x2; x++)
            {
                uchar g = ptr[x];
                double i1 = (double)(y - y1) / (y2 - y1);
                double i2 = (double)(x - x1) / (x2 - x1);
                double g5 = g1 + (g2 - g1) * i2;//zyp
                double g6 = g3 + (g4 - g3) * i2;//zyp
                double gest = g5 + (g6 - g5) * i1;//zyp
                //printf("g=%f  g5=%f g6=%f  gest=%f  \n",g, g5,g6,gest);
                //printf("g-gest=%f \n",g-gest);
                if (g - gest >= -epsilon && g - gest <= epsilon)

                {
                    continue;
                }
                else { return false; }

            }
        }



        return true;


    }

    //BuildTreeT.cpp
    void BuildTreeT(IplImage*& img1, treeNode*& root, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, int x1, int y1, int x2, int y2)//分割原图.建立矩阵R.颜色表P
    {
        //uchar* ptr=(uchar*) (img1->imageData);
        //colorListStandard temp;
        //doubleCoordinate tempc;


        //if (root->nwchild==NULL||root->nechild==NULL) cout << "allocation failed" << endl;//递归建立二叉树结构



        uchar* ptr = (uchar*)(img1->imageData);
        colorListStandard temp;
        doubleCoordinate tempc;
        InsertNode(root);

        if (root->nwchild == NULL || root->nechild == NULL) cout << "allocation failed" << endl;//递归建立二叉树结构

        if (num % 2 == 1)  //num不为2的整数倍，水平分隔
        {
            num = 0;

            if (y1 == y2)
            {
                //cout<<"x1"<<x1<<"y1"<<y1<<"x2"<<x2<<"y2"<<y2<<endl;
                root->confirm = '1';
                delete(root->nechild);
                root->nechild = NULL;
                delete(root->nwchild);
                root->nwchild = NULL;
                ptr = (uchar*)(img1->imageData + y1 * img1->widthStep);
                temp.g1 = ptr[x1]; temp.g2 = ptr[x2];
                ptr = (uchar*)(img1->imageData + y2 * img1->widthStep);
                temp.g3 = ptr[x1]; temp.g4 = ptr[x2];
                P.push_back(temp);
                tempc.x1 = x1; tempc.x2 = x2; tempc.y1 = y1; tempc.y2 = y2;
                C.push_back(tempc);
                return;
            }

            if (JudgeSameBlock(epsilon, img1, x1, y1, x2, (y1 + y2 - 1) / 2))   //判断上半部分是否为同类块:nwchild
            {
                root->nwchild->confirm = '1';
                ptr = (uchar*)(img1->imageData + y1 * img1->widthStep);
                temp.g1 = ptr[x1]; temp.g2 = ptr[x2];
                ptr = (uchar*)(img1->imageData + (y1 + y2 - 1) / 2 * img1->widthStep);
                temp.g3 = ptr[x1]; temp.g4 = ptr[x2];
                P.push_back(temp);
                tempc.x1 = x1; tempc.x2 = x2; tempc.y1 = y1; tempc.y2 = (y1 + y2 - 1) / 2;
                C.push_back(tempc);


            }
            else { BuildTreeT(img1, root->nwchild, P, C, num, epsilon, x1, y1, x2, (y1 + y2 - 1) / 2); }//若非同类块则递归调用

            num = 0;

            if (JudgeSameBlock(epsilon, img1, x1, (y1 + y2 + 1) / 2, x2, y2))    //判断下半部分:nechild
            {
                root->nechild->confirm = '1';
                ptr = (uchar*)(img1->imageData + (y1 + y2 + 1) / 2 * img1->widthStep);
                temp.g1 = ptr[x1]; temp.g2 = ptr[x2];
                ptr = (uchar*)(img1->imageData + y2 * img1->widthStep);
                temp.g3 = ptr[x1]; temp.g4 = ptr[x2];
                P.push_back(temp);
                tempc.x1 = x1; tempc.x2 = x2; tempc.y1 = (y1 + y2 + 1) / 2; tempc.y2 = y2;
                C.push_back(tempc);
            }
            else { BuildTreeT(img1, root->nechild, P, C, num, epsilon, x1, (y1 + y2 + 1) / 2, x2, y2); }//递归调用


        }

        else if (num % 2 == 0)  //num是2的整数倍，垂直分隔
        {
            num = 1;

            int vx2 = 0;

            if (x1 == x2)
            {
                //cout<<"x1"<<x1<<"y1"<<y1<<"x2"<<x2<<"y2"<<y2<<endl;
                root->confirm = '1';
                delete(root->nechild);
                root->nechild = NULL;
                delete(root->nwchild);
                root->nwchild = NULL;
                ptr = (uchar*)(img1->imageData + y1 * img1->widthStep);
                temp.g1 = ptr[x1]; temp.g2 = ptr[x2];
                ptr = (uchar*)(img1->imageData + y2 * img1->widthStep);
                temp.g3 = ptr[x1]; temp.g4 = ptr[x2];
                P.push_back(temp);
                tempc.x1 = x1; tempc.x2 = x2; tempc.y1 = y1; tempc.y2 = y2;
                C.push_back(tempc);
                return;
            }


            if (JudgeSameBlock(epsilon, img1, x1, y1, (x1 + x2 - 1) / 2, y2))  //判断左半部分:nwchild
            {
                root->nwchild->confirm = '1';
                ptr = (uchar*)(img1->imageData + y1 * img1->widthStep);
                temp.g1 = ptr[x1]; temp.g2 = ptr[(x1 + x2 - 1) / 2];
                ptr = (uchar*)(img1->imageData + y2 * img1->widthStep);
                temp.g3 = ptr[x1]; temp.g4 = ptr[(x1 + x2 - 1) / 2];
                P.push_back(temp);
                tempc.x1 = x1; tempc.x2 = (x1 + x2 - 1) / 2; tempc.y1 = y1; tempc.y2 = y2;
                C.push_back(tempc);
            }
            else { BuildTreeT(img1, root->nwchild, P, C, num, epsilon, x1, y1, (x1 + x2 - 1) / 2, y2); }//递归调用

            num = 1;


            if (JudgeSameBlock(epsilon, img1, (x1 + x2 + 1) / 2, y1, x2, y2))   //判断右半部分:nechild
            {
                root->nechild->confirm = '1';
                ptr = (uchar*)(img1->imageData + y1 * img1->widthStep);
                temp.g1 = ptr[(x1 + x2 + 1) / 2]; temp.g2 = ptr[x2];
                ptr = (uchar*)(img1->imageData + y2 * img1->widthStep);
                temp.g3 = ptr[(x1 + x2 + 1) / 2]; temp.g4 = ptr[x2];
                P.push_back(temp);
                tempc.x1 = (x1 + x2 + 1) / 2; tempc.x2 = x2; tempc.y1 = y1; tempc.y2 = y2;
                C.push_back(tempc);
            }
            else { BuildTreeT(img1, root->nechild, P, C, num, epsilon, (x1 + x2 + 1) / 2, y1, x2, y2); }//递归调用


        }




        //cout << "done" << endl;
        return;

    }

    void Region_Segm(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, int Xleft, int Yupper, int Length, int Width, Region** all_region, vector<colorListStandard>& P, vector<doubleCoordinate>& C, vector<char> Q, int& num)
    {
        Segment* UR = NULL;
        Segment* PLL = NULL;
        Segment* DUMMY = NULL;
        char bit;

        if (UpperLeft->Length > Width)
        {
            SPLIT(UpperLeft, Width, 0);
        }

        if (UpperLeft->SucLink != NULL && UpperLeft->SucLink->Length > Length)

        {
            SPLIT(UpperLeft->SucLink, Length, 1);
        }

        bit = Get_bit(Q);
        //cout<<"bitnum"<<bitnum<<" Q size"<<Q.size()<<endl;

        if (bit == '0')
        {
            if (num % 2 == 0) //垂直
            {
                num = 1;
                Region_Segm(UpperLeft, UR, PreLowerLeft, Xleft, Yupper, Length / 2, Width, all_region, P, C, Q, num);
                num = 1;
                Region_Segm(UR, UpperRight, DUMMY, Xleft + Length / 2, Yupper, Length - Length / 2, Width, all_region, P, C, Q, num);
            }
            else //水平
            {
                num = 0;
                Region_Segm(UpperLeft, UpperRight, PLL, Xleft, Yupper, Length, Width / 2, all_region, P, C, Q, num);
                num = 0;
                Region_Segm(PLL, UR, PreLowerLeft, Xleft, Yupper + Width / 2, Length, Width - Width / 2, all_region, P, C, Q, num);
            }
            /*Region_Segm(UpperLeft , UR , PLL , Xleft , Yupper , Size/2 , all_region  ,P , C  ,Q);
        Region_Segm(UR , UpperRight , DUMMY , Xleft + Size/2 , Yupper , Size/2 , all_region ,P , C  ,Q);
        Region_Segm(PLL , UR, PreLowerLeft , Xleft , Yupper  + Size/2 , Size/2 , all_region ,P , C  ,Q);
        Region_Segm(UR  , DUMMY  , DUMMY , Xleft + Size/2 , Yupper  + Size/2 , Size/2 , all_region ,P , C  ,Q);*/
        }
        else
        {
            cur_block++;
            if (Xleft == C[cur_block].x1 && Yupper == C[cur_block].y1)
            {
                if ((Xleft + Length - 1) != C[cur_block].x2 && (Yupper + Width - 1) != C[cur_block].y2)
                {
                    cout << cur_block << endl;
                }
            }
            Leaf_Operation(UpperLeft, UpperRight, PreLowerLeft, Xleft, Yupper, Length, Width, P, C, all_region);
        }
    }

    void Leaf_Operation(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, int Xleft, int Yupper, int Length, int Width, vector<colorListStandard>& P, vector<doubleCoordinate>& C, Region** all_region)
    {
        //find lower left = start_segment;and find prelowerleft
        //int cur_block = bitnum - 1;
        int side_length = Width;
        Segment* start_segment = UpperLeft;
        while ((side_length = side_length - start_segment->Length) > 0)
            start_segment = start_segment->PreLink;

        PreLowerLeft = start_segment->PreLink;
        side_length = 0;

        //allocate new region,allocate new edge
        Region* cur_region = new Region;
        all_region[cur_block] = cur_region;

        Edge* active_right = new Edge;
        Edge* inactive = new Edge;
        Edge* active_down = new Edge;

        active_right->SucLink = active_down;
        active_right->PreLink = inactive;
        active_right->Reg = cur_region;


        active_down->SucLink = inactive;
        active_down->PreLink = active_right;
        active_down->Reg = cur_region;


        inactive->SucLink = active_right;
        inactive->PreLink = active_down;
        inactive->Reg = NULL;

        //Corner_Vertex* leftdown = new Corner_Vertex;
        //Corner_Vertex* leftup = new Corner_Vertex;
        //Corner_Vertex* rightup = new Corner_Vertex;

        //leftdown->x = Xleft;
        //leftdown->y = Yupper + Size;
        //leftdown->Next = leftup;

        //leftup->x = Xleft;
        //leftup->y = Yupper ;
        //leftup->Next = rightup;

        //rightup->x = Xleft + Size;
        //rightup->y = Yupper ;
        //rightup->Next = NULL;


        cur_region->Father = NULL;//
        cur_region->Count = 0;
        cur_region->EdgeLink = inactive;//
        cur_region->Mean = Ubi(P[cur_block], C[cur_block]);//
        cur_region->Var = Varbi(P[cur_block], C[cur_block]);//
        //cur_region->Size = Size*Size;
        cur_region->Size = Length * Width;
        cur_region->SegmentCount = 2;


        //cout << "cur_block:" << cur_block <<  endl;
        reg_num++;
        //遍历每个SEGMENT
        while (true)
        {
            //cout << start_segment->Length << "  " << endl;

            if (start_segment->ActiveELink != NULL && start_segment->ActiveELink->Reg != NULL)
            {
                Region* neighbour_region = start_segment->ActiveELink->Reg;
                Region* neighbour_father = FindParent(neighbour_region);
                Region* cur_father = FindParent(cur_region);
                //同一区域
                if (neighbour_father == cur_father)
                {
                }
                //不同区域
                else
                {
                    double varnew = Varc(cur_father->Size, neighbour_father->Size, cur_father->Var, neighbour_father->Var, cur_father->Mean, neighbour_father->Mean);
                    //可以合并
                    if (neighbour_father->Mean - cur_father->Mean >= -thresU && neighbour_father->Mean - cur_father->Mean <= thresU && varnew <= thresVar)
                    {

                        neighbour_father->Mean = Uc(cur_father->Size, neighbour_father->Size, cur_father->Mean, neighbour_father->Mean);
                        neighbour_father->Size += cur_father->Size;
                        neighbour_father->Var = varnew;
                        cur_father->Father = neighbour_father;
                        reg_num--;
                    }
                    //不能合并
                    else
                    {

                    }
                }

            }





            if ((side_length = side_length + start_segment->Length) == (Length + Width))
                break;
            else
            {
                start_segment = start_segment->SucLink;
                //delete(start_segment->PreLink);//delete old segment
            }

        }

        //此块遍历完成,重新构造waveform,Upperright

        if (start_segment != NULL && start_segment->SucLink != NULL)
        {
            start_segment = start_segment->SucLink;
            //delete(start_segment->PreLink);
        }
        else
        {
            //delete (start_segment);
        }
        Segment* downseg = new Segment;
        Segment* rightseg = new Segment;
        downseg->ActiveELink = active_down;
        downseg->Length = Length;
        downseg->PreLink = PreLowerLeft;
        if (PreLowerLeft != NULL)
            PreLowerLeft->SucLink = downseg;
        downseg->SucLink = rightseg;

        rightseg->ActiveELink = active_right;
        rightseg->Length = Width;
        rightseg->PreLink = downseg;
        rightseg->SucLink = start_segment;
        if (start_segment != NULL)
            start_segment->PreLink = rightseg;

        UpperRight = rightseg;

    }

    void SPLIT(Segment* UpperLeft, int Size, int direction)
    {
        Segment* late_half = new Segment;
        late_half->ActiveELink = UpperLeft->ActiveELink;
        if (direction == 0)
        {
            late_half->Length = (UpperLeft->Length + 1) / 2;
            UpperLeft->Length /= 2;
        }
        else
        {
            late_half->Length = (UpperLeft->Length) / 2;
            UpperLeft->Length = (UpperLeft->Length + 1) / 2;
        }
        late_half->SucLink = UpperLeft;
        late_half->PreLink = UpperLeft->PreLink;
        UpperLeft->PreLink = late_half;
        if (late_half->PreLink != NULL)
            late_half->PreLink->SucLink = late_half;
    }

    Region* FindParent(Region* p)
    {
        if (p->Father != NULL)
        {
            p->Father = FindParent(p->Father);
            return p->Father;
        }
        else return p;
    }

    //BPP.cpp

    double BPP(vector<colorListStandard>& P, int M, int N, vector<char>& Q)  //计算BPP

    {

        double b = (Q.size() + 32.0 * P.size()) / (M * N);
        //double b = 8*(Q.size()+32.0*P.size())/(M*N*8);

        //cout << fixed << setprecision(4) << "Length of the linear tree table: " << Q.size() << " bits." << endl;
        //cout << fixed << setprecision(4) << "Length of the color table      : " << 32.0*P.size() << " bits." << endl;
        return b;
    }



};
//IBR
class IBR :public structAndVariables
{
public:
    //StartNameCut.cpp
    void SetMarkMatrix(CvMat* markMatrix, int x1, int y1, int x2, int y2, int value)
    {
        for (int y = y1; y <= y2; y++)
        {
            for (int x = x1; x <= x2; x++)
            {
                (markMatrix->data.ptr + markMatrix->step * y)[x] = value;
            }
        }
    }

    bool IsSameBlock(const IplImage* img, int x1, int y1, int x2, int y2, int margin)
    {
        uchar* gy1 = (uchar*)img->imageData + y1 * img->widthStep;
        uchar* g1 = gy1 + x1;
        uchar* g2 = gy1 + x2;
        uchar* gy2 = (uchar*)img->imageData + y2 * img->widthStep;
        uchar* g3 = gy2 + x1;
        uchar* g4 = gy2 + x2;
        bool returnValue = true;

        if (x1 == x2 && y1 == y2)
        {
            returnValue = true;
        }
        else if (y1 == y2)
        {
            for (int x = x1 + 1; x < x2; x++)
            {
                double i2 = (double)(x - x1) / (double)(x2 - x1);
                double g = *g1 + (*g4 - *g1) * i2;
                uchar* gValue = gy1 + x;
                if (abs(*gValue - g) > margin)
                {
                    returnValue = false;
                    break;
                }

            }
        }
        else if (x1 == x2)
        {
            for (int y = y1 + 1; y < y2; y++)
            {
                double i1 = (double)(y - y1) / (double)(y2 - y1);
                double g = *g1 + (*g4 - *g1) * i1;
                uchar* gy = (uchar*)img->imageData + y * img->widthStep;
                uchar* gValue = gy + x1;
                if (abs(*gValue - g) > margin)
                {
                    returnValue = false;
                    break;
                }
            }
        }
        else
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    double i1 = (double)(y - y1) / (double)(y2 - y1);
                    double i2 = (double)(x - x1) / (double)(x2 - x1);
                    double g5 = *g1 + (*g2 - *g1) * i2;
                    double g6 = *g3 + (*g4 - *g3) * i2;
                    double g = g5 + (g6 - g5) * i1;
                    uchar* gy = (uchar*)img->imageData + y * img->widthStep;
                    uchar* gValue = gy + x;
                    if (abs(*gValue - g) > margin)
                    {
                        returnValue = false;
                        break;
                    }
                }
            }
        }

        return returnValue;
    }

    void StartNamCut(const IplImage* img, CvMat* markMatrix, CvMat* R, map<unsigned int, ColorNode>& color_list, map<unsigned int, Location>& block_list, int height, int width, double margin, int& num)
    {

        unsigned int* block = new unsigned int[height * width];
        for (int i = 0; i < height * width; i++)
        {
            block[i] = 0;
        }

        for (int y = 0; y < height; y++)
        {
            int x = 0;
            uchar* p_y = (uchar*)(img->imageData + y * img->widthStep);

            while (x < width)
            {
                int start_pos = x;
                while (x < width)
                {
                    x++;
                    if (!IsSameBlock(img, start_pos, y, x, y, margin))
                    {
                        break;
                    }
                }

                x--;
                if (0 == y)
                {
                    Location loc;
                    ColorNode color;

                    if (start_pos == x)
                    {
                        (R->data.ptr + R->step * y)[x] = 3;
                        block[y * width + x] = ++num;
                        loc.x1 = loc.x2 = x;
                        loc.y1 = loc.y2 = y;

                        color.kind = 3;
                        color.g1 = p_y[x];
                        color.g2 = color.g3 = color.g4 = -1;
                    }
                    else
                    {
                        (R->data.ptr + R->step * y)[start_pos] = 1;
                        (R->data.ptr + R->step * y)[x] = 2;
                        ++num;

                        for (int j = start_pos; j <= x; j++)
                        {
                            block[y * width + j] = num;
                        }

                        loc.x1 = start_pos;
                        loc.x2 = x;
                        loc.y1 = loc.y2 = y;

                        color.kind = 1;
                        color.g1 = p_y[start_pos];
                        color.g2 = p_y[x];;
                        color.g3 = color.g4 = -1;
                    }

                    block_list.insert(make_pair(num, loc));
                    color_list.insert(make_pair(num, color));
                }
                else
                {
                    int key;
                    map<unsigned int, Location>::iterator it;
                    map<unsigned int, ColorNode>::iterator c_it;
                    key = block[(y - 1) * width + start_pos];
                    it = block_list.find(key);
                    c_it = color_list.find(key);

                    if (it->second.x1 == start_pos && it->second.x2 == x && IsSameBlock(img, start_pos, it->second.y1, x, y, margin))
                    {
                        it->second.x2 = x;
                        it->second.y2 = y;


                        if (3 == (R->data.ptr + R->step * (y - 1))[x])
                        {
                            (R->data.ptr + R->step * (y - 1))[x] = 1;
                            c_it->second.g3 = ((uchar*)(img->imageData + y * img->widthStep))[start_pos];
                            c_it->second.kind = 2;
                        }
                        else
                        {
                            (R->data.ptr + R->step * (y - 1))[x] = 0;
                            c_it->second.g3 = ((uchar*)(img->imageData + y * img->widthStep))[start_pos];
                            c_it->second.g4 = ((uchar*)(img->imageData + y * img->widthStep))[x];
                            c_it->second.kind = 0;
                        }

                        (R->data.ptr + R->step * y)[x] = 2;
                    }
                    else
                    {
                        Location loc;
                        ColorNode color;

                        if (start_pos == x)
                        {
                            (R->data.ptr + R->step * y)[x] = 3;
                            loc.x1 = loc.x2 = x;
                            loc.y1 = loc.y2 = y;

                            color.kind = 3;
                            color.g1 = p_y[x];
                            color.g2 = color.g3 = color.g4 = -1;
                        }
                        else
                        {
                            (R->data.ptr + R->step * y)[start_pos] = 1;
                            (R->data.ptr + R->step * y)[x] = 2;

                            loc.x1 = start_pos;
                            loc.x2 = x;
                            loc.y1 = loc.y2 = y;

                            color.kind = 1;
                            color.g1 = p_y[start_pos];
                            color.g2 = p_y[x];;
                            color.g3 = color.g4 = -1;
                        }
                        key = ++num;
                        block_list.insert(make_pair(num, loc));
                        color_list.insert(make_pair(num, color));
                    }

                    for (int j = start_pos; j <= x; j++)
                    {
                        block[y * width + j] = key;
                    }
                }

                x++;
            }

        }

        delete[] block;

        //for(int row = 0;row < height;row++)
        //{
        //	for(int col = 0;col < width;col++)
        //	{
        //		if((markMatrix->data.ptr+row*markMatrix->step)[col] == 0)
        //		{
        //			num++;
        //			Location loc = FindSameBlock(img,markMatrix,R,col,row,margin,ratio);
        //			LocList.push_back(loc);
        //			//Mark
        //			SetMarkMatrix(markMatrix,loc.x1,loc.y1,loc.x2,loc.y2,1);
        //			//R
        //			if(loc.x1 == loc.x2 && loc.y1 == loc.y2)
        //			{
        //				uchar * g = R->data.ptr + R->step*loc.y1;
        //				g[loc.x1] = 3;
        //				ColorNode node(3,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1]);
        //				ColorList.push_back(node);
        //			}
        //			else if(loc.x1 == loc.x2)
        //			{
        //				for(int j=loc.y1;j<=loc.y2;j++)
        //				{
        //					uchar *g = R->data.ptr + R->step*j;
        //					g[loc.x1] = 0;
        //				}
        //				(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
        //				(R->data.ptr + R->step*loc.y2)[loc.x1] = 2;
        //				ColorNode node(2,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1]);
        //				ColorList.push_back(node);
        //
        //			}
        //			else
        //			{
        //				for(int i=loc.y1;i<=loc.y2;i++)
        //				{
        //					for(int j = loc.x1;j<=loc.x2;j++)
        //					{
        //						(R->data.ptr + R->step*i)[j] = 0;
        //					}
        //				}

        //				if(loc.y1 == loc.y2)
        //				{
        //					ColorNode node(1,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2]);
        //					ColorList.push_back(node);
        //				}
        //				else
        //				{
        //					ColorNode node(0,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2],
        //						((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x2]);
        //					ColorList.push_back(node);
        //				}


        //				(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
        //				(R->data.ptr + R->step*loc.y2)[loc.x2] = 2;
        //			}
        //		}
        //	}
        //}
    }

    //RestoreImage.cpp
    void RestoreImage(IplImage* img, CvMat* markMatrix, CvMat* R, map<unsigned int, ColorNode>& color_list, int height, int width)
    {
        int x1(0), x2(0), y1(0), y2(0);

        for (int i = 1; i <= color_list.size(); i++)
        {
            map<unsigned int, ColorNode>::iterator it = color_list.find(i);
            //先查找下一个未计算的分块 起点坐标
            while (x2 < width)
            {
                if ((markMatrix->data.ptr + markMatrix->step * y2)[x2++] == 0)
                    break;


                if (x2 == width)
                {
                    x1 = x2 = 0;
                    y1 = ++y2;
                }

            }

            x1 = --x2;

            //再查找出这个块的 (x1,y1) (x2,y2)
            if (0 == (it->second).kind)
            {
                while (x2 < width)
                {
                    //x2要先走一步
                    if ((R->data.ptr + R->step * y2)[++x2] != 0 || (markMatrix->data.ptr + markMatrix->step * y2)[x2] == 1)
                        break;
                }

                x2--;

                while (y2 < height)
                {
                    if ((R->data.ptr + R->step * y2)[x2] == 2 || (markMatrix->data.ptr + markMatrix->step * y2)[x2] == 1)
                        break;
                    y2++;
                }

            }
            else if (1 == (it->second).kind)
            {
                while (x2 < width)
                {
                    if ((R->data.ptr + R->step * y2)[++x2] == 2)
                        break;
                }
            }
            else if (2 == (it->second).kind)
            {
                while (y2 < height)
                {
                    if ((R->data.ptr + R->step * y2)[x2] == 2)
                        break;
                    y2++;
                }
            }

            //cout<<"("<<x1<<","<<y1<<")("<<x2<<","<<y2<<")"<<endl;
            RestoreImageValue(img, it->second, x1, y1, x2, y2);

            //Mark

            SetMarkMatrix(markMatrix, x1, y1, x2, y2, 1);


            x1 = x2;
            y2 = y1;

        }

    }

    void RestoreImageValue(IplImage* img, ColorNode node, int x1, int y1, int x2, int y2)
    {
        uchar* upPtr = (uchar*)(img->imageData + img->widthStep * y1);
        uchar* downPtr = (uchar*)(img->imageData + img->widthStep * y2);

        if (3 == node.kind)
        {
            upPtr[x1] = node.g1;
        }
        else if (1 == node.kind)
        {
            upPtr[x1] = node.g1;
            upPtr[x2] = node.g2;
            for (int x = x1 + 1; x < x2; x++)
            {
                double i2 = (double)(x - x1) / (double)(x2 - x1);
                upPtr[x] = (int)(node.g1 + (node.g2 - node.g1) * i2);

            }
        }
        else if (2 == node.kind)
        {
            upPtr[x1] = node.g1;
            downPtr[x1] = node.g2;
            for (int y = y1 + 1; y < y2; y++)
            {
                double i1 = (double)(y - y1) / (double)(y2 - y1);
                (img->imageData + img->widthStep * y)[x1] = (int)(node.g1 + (node.g2 - node.g1) * i1);

            }
        }
        else
        {
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    double i1 = (double)(y - y1) / (double)(y2 - y1);
                    double i2 = (double)(x - x1) / (double)(x2 - x1);
                    double g5 = node.g1 + (node.g2 - node.g1) * i2;
                    double g6 = node.g3 + (node.g4 - node.g3) * i2;
                    (img->imageData + img->widthStep * y)[x] = (int)(g5 + (g6 - g5) * i1);

                }
            }

            upPtr[x1] = node.g1;
            upPtr[x2] = node.g2;
            downPtr[x1] = node.g3;
            downPtr[x2] = node.g4;
        }
    }

    //PSNR.cpp
    //计算峰值信噪比（PSNR）
    double PSNR(IplImage* img, IplImage* newImg)
    {
        int yn = img->height;
        int xn = img->width;
        double sum = 0.0;
        for (int i = 0; i < yn; i++) {
            uchar* imgptr = (uchar*)img->imageData + i * img->widthStep;
            uchar* newImgptr = (uchar*)newImg->imageData + i * newImg->widthStep;
            for (int j = 0; j < xn; j++) {
                sum += pow((double)(imgptr[j] - newImgptr[j]), 2);
            }
        }
        double temp = 255.0 * 255 * xn * yn / sum;
        double PSNRValue = 10 * log(temp) / log(10.0);
        return PSNRValue;
    }

    //BPP.cpp
    //计算压缩图像的比特率（Bits Per Pixel）
    double BPP(map<unsigned int, ColorNode>& color_list, int xn, int yn, vector<char>& Q)
    {
        int a1 = 0, a2 = 0, a3 = 0;
        for (int i = 0; i < color_list.size(); i++) {
            if (color_list[i].g1 != -1 && color_list[i].g4 != -1) a1++;
            else if (color_list[i].g2 == -1 && color_list[i].g3 == -1) a3++;
            else  a2++;
        }
        double BPPValue = (Q.size() + 16 * a1 + 8 * a2 + 4.0 * a3) / (xn * yn);
        return BPPValue;
    }

    //FindSameBlock.cpp
    Location FindSameBlock(const IplImage* img, CvMat* markMatrix, CvMat* R, int x1, int y1, double margin, double ratio)
    {
        /*int x2(x1),y2(y1);

    if(x1 < img->width - 1)
    {
        x2 = x1 + 1;
        while (x2 < img->width && (markMatrix->data.ptr+y1*markMatrix->step)[x2]== 0)
        {
            if(!IsSameBlock(img,x1,y1,x2,y2,margin))
            {
                break;
            }
            x2++;
        }
        x2--;
    }
    else
    {
        x2 = img->width - 1;
    }

    if(y1 != img->height - 1)
    {
        y2 = y1 +1;

        while (y2 < img->height)
        {
            if(!IsSameBlock(img,x1,y1,x2,y2,margin))
            {
                break;
            }

            y2 = y2+1;
        }

        y2--;
    }
    else
    {
        y2 = img->height - 1;
    }

    Location loc(x1,y1,x2,y2);

    return loc;*/



        int x2(x1), y2(y1);


        while (x2 < img->width && (markMatrix->data.ptr + y1 * markMatrix->step)[x2] == 0)
        {
            if (!IsSameBlock(img, x1, y1, x2, y2, margin))
            {
                break;
            }
            x2++;
        }
        x2--;

        int maxY = ratio == 0 ? INT_MAX : (x2 - x1 + 1) * ratio;

        while (y2 < img->height && ((y2 - y1) < maxY))
        {
            if (!IsSameBlock(img, x1, y1, x2, y2, margin))
            {
                break;
            }

            y2 = y2 + 1;
        }

        y2--;


        if (ratio != 0)
        {
            if ((x2 - x1 + 1) > (y2 - y1 + 1) * ratio)
            {
                x2 = (y2 - y1 + 1) * ratio + x1 - 1;
            }
        }

        Location loc(x1, y1, x2, y2);

        return loc;
    }

    //CodeMatrix.cpp
    void EnCode(CvMat* R, int height, int width, vector<char>& Q)
    {
        int c = 0;
        int offsetValue = 0;
        int count = 0;

        for (int i = 0; i < height; i++)
        {
            c = 0;
            offsetValue = 0;
            count = 0;
            //Q.push_back(' ');
            for (int j = 0; j < width; j++)
            {
                int value = (R->data.ptr + R->step * i)[j];
                if (0 == value)
                {
                    if (j == width - 1)
                    {
                        Q.push_back('0');
                    }
                }
                else
                {
                    if (1 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('1');
                    }
                    else if (2 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('0');
                        Q.push_back('1');
                    }
                    else if (3 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('0');
                        Q.push_back('0');
                    }

                    //位置从1开始 不是从0开始 所以多减去1
                    int b = ceil(log((double)(width - c - count)) / log(2.0f));
                    if (0 == count)
                    {
                        offsetValue = j;
                    }
                    else
                    {
                        offsetValue = j - c - 1;
                    }

                    b = (b == 0) ? 1 : b;
                    count = 1;
                    c = j;

                    for (int v = b - 1; v >= 0; v--)
                    {
                        if ((offsetValue & (1 << v)) == 0)
                        {
                            Q.push_back('0');
                        }
                        else
                        {
                            Q.push_back('1');
                        }
                    }
                }
            }
        }
    }

    void Decode(CvMat* R, int height, int width, const vector<char>& Q)
    {
        int n = 0;
        int count = 0;
        //上个非零元素的位置
        int c = 0;
        int row = 0;
        int num = 0;
        for (int pos = 0; pos < Q.size(); pos++)
        {
            if ('1' == Q[pos])
            {
                pos++;
                if ('1' == Q[pos])
                {
                    n = 1;

                }
                else
                {
                    pos++;
                    if ('1' == Q[pos])
                    {
                        n = 2;
                    }
                    else
                    {
                        n = 3;
                    }
                }
            }
            else
            {
                row++;
                count = 0;
                c = 0;
                num = 0;
                continue;
                //如果是0
                //if(c == 0)
                //{
                //	row++;
                //	continue;
                //}
                //else
                //{
                //	row++;
                //	count = 0;
                //	c = 0;
                //	num = 0;
                //	continue;

                //}
            }

            int b = ceil(log((double)(width - c - count)) / log(2.0f));
            b = b == 0 ? 1 : b;
            count = 1;

            int value = 0;
            for (int i = b - 1; i >= 0; i--)
            {
                pos++;
                if ('1' == Q[pos])
                {
                    value += 1 << i;
                }
            }

            if (0 == num)
            {
                c = c + value;
            }
            else
            {
                c = c + value + 1;
            }

            num++;


            (R->data.ptr + row * R->step)[c] = n;

            if (c == (width - 1))
            {
                row++;
                count = 0;
                c = 0;
                num = 0;
            }
        }

        /*for(vector<char>::const_iterator it = Q.begin();it != Q.end();it++)
    {
        if('1' == *it)
        {
            it++;
            if('1' == *it)
            {
                n = 1;

            }
            else
            {
                it++;
                if('1' == *it)
                {
                    n = 2;
                }
                else
                {
                    n = 3;
                }
            }
        }
        else
        {
            //如果是0
            if(c == 0)
            {
                row++;
                continue;
            }
            else
            {


                row++;
                count = 0;
                c = 0;
                num = 0;
                continue;

            }
        }

        int b = ceil(log((double)(width- c -count))/log(2.0f));
        b = b==0? 1:b;
        count = 1;

        int value = 0;
        for(int i = b -1;i >=0;i--)
        {
            it++;
            if(*it == '1')
            {
                value += 1<<i;
            }
        }

        if(0 == num)
        {
            c = c + value;
        }
        else
        {
            c = c + value +1;
        }

        num++;


        (R->data.ptr + row*R->step)[c] = n;

        if( c == (width -1))
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
        }
    }*/

    }


};
//TNAM Horizonal and Diagonal
class TNAM :public structAndVariables
{
public:
    bool isSameBlock(Mat f, Mat mark, Point lt, Point rb, int xgm)
    {
        uchar g1 = f.at<uchar>(lt);
        uchar g2 = f.at<uchar>(Point(rb.x, lt.y));
        uchar g3 = f.at<uchar>(Point(lt.x, rb.y));
        uchar g4 = f.at<uchar>(rb);
        //标准矩形
        if (lt.x < rb.x && lt.y < rb.y)
        {
            int flag = 1;
            for (int j = lt.y; j <= rb.y; j++)
            {
                for (int i = lt.x; i <= rb.x; i++)
                {
                    double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                    double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                    double g5 = g1 + (g2 - g1) * i2;
                    double g6 = g3 + (g4 - g3) * i2;
                    double gest = g5 + (g6 - g5) * i1;
                    //cout << g1 << " " << g2 << " " << g3 << " " << g4 << " " << g5 << " " << g6 << " " << gest << " "<<f.at<uchar>(Point(i,j))<<endl;
                    if (abs(f.at<uchar>(Point(i, j)) - gest) > xgm || mark.at<uchar>(Point(i, j)) == 1)
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0)break;
            }
            return flag;
        }
        //宽为1的矩形
        else if (lt.x != rb.x && lt.y == rb.y)
        {
            int flag = 1;
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double gest = g1 + (g4 - g1) * i2;
                if (abs(f.at<uchar>(Point(i, lt.y)) - gest) > xgm || mark.at<uchar>(Point(i, lt.y)) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            return flag;
        }
        //长为1的矩形
        else if (lt.x == rb.x && lt.y != rb.y)
        {
            int flag = 1;
            for (int j = lt.y; j <= rb.y; j++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double gest = g1 + (g4 - g1) * i1;
                if (abs(f.at<uchar>(Point(lt.x, j)) - gest) > xgm || mark.at<uchar>(Point(lt.x, j)) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            return flag;
        }
        //孤立点矩形
        else if (lt.x == rb.x && lt.y == rb.y)
        {
            //double g1 = f.at<uchar>(lt);
            if (mark.at<uchar>(lt) == 1)return 0;
            return 1;
        }
    }

    //给灰度图f已经搜索过的矩形子模式做标记
    void mark(Mat& mark, Point lt, Point rb) {
        for (int i = lt.y; i <= rb.y; i++)
            for (int j = lt.x; j <= rb.x; j++)
                mark.at<uchar>(i, j) = 1;
    }

    void EnCode(Mat& R, int height, int width, vector<char>& Q)
    {
        int c = 0;
        int offsetValue = 0;
        int count = 0;

        for (int i = 0; i < height; i++)
        {
            c = 0;
            offsetValue = 0;
            count = 0;
            //Q.push_back(' ');
            for (int j = 0; j < width; j++)
            {
                int value = R.at<uchar>(i, j);
                if (0 == value)
                {
                    if (j == width - 1)
                    {
                        Q.push_back('0');
                    }
                }
                else
                {
                    if (1 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('1');

                    }
                    else if (2 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('0');
                        Q.push_back('1');
                    }
                    else if (3 == value)
                    {
                        Q.push_back('1');
                        Q.push_back('0');
                        Q.push_back('0');

                    }

                    //位置从1开始 不是从0开始 所以多减去1
                    int b = ceil(log((double)(width - c - count)) / log(2.0f));
                    if (0 == count)
                    {
                        offsetValue = j;
                    }
                    else
                    {
                        offsetValue = j - c - 1;
                    }

                    b = (b == 0) ? 1 : b;
                    count = 1;
                    c = j;

                    for (int v = b - 1; v >= 0; v--)
                    {
                        if ((offsetValue & (1 << v)) == 0)
                        {
                            Q.push_back('0');
                        }
                        else
                        {
                            Q.push_back('1');
                        }
                    }
                }
            }
        }
    }

    void Decode(Mat& R, int height, int width, const vector<char>& Q)
    {
        int n = 0;
        int count = 0;
        //上个非零元素的位置
        int c = 0;
        int row = 0;
        int num = 0;
        for (int pos = 0; pos < Q.size(); pos++)
        {
            if ('1' == Q[pos])
            {
                pos++;
                if ('1' == Q[pos])
                {
                    n = 1;

                }
                else
                {
                    pos++;
                    if ('1' == Q[pos])
                    {
                        n = 2;
                    }
                    else
                    {
                        n = 3;
                    }
                }
            }
            else
            {
                row++;
                count = 0;
                c = 0;
                num = 0;
                continue;
                //如果是0
                //if(c == 0)
                //{
                //	row++;
                //	continue;
                //}
                //else
                //{
                //	row++;
                //	count = 0;
                //	c = 0;
                //	num = 0;
                //	continue;

                //}
            }

            int b = ceil(log((double)(width - c - count)) / log(2.0f));
            b = b == 0 ? 1 : b;
            count = 1;

            int value = 0;
            for (int i = b - 1; i >= 0; i--)
            {
                pos++;
                if ('1' == Q[pos])
                {
                    value += 1 << i;
                }
            }

            if (0 == num)
            {
                c = c + value;
            }
            else
            {
                c = c + value + 1;
            }

            num++;


            R.at<uchar>(row, c) = n;

            if (c == (width - 1))
            {
                row++;
                count = 0;
                c = 0;
                num = 0;
            }
        }

        /*for(vector<char>::const_iterator it = Q.begin();it != Q.end();it++)
    {
        if(1 == *it)
        {
            it++;
            if(1 == *it)
            {
                n = 1;

            }
            else
            {
                it++;
                if(1 == *it)
                {
                    n = 2;
                }
                else
                {
                    n = 3;
                }
            }
        }
        else
        {
            //如果是0
            if(c == 0)
            {
                row++;
                continue;
            }
            else
            {


                row++;
                count = 0;
                c = 0;
                num = 0;
                continue;

            }
        }

        int b = ceil(log((double)(width- c -count))/log(2.0f));
        b = b==0? 1:b;
        count = 1;

        int value = 0;
        for(int i = b -1;i >=0;i--)
        {
            it++;
            if(*it == 1)
            {
                value += 1<<i;
            }
        }

        if(0 == num)
        {
            c = c + value;
        }
        else
        {
            c = c + value +1;
        }

        num++;


        (R->data.ptr + row*R->step)[c] = n;

        if( c == (width -1))
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
        }
    }*/

    }

    //寻找最大的矩形子模式
    Point REHelper_Diagonal(Mat f, Mat mark, int M, int N, Point start, int xgm) {
        Point end = start;
        Point end1, end2;
        while (end.x < M && end.y < N && (mark.at<uchar>(end) == 0) && (mark.at<uchar>(start) == 0)) {
            if (!isSameBlock(f, mark, start, end, xgm)) break;
            end.x++;
            end.y++;
        }
        end.x--;
        end.y--;

        end1 = end;
        while (end1.x < M && (mark.at<uchar>(end1) == 0)) {
            if (!isSameBlock(f, mark, start, end1, xgm)) break;
            end1.x++;
        }
        end1.x--;

        end2 = end;
        while (end2.y < N && (mark.at<uchar>(end2) == 0)) {
            if (!isSameBlock(f, mark, start, end2, xgm)) break;
            end2.y++;
        }
        end2.y--;


        if ((end2.x - start.x + 1) * (end2.y - start.y + 1) > (end1.x - start.x + 1) * (end1.y - start.y + 1))return end2;
        else return end1;

        /*Point end_second = start;
    flag1 = 0;
    flag2 = 0;
    while (flag1 == 0 || flag2 == 0) {
        end1 = end_second;
        while (flag1 == 0) {
            end1.x++;
            if (end1.x == N)flag1 = 1;
            else if (REHelper2(f, start, end1))flag1 = 1;
            else if (!isSameBlock(f, start, end1))flag1 = 1;
            if (flag1 == 1)end1.x--;
        }
        end2 = end1;
        while (flag2 == 0) {
            end2.y++;
            if (end2.y == M)flag2 = 1;
            else if (REHelper2(f, start, end2))flag2 = 1;
            else if (!isSameBlock(f, start, end2))flag2 = 1;
            if (flag2 == 1)end2.y--;
        }
        Rect rec1(start, end1), rec2(start, end2);
        if (rec1.area() < rec2.area())end_second = end2;
        else end_second = end1;
    }
    Point end_third = start;
    flag1 = 0;
    flag2 = 0;
    while (flag1 == 0 || flag2 == 0) {
        end2 = end_third;
        while (flag2 == 0) {
            end2.y++;
            if (end2.y == M)flag2 = 1;
            else if (REHelper2(f, start, end2))flag2 = 1;
            else if (!isSameBlock(f, start, end2))flag2 = 1;
            if (flag2 == 1)end2.y--;
        }
        end1 = end2;
        while (flag1 == 0) {
            end1.x++;
            if (end1.x == N)flag1 = 1;
            else if (REHelper2(f, start, end1))flag1 = 1;
            else if (!isSameBlock(f, start, end1))flag1 = 1;
            if (flag1 == 1)end1.x--;
        }
        Rect rec1(start, end1), rec2(start, end2);
        if (rec1.area() < rec2.area())end_third = end2;
        else end_third = end1;
    }
    Point end;
    if ((end_first.x-start.x+1)*(end_first.y-start.y+1)<=(end_second.x-start.x+1)*(end_second.y-start.y+1))end = end_second;
    else end = end_first;
    if ((end.x-start.x+1)*(end.y-start.y+1)<(end_third.x-start.x+1)*(end_third.y-start.y+1))end = end_third;*/
    }
    Point REHelper_Horizonal(Mat f, Mat mark, int M, int N, Point start, int xgm) {
        Point end2, end1 = end2 = start;

        while (end1.x < M && (mark.at<uchar>(end1) != 1)) {
            if (!isSameBlock(f, mark, start, end1, xgm)) break;
            end1.x++;
        }
        end1.x--;
        while (end1.y < N && (mark.at<uchar>(end1) != 1)) {
            if (!isSameBlock(f, mark, start, end1, xgm)) break;
            end1.y++;
        }
        end1.y--;

        while (end2.y < N && (mark.at<uchar>(end2) != 1)) {
            if (!isSameBlock(f, mark, start, end2, xgm)) break;
            end2.y++;
        }
        end2.y--;
        while (end2.x < M && (mark.at<uchar>(end2) != 1)) {
            if (!isSameBlock(f, mark, start, end2, xgm)) break;
            end2.x++;
        }
        end2.x--;


        if ((end2.x - start.x + 1) * (end2.y - start.y + 1) > (end1.x - start.x + 1) * (end1.y - start.y + 1))return end2;
        else return end1;
    }

    //灰度图f编码
    void RNAMCEncoding_Diagonal(Mat f, Mat& R, Mat& markMatrix, int M, int N, vector<algorithmColor>& p, vector<char>& q, int xgm) {
        Point start, end;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (markMatrix.at<uchar>(i, j) == 0)
                {
                    start = Point(j, i);
                    end = REHelper_Diagonal(f, markMatrix, M, N, start, xgm);
                    algorithmColor p1;
                    p1.setLt(start);
                    p1.setRb(end);
                    uchar g1 = f.at<uchar>(start);
                    uchar g2 = f.at<uchar>(Point(end.x, start.y));
                    uchar g3 = f.at<uchar>(Point(start.x, end.y));
                    uchar g4 = f.at<uchar>(end);
                    if (start.x < end.x && start.y < end.y)
                    {
                        p1.setGrey(Scalar(g1, g2, g3, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //宽为1的矩形
                    if (start.x != end.x && start.y == end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //长为1的矩形
                    if (start.x == end.x && start.y != end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //孤立点矩形
                    if (start.x == end.x && start.y == end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, 0));
                        R.at<uchar>(start) = 3;
                    }
                    p.push_back(p1);
                    mark(markMatrix, start, end);
                    /*for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        cout << (int)markmatrix.at<uchar>(i, j);
                    }
                    cout << endl;
                }
                cout << endl;*/
                }
            }
        /*for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << (int)R.at<uchar>(i, j);
        }
        cout << endl;
    }*/
    }
    void RNAMCEncoding_Horizonal(Mat f, Mat& R, Mat& markMatrix, int M, int N, vector<algorithmColor>& p, vector<char>& q, int xgm) {
        Point start, end;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (markMatrix.at<uchar>(i, j) == 0)
                {
                    start = Point(j, i);
                    end = REHelper_Horizonal(f, markMatrix, M, N, start, xgm);
                    algorithmColor p1;
                    p1.setLt(start);
                    p1.setRb(end);
                    uchar g1 = f.at<uchar>(start);
                    uchar g2 = f.at<uchar>(Point(end.x, start.y));
                    uchar g3 = f.at<uchar>(Point(start.x, end.y));
                    uchar g4 = f.at<uchar>(end);
                    if (start.x < end.x && start.y < end.y)
                    {
                        p1.setGrey(Scalar(g1, g2, g3, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //宽为1的矩形
                    if (start.x != end.x && start.y == end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //长为1的矩形
                    if (start.x == end.x && start.y != end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, g4));
                        R.at<uchar>(start) = 1;
                        R.at<uchar>(end) = 2;
                    }
                    //孤立点矩形
                    if (start.x == end.x && start.y == end.y)
                    {
                        p1.setGrey(Scalar(g1, 0, 0, 0));
                        R.at<uchar>(start) = 3;
                    }
                    p.push_back(p1);
                    mark(markMatrix, start, end);
                    /*for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        cout << (int)markmatrix.at<uchar>(i, j);
                    }
                    cout << endl;
                }
                cout << endl;*/
                }
            }
        /*for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << (int)R.at<uchar>(i, j);
        }
        cout << endl;
    }*/
    }

    //恢复矩形子模式的值
    void RDHelper(Mat& R, algorithmColor p1) {
        Point lt = p1.getLt();
        Point rb = p1.getRb();
        uchar g1 = p1.getGrey()[0];
        uchar g2 = p1.getGrey()[1];
        uchar g3 = p1.getGrey()[2];
        uchar g4 = p1.getGrey()[3];
        //标准矩形
        if (lt.x < rb.x && lt.y < rb.y)
        {

            for (int j = lt.y; j <= rb.y; j++)
            {
                for (int i = lt.x; i <= rb.x; i++)
                {
                    double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                    double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                    double g5 = g1 + (g2 - g1) * i2;
                    double g6 = g3 + (g4 - g3) * i2;
                    double gest = g5 + (g6 - g5) * i1;
                    R.at<uchar>(Point(i, j)) = gest;
                }
            }
        }
        //宽为1的矩形
        if (lt.x != rb.x && lt.y == rb.y)
        {
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double gest = g1 + (g4 - g1) * i2;
                R.at<uchar>(Point(i, lt.y)) = gest;
            }
        }
        //长为1的矩形
        if (lt.x == rb.x && lt.y != rb.y)
        {
            for (int j = lt.y; j <= rb.y; j++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double gest = g1 + (g4 - g1) * i1;
                R.at<uchar>(Point(lt.x, j)) = gest;
            }
        }
        //孤立点矩形
        if (lt.x == rb.x && lt.y == rb.y)
        {
            R.at<uchar>(Point(lt.x, lt.y)) = g1;
        }
    }

    //灰度图f解码
    void RNAMCDecoding(Mat& R, int M, int N, vector<algorithmColor> p, vector<char> q) {
        for (int i = 0; i < p.size(); i++)
            RDHelper(R, p[i]);
    }

    //PSNR
    double PSNR(Mat f, Mat R, int M, int N) {
        double mid = 0;;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                mid += pow(f.at<uchar>(i, j) - R.at<uchar>(i, j), 2);
            }
        return 10 * log10f(pow(255., 2) * M * N / mid);
    }

    //BPP
    double BPP(vector<algorithmColor> p, int M, int N, vector<char> q) {
        int a1 = 0, a2 = 0, a3 = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].getGrey()[0] != -1 && p[i].getGrey()[3] != -1) a1++;
            else if (p[i].getGrey()[1] == -1 && p[i].getGrey()[2] == -1) a3++;
            else  a2++;
        }
        double BPPValue = (q.size() + 16 * a1 + 8 * a2 + 4.0 * a3) / (M * N);
        return BPPValue;
    }

    void segmentDisplay(Mat& display, vector<algorithmColor> p) {
        for (int i = 0; i < p.size(); i++) {
            rectangle(display, p[i].getLt(), p[i].getRb(), Scalar(0), 1);
        }
    }

};
//---------------第三层类，包括算法的调用函数和参数---------------
class main_algorithm : public STC, public IBR, public TNAM
{
public:
    //参数表
    long compression_time;//编码时间
    long decode_time;//解码时间
    unsigned long long blocks;//块数
    double psnr_value;//psnr值
    double bpp_value;//bpp值
    double cr_value;//cr值
    long long qsc_time;//qsc处理时间
    int region_nums; //区域数量

    //Diagonal参数：分别输入1.原灰度图 2.转灰度图文件名 3.解码后的文件名 4.EPSILON
    int diag_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
    {
        if (argv1 != NULL) {
            TNAM tnamDiagonal;
            Mat img = imread(argv1);
            if (!img.empty()) {

                //namedWindow("原图灰度图像", 1);
                //imshow("原图灰度图像", img);

                /*一，分割同类块及编码*/
                int M = img.rows;
                int N = img.cols;

                Mat img_gray = img;
                cvtColor(img, img_gray, CV_BGR2GRAY);
                Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
                Mat R = Mat::zeros(M, N, CV_8UC1);

                vector<algorithmColor> colorList;
                vector<char> coordinateList;
                int xigema = atoi(argv4);


                time_t begin1,end1,begin2,end2;
                begin1 = clock();

                /*分块*/
                tnamDiagonal.RNAMCEncoding_Diagonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

                /*矩阵编码*/
                tnamDiagonal.EnCode(R, M, N, coordinateList);
                //mt.End();
                end1 = clock();


                cout << "编码压缩花费:" << end1 - begin1 << "ms" << endl;
                compression_time = end1-begin1;
                /*二，还原图像矩阵及图像*/
                Mat T = Mat::zeros(M, N, CV_8UC1);

                begin2 = clock();
                tnamDiagonal.Decode(T, M, N, coordinateList);
                tnamDiagonal.RNAMCDecoding(T, M, N, colorList, coordinateList);
                end2 = clock();

                cout << "还原图像耗时:" << end2 - begin2 << "ms" << endl;
                decode_time = end2 - begin2;

                cout << "块数:" << colorList.size() << endl;
                        blocks = colorList.size();

                cout << "PSNR值:" << tnamDiagonal.PSNR(img_gray, T, M, N) << endl;
                        psnr_value = tnamDiagonal.PSNR(img_gray, T, M, N);

                cout << "BPP值:" << tnamDiagonal.BPP(colorList, M, N, coordinateList) << endl;
                        bpp_value = tnamDiagonal.BPP(colorList, M, N, coordinateList);

                cout << "CR值:" << 8.0 / bpp_value << endl;
                        cr_value = 8.0 / bpp_value;


                //namedWindow("压缩图灰度图像", 1);
                //imshow("压缩图灰度图像", T);

                imwrite(argv2, img_gray);//输出灰度图
                imwrite(argv3, T);//输出解码后图像

                /*分割图*/
                Mat display(M, N, CV_8UC1, Scalar::all(255));
                tnamDiagonal.segmentDisplay(display, colorList);

                //namedWindow("分割图", 1);
                //imshow("分割图", display);
                imwrite("./segment.bmp",display);
                //等待
                //waitKey(2000);
                destroyAllWindows();
                img.release();
                img_gray.release();
                display.release();
                T.release();
            }
        }

        return 0;
    }

    //Horizonal参数：分别输入1.原灰度图 2.转灰度图文件名 3.解码后的文件名 4.EPSILON
    int hori_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
    {
        if (argv1 != NULL) {
            TNAM tnamHorizonal;
            Mat img = imread(argv1);
            if (!img.empty()) {

                //namedWindow("原图灰度图像", 1);
                //imshow("原图灰度图像", img);

                /*一，分割同类块及编码*/
                int M = img.rows;
                int N = img.cols;

                Mat img_gray;
                cvtColor(img, img_gray, CV_BGR2GRAY);
                Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
                Mat R = Mat::zeros(M, N, CV_8UC1);

                vector<algorithmColor> colorList;
                vector<char> coordinateList;
                int xigema = atoi(argv4);

                time_t begin1,end1,begin2,end2;
                begin1 = clock();

                /*分块*/
                tnamHorizonal.RNAMCEncoding_Horizonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

                /*矩阵编码*/
                tnamHorizonal.EnCode(R, M, N, coordinateList);
                end1 = clock();


                cout << "编码压缩花费:" << end1 - begin1 << "ms" << endl;
                compression_time = end1-begin1;

                /*二，还原图像矩阵及图像*/
                Mat T = Mat::zeros(M, N, CV_8UC1);

                begin2 = clock();
                tnamHorizonal.Decode(T, M, N, coordinateList);
                tnamHorizonal.RNAMCDecoding(T, M, N, colorList, coordinateList);
                end2 = clock();

                cout << "还原图像耗时:" << end2 - begin2 << "ms" << endl;
                decode_time = end2 - begin2;

                cout << "块数:" << colorList.size() << endl;
                        blocks = colorList.size();

                cout << "PSNR值:" << tnamHorizonal.PSNR(img_gray, T, M, N) << endl;
                        psnr_value = tnamHorizonal.PSNR(img_gray, T, M, N);

                cout << "BPP值:" << tnamHorizonal.BPP(colorList, M, N, coordinateList) << endl;
                        bpp_value = tnamHorizonal.BPP(colorList, M, N, coordinateList);

                cout << "CR值:" << 8.0 / bpp_value << endl;
                        cr_value = 8.0 / bpp_value;

                //namedWindow("压缩图灰度图像", 1);
                //imshow("压缩图灰度图像", T);
                imwrite(argv2, img_gray);//多出来的两行
                imwrite(argv3, T);//多出来的两行

                /*分割图*/
                Mat display(M, N, CV_8UC1, Scalar::all(255));
                tnamHorizonal.segmentDisplay(display, colorList);
                //namedWindow("分割图", 1);
                //imshow("分割图", display);
                imwrite("./segment.bmp",display);

                //waitKey(2000);
                destroyAllWindows();
                img.release();
                img_gray.release();
                display.release();
                T.release();
            }
        }

        return 0;
    }

    //IBR参数：分别输入1.原灰度图 2.转灰度图文件名 3.解码后的文件名 4.EPSILON
    int ibr_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
    {
        IplImage* img = NULL;

        if ((img = cvLoadImage(argv1, 0)) != 0)
        {
            IBR ibr;

            //cvNamedWindow("原图灰度图像", 1);
            //cvShowImage("原图灰度图像", img);
            /*一，分割同类块及编码*/
            int height = img->height;
            int width = img->width;

            CvMat* markMatrix = cvCreateMat(height, width, CV_8UC1);
            cvSetZero(markMatrix);
            CvMat* R = cvCreateMat(height, width, CV_8UC1);
            cvSetZero(R);

            int num = 0;
            map<unsigned int, ColorNode> color_list;
            map<unsigned int, Location> block_list;
            double margin = atof(argv4);
            time_t begin, end;
            begin = clock();
            /*分块*/
            ibr.StartNamCut(img, markMatrix, R, color_list, block_list, height, width, margin, num);

            /*矩阵编码*/
            vector<char> Q;
            ibr.EnCode(R, height, width, Q);
            end = clock();

            cout << "编码压缩花费:" << end - begin << "ms" << endl;
            compression_time = end - begin;

            /*for(int i =0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                cout<<(int)(R->data.ptr+i*R->step)[j]<<" ";
            }
            cout<<endl;
        }


        cout<<"编码共："<<Q.size()<<"位"<<endl;
        for (vector<char>::iterator it = Q.begin();it != Q.end();it++)
        {
            cout<<*it;
        }*/

            /*for (vector<ColorNode>::iterator it = colorList.begin();it != colorList.end();it++)
        {
            cout<<(*it).g1<<" "<<(*it).g2<<" "<<(*it).g3<<" "<<(*it).g4<<endl;
        }*/

            /*二，还原图像矩阵及图像*/
            CvMat* T = cvCreateMat(height, width, CV_8UC1);
            cvSetZero(T);
            begin = clock();
            ibr.Decode(T, height, width, Q);


            /*cout<<endl;
        for(int i =0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                cout<<(int)(T->data.ptr+i*T->step)[j]<<" ";
            }
            cout<<endl;
        }*/


            IplImage* newImg = cvCreateImage(cvSize(width, height), 8, 1);
            ibr.RestoreImage(newImg, markMatrix, T, color_list, height, width);
            end = clock();


            cout << "还原图像耗时:" << end - begin << "ms" << endl;
            decode_time = end - begin;

            cout << "块数:" << num << endl;
                    blocks = num;

            cout << "PSNR值:" << ibr.PSNR(img, newImg) << endl;
                    psnr_value = ibr.PSNR(img, newImg);

            cout << "BPP值:" << ibr.BPP(color_list, width, height, Q) << endl;
                    bpp_value = ibr.BPP(color_list, width, height, Q);

            cout << "CR值:" << 8.0 / ibr.BPP(color_list, width, height, Q) << endl;
                    cr_value = 8.0 / ibr.BPP(color_list, width, height, Q);
            //cvNamedWindow("压缩图灰度图像", 1);
            //cvShowImage("压缩图灰度图像", newImg);
            cvSaveImage(argv2, img, 0);
            cvSaveImage(argv3, newImg, 0);

            //画分割图
            IplImage* sketch;
            int xr, yr;
            int sketchXn, sketchYn;
            if (height >= 256 || width >= 256)
            {
                xr = 1, yr = 1, sketchXn = height, sketchYn = width;
                sketch = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
            }
            else
            {
                xr = 511 / (height - 1);
                yr = 511 / (width - 1);
                sketchXn = 512, sketchYn = 512;
                sketch = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 1);
            }

            for (int i = 0; i < sketchYn; i++)
            {
                uchar* ptrsketch = (uchar*)(sketch->imageData + i * sketch->widthStep);
                for (int j = 0; j < sketchXn; j++)
                {
                    ptrsketch[j] = 255;
                }
            }
            for (int i = 0; i < block_list.size(); i++)
            {
                if (block_list[i].x1 == 0 && block_list[i].y1 == 0)
                    cvRectangle(sketch, cvPoint(block_list[i].x1, block_list[i].y1), cvPoint(block_list[i].x2, block_list[i].y2), cvScalar(0x00, 0x00, 0x00));
                else   if (block_list[i].x1 == 0 && block_list[i].y1 != 0)
                    cvRectangle(sketch, cvPoint(block_list[i].x1, block_list[i].y1 - 1), cvPoint(block_list[i].x2, block_list[i].y2), cvScalar(0x00, 0x00, 0x00));
                else   if (block_list[i].x1 != 0 && block_list[i].y1 == 0)
                    cvRectangle(sketch, cvPoint(block_list[i].x1 - 1, block_list[i].y1), cvPoint(block_list[i].x2, block_list[i].y2), cvScalar(0x00, 0x00, 0x00));
                else   if (block_list[i].x1 != 0 && block_list[i].y1 != 0)
                    cvRectangle(sketch, cvPoint(block_list[i].x1 - 1, block_list[i].y1 - 1), cvPoint(block_list[i].x2, block_list[i].y2), cvScalar(0x00, 0x00, 0x00));
            }
            //cvShowImage("分割示意图", sketch);
            cvSaveImage("./segment.bmp",sketch);

            //cvWaitKey(2000);
            cvDestroyAllWindows();
        }

        return 0;
    }

    //STC参数：分别输入2.原彩图3.转换灰度图文件名4.转换RNAMC文件名 【5.同类快阀值 6.均值阀值 7.方差阀值 8.切法 1 水平 0垂直】
    int stc_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4,const char* argv5,const char* argv6,const char* argv7)
    {
        int nmb = 0;
        IplImage* img1;
        if ((img1 = cvLoadImage(argv1, 0)) != 0)   //将源彩色图像img转化成目标灰色图像读入
        {
            //
            STC stc;
            //
            time_t start, end, time, converge_start, converge_end, converge_time; //计时变量


            IplImage* imggest = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels); //创建同类型图像gest
            cvSetZero(imggest);

            int num = atoi(argv7);
            int M = img1->height;  //行(after)
            int N = img1->width;   //列(before)
            double epsilon = atof(argv4);


            vector<doubleCoordinate> C;//建立坐标表
            vector<colorListStandard>P;//建立颜色表
            vector<char> Q;//建立线性树表
            treeNode* root = new treeNode; //建立根结点
            stc.InitialNode(root);
            stc.thresU = atof(argv5);
            stc.thresVar = atof(argv6);

            //创建素描图像
            //IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);

            start = clock();
            cout << "building tree" << endl;
            stc.BuildTreeT(img1, root, P, C, num, epsilon, 0, 0, M - 1, N - 1);
            cout << "making  Q" << endl;
            stc.LevelOrder(Q, root);//寻找同类块，构造线性树表，颜色表,坐标表

            end = clock();
            time = end - start;
            cout << "编码所用时间:" << time << "ms" << endl;
            compression_time = time;


            start = clock();

            end = clock();

            time = end - start;

            //ofstream fout("Results.txt");
            cout << "解码所用时间:  " << time << "  ms" << endl << endl;
                    decode_time = time;
            cout << "epsilon =  " << epsilon << endl << endl;

            //fout << "epsilon =  " << epsilon << endl << endl;

            cout << "================================================" << endl << endl;

            //ofstream fout("Results.txt",ios::app);


            cout << "块数:" << P.size() << endl << endl;
                        blocks = P.size();
            //fout << "块数:" << P.size() << endl << endl;

            cout << fixed << setprecision(4) << "BPP:" << stc.BPP(P, M, N, Q) << endl << endl;
            //fout << fixed << setprecision(4) << "BPP:" << stc.BPP(P, M, N, Q) << endl << endl;
            bpp_value = stc.BPP(P, M, N, Q);
            cout << fixed << setprecision(4)  << "CR:  " << 8.0/stc.BPP ( P , M , N , Q ) << endl<<endl;
            //fout << fixed << setprecision(4)  << "CR:  " << 8.0/stc.BPP ( P , M , N , Q ) << endl<<endl;
            cr_value = 8.0/stc.BPP ( P , M , N , Q );

            converge_start = clock();
            Region** all_region = new Region * [P.size()];

            Segment* UpperLeft = new Segment;

            Segment* Upper = new Segment;

            UpperLeft->Length = M;
            UpperLeft->ActiveELink = NULL;
            UpperLeft->PreLink = NULL;
            UpperLeft->SucLink = Upper;

            Upper->Length = M;
            Upper->ActiveELink = NULL;
            Upper->PreLink = UpperLeft;
            Upper->SucLink = NULL;

            Segment* UpperRight = NULL;
            Segment* PreLowerLeft = NULL;

            num = atoi(argv7);
            stc.Region_Segm(UpperLeft, UpperRight, PreLowerLeft, 0, 0, M, N, all_region, P, C, Q, num);


            converge_end = clock();
            converge_time = converge_end - converge_start;

            cout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;
            qsc_time = converge_time;

            //fout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;

            Region** pixel_region = new Region * [M * N];

            //
            //        IplImage* seg = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
            //        for (unsigned int i = 0; i < P.size(); i++)
            //        {
            //            int x1 = C[i].x1, x2 = C[i].x2;
            //            int y1 = C[i].y1, y2 = C[i].y2;

            //            for (int y = y1; y <= y2; y++)
            //            {
            //                uchar* ptrsketch = (uchar*)(seg->imageData + y * seg->widthStep);

            //                for (int x = x1; x <= x2; x++)
            //                {
            //                    ptrsketch[x] = FindParent(all_region[i])->Mean;
            //                    pixel_region[y * N + x] = FindParent(all_region[i]);
            //                }
            //            }
            //        }

            IplImage* seg_line = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
            for (int y = 0; y < M; y++)
            {
                uchar* ptrsketch = (uchar*)(seg_line->imageData + y * seg_line->widthStep);

                for (int x = 0; x < N; x++)
                {
                    if (x == N - 1 || y == M - 1)
                    {
                        ptrsketch[x] = 0;
                        break;
                    }
                    ptrsketch[x] = (pixel_region[y * N + x] != pixel_region[y * N + x + 1] || pixel_region[y * N + x] != pixel_region[(y + 1) * N + x]) ? 0 : 255;


                }
            }
            cout<<"pooint 4"<<endl;

            // added by zyp add box begin!
            for (int y = 0; y < M; y++)
            {
                uchar* ptrsketch = (uchar*)(seg_line->imageData + y * seg_line->widthStep);

                for (int x = 0; x < N; x++)
                {
                    if ((y == 0) || (y == M - 1))
                        ptrsketch[x] = 0;
                    else if ((x == 0))
                        ptrsketch[x] = 0;
                }
            }
            // added by zyp add box end!

            //cvShowImage("区域合并示意图1", seg);
            //cvShowImage("区域合并示意图2", seg_line);
            //cvSaveImage("region_merge_1.bmp",seg);
            //cvSaveImage("region_merge_2.bmp",seg_line);
            stc.MakeImggest(imggest, P, C, all_region);

            cout << "PSNR of recontructured:  " << stc.STC_PSNR(img1, imggest) << endl << endl;
            psnr_value = stc.STC_PSNR(img1, imggest);
            //cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;
            //fout << "PSNR of recontructured:  " << STC_PSNR(img1, imggest) << endl << endl;

            //cvNamedWindow("灰度化图像", CV_WINDOW_AUTOSIZE);
            //cvShowImage("灰度化图像", img1); //显示原始灰度图像

            //cvNamedWindow("QSC区域分割后的图像", CV_WINDOW_AUTOSIZE);     //区域分割后的图像
            //cvShowImage("QSC区域分割后的图像", imggest);//载入转化后的灰度图像   //区域分割后的图像

            cvSaveImage(argv2, img1, 0);//把图像写入文件
            cvSaveImage(argv3, imggest, 0);//把图像写入文件
            //画示意图
            //cvNamedWindow("分割示意图", CV_WINDOW_AUTOSIZE);
            if (N >= 256 || M >= 256)
            {
                //创建素描图像
                IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
                for (int y = 0; y < M; y++)
                {
                    uchar* ptrsketch = (uchar*)(sketch->imageData + y * sketch->widthStep);

                    for (int x = 0; x < N; x++)
                    {
                        ptrsketch[x] = 255;
                    }
                }
                //素描图像初始化完成

                // 向原始图像中加矩形时，只需将cvRectangle和cvShowImage("分割示意图",sketch512或sketch);中的sketch或sketch512换为img1即可，共有两处修改！


                for (int i = 0; i < C.size(); i++)
                {
                    if (C[i].x1 == 0 && C[i].y1 == 0)
                        cvRectangle(img1, cvPoint(C[i].x1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 == 0 && C[i].y1 != 0)
                        cvRectangle(img1, cvPoint(C[i].x1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 != 0 && C[i].y1 == 0)
                        cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 != 0 && C[i].y1 != 0)
                        cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));

                }




                //cvShowImage("分割示意图", img1);//载入转化后的灰度图像

                //画示意图结束
            }
            else //放大图像
            {
                //创建素描图像
                IplImage* sketch512 = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 1);
                int xr = 511 / (N - 1);
                int yr = 511 / (M - 1);
                for (int y = 0; y < 512; y++)
                {
                    uchar* ptrsketch = (uchar*)(sketch512->imageData + y * sketch512->widthStep);

                    for (int x = 0; x < 512; x++)
                    {
                        ptrsketch[x] = 255;
                    }
                }
                //素描图像初始化完成
                for (int i = 0; i < C.size(); i++)
                {
                    if (C[i].x1 == 0 && C[i].y1 == 0)
                        cvRectangle(img1, cvPoint(C[i].x1 * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 == 0 && C[i].y1 != 0)
                        cvRectangle(img1, cvPoint(C[i].x1 * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 != 0 && C[i].y1 == 0)
                        cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
                    else   if (C[i].x1 != 0 && C[i].y1 != 0)
                        cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));

                }
                //cvShowImage("分割示意图", img1);//载入转化后的灰度图像
                //画示意图结束
            }

            cvSaveImage("segment.bmp", img1, 0);//把图像写入文件 , added by zyp
            //cvSaveImage("segment_and_rebuild.bmp", imggest, 0);//把图像写入文件 , added by zyp 重建后的图像

            //cvSaveImage("二元树区域合并示意图1.bmp", seg, 0);//把图像写入文件 , added by zyp  区域合并后用均值填充后的图像
            //cvSaveImage("二元树区域合并示意图2.bmp", seg_line, 0);//把图像写入文件 , added by zyp


            for (int i = 0; i < C.size(); i++)
            {
                if (C[i].x2 - C[i].x1 == 1)
                    nmb++;

            }

            //cout << "2*2块数量："<< nmb << endl;
            cout << "区域数量：  " << stc.reg_num << endl << endl;
                    region_nums = stc.reg_num;
            //fout << "区域数量：  " << stc.reg_num << endl << endl;
            //分隔符
            cout << "================================================" << endl << endl;
            //fout.close();


            //cvWaitKey(2000); //等待按键
            //        delete[] pixel_region;
            //        delete root;
            //        delete[] all_region;
            //        delete UpperLeft;
            //        delete Upper;
            //        cvReleaseImage(&seg);
            //        cvReleaseImage(&seg_line);
            //        cvDestroyAllWindows();//关闭
            pixel_region = NULL;
            root = NULL;
            all_region = NULL;
            UpperLeft = NULL;
            Upper = NULL;
            cvReleaseImage(&img1);
            cvReleaseImage(&imggest);
            cvDestroyAllWindows();//关闭

            return 0;
        }

        else

        return -1;

    }

};

#endif // MAIN_ALGORITHM_H
