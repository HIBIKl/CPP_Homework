#include "widget.h"
#include "ui_widget.h"
#include<qtmaterialtoggle.h>
#include<qtmaterialflatbutton.h>
#include<qtmaterialflatbutton_internal.h>
#include<qtmaterialcircularprogress.h>
#include<qtmaterialcircularprogress_internal.h>
#include <qtmaterialraisedbutton.h>
#include <QColor>
#include <QFileDialog>
#include <QTextEdit>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "./hzc/upload/Horizonal_Priority.cpp"
#include <./hzc/upload/Horizonal_Priority.cpp>
#include "./hzc/upload/BigHeader.h"
#include <./hzc/upload/BigHeader.h>

using namespace std;
using namespace Material;

    //--------------------------------------------//
    //需要实现的特性：
    //1.未选择参数时弹窗提醒选择参数（图片、sigma、算法等）
    //2.处理完之后弹窗提醒
    //3.QtMaterialScrollBar实现控制台实时输出处理日志
    //4.一点点彩蛋...?
    //--------------------------------------------//


//23.6.5 在ui展示了部分widget的实现效果
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Homework Test");


    //关闭恼人的特性
    ui->startCompression->setHaloVisible(false);
    //ui->uploadPic->setHaloVisible(false);
    //ui->function1->setHaloVisible(false);
    //ui->function2->setHaloVisible(false);
    //ui->function3->setHaloVisible(false);
    ui->function4->setHaloVisible(false);
    ui->selectPicture->setHaloVisible(false);

    //修改颜色
    ui->startCompression->setBackgroundColor(QColor(0,128,128));
    //ui->uploadPic->setBackgroundColor(QColor(0,128,128));
    //ui->function1->setBackgroundColor(QColor(0,128,128));
    //ui->function2->setBackgroundColor(QColor(0,128,128));
    //ui->function3->setBackgroundColor(QColor(0,128,128));
    ui->function4->setBackgroundColor(QColor(0,128,128));
    ui->selectPicture->setBackgroundColor(QColor(0,128,128));

    //修改圆角半径
    ui->startCompression->setCornerRadius(5);
    //ui->uploadPic->setCornerRadius(5);
    //ui->function1->setCornerRadius(5);
    //ui->function2->setCornerRadius(5);
    //ui->function3->setCornerRadius(5);
    //ui->function4->setCornerRadius(5);

    //其他的一些细节
    ui->selectPicture->setCursor(Qt::OpenHandCursor);
    //ui->textOutput->setFocus(Qt::ActiveWindowFocusReason);

//拨动按钮
//    QtMaterialToggle *toggle=new QtMaterialToggle(this);
//(x坐标,y坐标,长度,粗细)
//    toggle->setGeometry(30,30,100,50);
//扁平按钮
//    QtMaterialRaisedButton *btn=new QtMaterialRaisedButton(this);
//    btn->setForegroundColor(QColor(0,198,231));
//    btn->setGeometry(100,100,250,40);
//    btn->setText("I am a flat button");
//    btn->applyPreset(Material::FlatPreset);
//    //设置字体
//    QFont font;
//    font.setFamily("Consolas");
//    font.setPixelSize(25);
//    btn->setFont(font);
//加载动画
//    QtMaterialCircularProgress * circular = new QtMaterialCircularProgress(this);
//    circular->setColor(QColor::fromRgb(0,0,127));
//    circular->setGeometry(200,200,200,16);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_selectPicture_clicked()
{
    //选择单个文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    //获取应用程序的路径
    QString dlgTitle="Select a file:"; //对话框标题
    QString filter="Image(*.jpg *.png *.bmp)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    const std::string argvName = aFileName.toStdString();

    cv::Mat img = cv::imread(argvName); //路径不能有汉字
    cv::imshow("img",img);
    if (!aFileName.isEmpty())
        ui->textOutput->appendPlainText(aFileName);
}

//void Widget::on_function1_clicked() //实现弹出窗口dialog
//{

//}


//各类算法 其中H=hotizonal priority,D=diagonal, I=IBR,STC尚未加入 

void Widget::startAdjustH(char** argv)
{

	Mat img = imread(argv[1]);
	if (!img.empty()) {
		namedWindow("原图灰度图像", 1);
		imshow("原图灰度图像", img);
		/*一，分割同类块及编码*/
		int M = img.rows;
		int N = img.cols;

		Mat img_gray;
		cvtColor(img, img_gray, CV_BGR2GRAY);
		Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
		Mat R = Mat::zeros(M, N, CV_8UC1);

		vector<Color> colorList;
		vector<char> coordinateList;
		int xigema = atoi(argv[4]);
		MyTimer mt;
		mt.Start();
		/*分块*/
		RNAMCEncoding(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

		/*矩阵编码*/
		EnCode(R, M, N, coordinateList);
		mt.End();

		cout << "编码压缩花费:" << mt.costTime << "ms" << endl;
		mt.Reset();

		/*二，还原图像矩阵及图像*/
		Mat T = Mat::zeros(M, N, CV_8UC1);

		mt.Start();
		Decode(T, M, N, coordinateList);
		RNAMCDecoding(T, M, N, colorList, coordinateList);
		mt.End();
		cout << "还原图像耗时:" << mt.costTime << "ms" << endl;
		mt.Reset();

		cout << "块数:" << colorList.size() << endl;
		cout << "PSNR值:" << PSNR(img_gray, T, M, N) << endl;
		double BPPValue = BPP(colorList, M, N, coordinateList);
		cout << "BPP值:" << BPPValue << endl;
		cout << "CR值:" << 8.0 / BPPValue << endl;

		namedWindow("压缩图灰度图像", 1);
		imshow("压缩图灰度图像", T);
		imwrite(argv[2], img_gray);
		imwrite(argv[3], T);

		/*分割图*/
		Mat display(M, N, CV_8UC1, Scalar::all(255));
		segmentDisplay(display, colorList);
		namedWindow("分割图", 1);
		imshow("分割图", display);


		//释放空间
		waitKey(0);
		destroyAllWindows();
		img.release();
		img_gray.release();
		display.release();
		T.release();
	}



}

void Widget::startAdjustD(char** argv)
{
	Mat img = imread(argv[1]);
	if (!img.empty()) {
		namedWindow("原图灰度图像", 1);
		imshow("原图灰度图像", img);
		/*一，分割同类块及编码*/
		int M = img.rows;
		int N = img.cols;

		Mat img_gray = img;
		cvtColor(img, img_gray, CV_BGR2GRAY);
		Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
		Mat R = Mat::zeros(M, N, CV_8UC1);

        vector<Color> colorList;
		vector<char> coordinateList;
		int xigema = atoi(argv[4]);
		MyTimer mt;
		mt.Start();
		/*分块*/
        RNAMCEncoding(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

		/*矩阵编码*/
		EnCode(R, M, N, coordinateList);
		mt.End();

		cout << "编码压缩花费:" << mt.costTime << "ms" << endl;
		mt.Reset();

		/*二，还原图像矩阵及图像*/
		Mat T = Mat::zeros(M, N, CV_8UC1);

		mt.Start();
		Decode(T, M, N, coordinateList);
		RNAMCDecoding(T, M, N, colorList, coordinateList);
		mt.End();
		cout << "还原图像耗时:" << mt.costTime << "ms" << endl;
		mt.Reset();

		cout << "块数:" << colorList.size() << endl;
		cout << "PSNR值:" << PSNR(img_gray, T, M, N) << endl;
		double BPPValue = BPP(colorList, M, N, coordinateList);
		cout << "BPP值:" << BPPValue << endl;
		cout << "CR值:" << 8.0 / BPPValue << endl;

		namedWindow("压缩图灰度图像", 1);
		imshow("压缩图灰度图像", T);

		/*分割图*/
		Mat display(M, N, CV_8UC1, Scalar::all(255));
		segmentDisplay(display, colorList);
		namedWindow("分割图", 1);
		imshow("分割图", display);

		waitKey(0);
		destroyAllWindows();
		img.release();
		img_gray.release();
		display.release();
		T.release();
	}
}

void Widget::startAdjustI(char** argv)
{
	IplImage* img = NULL;



	cvNamedWindow("原图灰度图像", 1);
	cvShowImage("原图灰度图像", img);
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
	double margin = atof(argv[4]);
	time_t begin, end;
	begin = clock();
	/*分块*/
	StartNamCut(img, markMatrix, R, color_list, block_list, height, width, margin, num);

	/*矩阵编码*/
	vector<char> Q;
	EnCode(R, height, width, Q);
	end = clock();

	cout << "编码压缩花费:" << end - begin << "ms" << endl;

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
	Decode(T, height, width, Q);


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
	RestoreImage(newImg, markMatrix, T, color_list, height, width);
	end = clock();


	cout << "还原图像耗时:" << end - begin << "ms" << endl;


	cout << "块数:" << num << endl;
	cout << "PSNR值:" << PSNR(img, newImg) << endl;
	double BPPValue = BPP(color_list, width, height, Q);
	cout << "BPP值:" << BPPValue << endl;
	cout << "CR值:" << 8.0 / BPPValue << endl;

	cvNamedWindow("压缩图灰度图像", 1);
	cvShowImage("压缩图灰度图像", newImg);
	cvSaveImage(argv[2], img, 0);
	cvSaveImage(argv[3], newImg, 0);

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

		cvShowImage("分割示意图", sketch);

		cvWaitKey();
		cvDestroyAllWindows();
	}
}

//void picture::startAdjustS(char** argv)
//{
//	/*int*/ reg_num = 0;
//	/*int*/ bitnum = 0;
//	/*double*/ thresU = 0;
//	/*double*/ thresVar = 0;
//	/*int*/ cur_block = -1;
//	int nmb = 0;
//	IplImage* img1;
//	//	 cout << "img readed" << endl;
//	  /*int sum=0;
//	  for (int row=0;row<img1->height;row++)
//	  {
//	  uchar* p=(uchar*) (img1->imageData+row*img1->widthStep);
//	  for (int col=0;col<img1->width;col++)
//	  {
//
//		  sum+=*p;
//		  printf("%3d ", *p++);
//
//		}
//		printf("\n\n");
//	   }
//		printf("\n%d\n",sum);*/
//
//		//// added by zyp begin
//	   //cout << "Display the data matrix of the source image:" << endl;
//		//for(int y = 0;y<img1->height;y++)
//	 //  {
//		   //	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);
//
//		   //	for (int x = 0;x<img1->width;x++)
//		   //	{
//		   //		printf ("%5d",*ptr++);
//		   //	}
//	 //          printf("\n\n");
//	 //  }
//		//// added by zyp end
//
//
//
//
//	time_t start, end, time, converge_start, converge_end, converge_time; //计时变量
//
//
//	IplImage* imggest = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels); //创建同类型图像gest
//	cvSetZero(imggest);
//
//	int num = atoi(argv[7]);
//	int M = img1->height;  //行(after)
//	int N = img1->width;   //列(before)
//	double epsilon = atof(argv[4]);
//
//
//	vector<doubleCoordinate> C;//建立坐标表
//	vector<colorListStandard>P;//建立颜色表
//	vector<char> Q;//建立线性树表
//	treeNode* root = new treeNode; //建立根结点
//	InitialNode(root);
//	thresU = atof(argv[5]);
//	thresVar = atof(argv[6]);
//	//创建素描图像
//	IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
//	/* for(int y = 0;y<M;y++)
//	  {
//		  uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);
//
//			  for (int x = 0;x<N;x++)
//			  {
//			   ptrsketch[x]=255;
//			  }
//	   }*/
//	   //素描图像初始化完成
//
//	start = clock();
//	cout << "building tree" << endl;
//	BuildTreeT(img1, root, P, C, num, epsilon, 0, 0, M - 1, N - 1);
//	cout << "making  Q" << endl;
//	LevelOrder(Q, root);//寻找同类块，构造线性树表，颜色表,坐标表
//
//	end = clock();
//	time = end - start;
//	cout << "编码所用时间:" << time << "ms" << endl;
//
//
//
//	start = clock();
//
//	end = clock();
//
//	time = end - start;
//
//	ofstream fout("Results.txt");
//	cout << "解码所用时间:  " << time << "  ms" << endl << endl;
//
//	cout << "epsilon =  " << epsilon << endl << endl;
//	fout << "epsilon =  " << epsilon << endl << endl;
//
//	cout << "================================================" << endl << endl;
//
//	//ofstream fout("Results.txt",ios::app);
//
//
//	cout << "块数:  " << P.size() << endl << endl;
//
//	fout << "块数:  " << P.size() << endl << endl;
//
//	cout << fixed << setprecision(4) << "BPP:" << BPP(P, M, N, Q) << endl << endl;
//	fout << fixed << setprecision(4) << "BPP:  " << BPP(P, M, N, Q) << endl << endl;
//
//	//cout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	
//	//fout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	
//
//
//
//
//
//
//
//	converge_start = clock();
//	Region** all_region = new Region * [P.size()];
//
//
//	Segment* UpperLeft = new Segment;
//
//	Segment* Upper = new Segment;
//
//	UpperLeft->Length = M;
//	UpperLeft->ActiveELink = NULL;
//	UpperLeft->PreLink = NULL;
//	UpperLeft->SucLink = Upper;
//
//	Upper->Length = M;
//	Upper->ActiveELink = NULL;
//	Upper->PreLink = UpperLeft;
//	Upper->SucLink = NULL;
//
//	Segment* UpperRight = NULL;
//	Segment* PreLowerLeft = NULL;
//
//	num = atoi(argv[7]);
//	Region_Segm(UpperLeft, UpperRight, PreLowerLeft, 0, 0, M, N, all_region, P, C, Q, num);
//
//
//	converge_end = clock();
//	converge_time = converge_end - converge_start;
//	cout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;
//
//	fout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;
//
//	Region** pixel_region = new Region * [M * N];
//
//
//	IplImage* seg = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
//	for (unsigned int i = 0; i < P.size(); i++)
//	{
//		int x1 = C[i].x1, x2 = C[i].x2;
//		int y1 = C[i].y1, y2 = C[i].y2;
//
//		for (int y = y1; y <= y2; y++)
//		{
//			uchar* ptrsketch = (uchar*)(seg->imageData + y * seg->widthStep);
//
//			for (int x = x1; x <= x2; x++)
//			{
//				ptrsketch[x] = FindParent(all_region[i])->Mean;
//				pixel_region[y * N + x] = FindParent(all_region[i]);
//			}
//		}
//	}
//
//
//	IplImage* seg_line = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
//	for (int y = 0; y < M; y++)
//	{
//		uchar* ptrsketch = (uchar*)(seg_line->imageData + y * seg_line->widthStep);
//
//		for (int x = 0; x < N; x++)
//		{
//			if (x == N - 1 || y == M - 1)
//			{
//				ptrsketch[x] = 0;
//				break;
//			}
//			ptrsketch[x] = (pixel_region[y * N + x] != pixel_region[y * N + x + 1] || pixel_region[y * N + x] != pixel_region[(y + 1) * N + x]) ? 0 : 255;
//
//
//		}
//	}
//
//
//	// added by zyp add box begin!
//	for (int y = 0; y < M; y++)
//	{
//		uchar* ptrsketch = (uchar*)(seg_line->imageData + y * seg_line->widthStep);
//
//		for (int x = 0; x < N; x++)
//		{
//			if ((y == 0) || (y == M - 1))
//				ptrsketch[x] = 0;
//			else if ((x == 0))
//				ptrsketch[x] = 0;
//		}
//	}
//	// added by zyp add box end!
//
//	cvShowImage("区域合并示意图1", seg);
//	cvShowImage("区域合并示意图2", seg_line);
//
//	MakeImggest(imggest, P, C, all_region);
//
//	cout << "PSNR of recontructured:  " << PSNR(img1, imggest) << endl << endl;
//	//cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;	
//	fout << "PSNR of recontructured:  " << PSNR(img1, imggest) << endl << endl;
//
//	cvNamedWindow("灰度化图像", CV_WINDOW_AUTOSIZE);
//	cvShowImage("灰度化图像", img1); //显示原始灰度图像
//	cvNamedWindow("QSC区域分割后的图像", CV_WINDOW_AUTOSIZE);     //区域分割后的图像
//	cvShowImage("QSC区域分割后的图像", imggest);//载入转化后的灰度图像   //区域分割后的图像
//
//	cvSaveImage(argv[2], img1, 0);//把图像写入文件
//	cvSaveImage(argv[3], imggest, 0);//把图像写入文件
//	//画示意图
//	cvNamedWindow("分割示意图", CV_WINDOW_AUTOSIZE);
//	if (N >= 256 || M >= 256)
//	{
//		//创建素描图像
//		IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
//		for (int y = 0; y < M; y++)
//		{
//			uchar* ptrsketch = (uchar*)(sketch->imageData + y * sketch->widthStep);
//
//			for (int x = 0; x < N; x++)
//			{
//				ptrsketch[x] = 255;
//			}
//		}
//		//素描图像初始化完成
//
//		 // 向原始图像中加矩形时，只需将cvRectangle和cvShowImage("分割示意图",sketch512或sketch);中的sketch或sketch512换为img1即可，共有两处修改！
//
//
//		for (int i = 0; i < C.size(); i++)
//		{
//			if (C[i].x1 == 0 && C[i].y1 == 0)
//				cvRectangle(img1, cvPoint(C[i].x1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 == 0 && C[i].y1 != 0)
//				cvRectangle(img1, cvPoint(C[i].x1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 != 0 && C[i].y1 == 0)
//				cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 != 0 && C[i].y1 != 0)
//				cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
//
//		}
//
//
//
//
//		cvShowImage("分割示意图", img1);//载入转化后的灰度图像 
//
//		//画示意图结束
//	}
//	else //放大图像
//	{
//		//创建素描图像
//		IplImage* sketch512 = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 1);
//		int xr = 511 / (N - 1);
//		int yr = 511 / (M - 1);
//		for (int y = 0; y < 512; y++)
//		{
//			uchar* ptrsketch = (uchar*)(sketch512->imageData + y * sketch512->widthStep);
//
//			for (int x = 0; x < 512; x++)
//			{
//				ptrsketch[x] = 255;
//			}
//		}
//		//素描图像初始化完成
//		for (int i = 0; i < C.size(); i++)
//		{
//			if (C[i].x1 == 0 && C[i].y1 == 0)
//				cvRectangle(img1, cvPoint(C[i].x1 * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 == 0 && C[i].y1 != 0)
//				cvRectangle(img1, cvPoint(C[i].x1 * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 != 0 && C[i].y1 == 0)
//				cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
//			else   if (C[i].x1 != 0 && C[i].y1 != 0)
//				cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
//
//		}
//		cvShowImage("分割示意图", img1);//载入转化后的灰度图像 
//		//画示意图结束
//	}
//
//	cvSaveImage("二元树分割示意图.bmp", img1, 0);//把图像写入文件 , added by zyp
//	cvSaveImage("二元树区域分割后的图像.bmp", imggest, 0);//把图像写入文件 , added by zyp 重建后的图像
//
//	cvSaveImage("二元树区域合并示意图1.bmp", seg, 0);//把图像写入文件 , added by zyp  区域合并后用均值填充后的图像
//	cvSaveImage("二元树区域合并示意图2.bmp", seg_line, 0);//把图像写入文件 , added by zyp
//
//
//	//// added by zyp begin
//   //cout << "Display the data matrix of the 二元树分割示意图.bmp:" << endl;
//	//for(int y = 0;y<img1->height;y++)
// //  {
//	   //	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);
//
//	   //	for (int x = 0;x<img1->width;x++)
//	   //	{
//	   //		printf ("%5d",*ptr++);
//	   //	}
// //          printf("\n\n");
// //  }
//	//// added by zyp end
//
//
//	//// added by zyp begin
//   //cout << "Display the data matrix of the 二元树区域分割后的图像.bmp:" << endl;
//	//for(int y = 0;y<imggest->height;y++)
// //  {
//	   //	uchar* ptr = (uchar*) (imggest->imageData+y*imggest->widthStep);
//
//	   //	for (int x = 0;x<imggest->width;x++)
//	   //	{
//	   //		printf ("%5d",*ptr++);
//	   //	}
// //          printf("\n\n");
// //  }
//	//// added by zyp end
//
//
//	//// added by zyp begin
//   //cout << "Display the data matrix of the 二元树区域合并示意图1.bmp:" << endl;
//	//for(int y = 0;y<seg->height;y++)
// //  {
//	   //	uchar* ptr = (uchar*) (seg->imageData+y*seg->widthStep);
//
//	   //	for (int x = 0;x<seg->width;x++)
//	   //	{
//	   //		printf ("%5d",*ptr++);
//	   //	}
// //          printf("\n\n");
// //  }
//	//// added by zyp end
//
//
//	//// added by zyp begin
//   //cout << "Display the data matrix of the 二元树区域合并示意图2.bmp:" << endl;
//	//for(int y = 0;y<seg_line->height;y++)
// //  {
//	   //	uchar* ptr = (uchar*) (seg_line->imageData+y*seg_line->widthStep);
//
//	   //	for (int x = 0;x<seg_line->width;x++)
//	   //	{
//	   //		printf ("%5d",*ptr++);
//	   //	}
// //          printf("\n\n");
// //  }
//	//// added by zyp end
//
//
//	for (int i = 0; i < C.size(); i++)
//	{
//		if (C[i].x2 - C[i].x1 == 1)
//			nmb++;
//
//	}
//
//	//cout << "2*2块数量："<< nmb << endl;
//	cout << "区域数量：  " << reg_num << endl << endl;
//
//	fout << "区域数量：  " << reg_num << endl << endl;
//	fout.close();
//
//
//	cvWaitKey(0); //等待按键
//
//
//	cvReleaseImage(&img1);
//	cvReleaseImage(&imggest);
//	cvDestroyAllWindows();//关闭
//
//	char zyp;
//	cin >> zyp;
//}
