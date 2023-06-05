#include "Header.h"
#include "picture.h"


picture::picture(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	btn1 = new QPushButton;
	btn1->setText("点击就送屠龙宝刀");
	btn1->show();
	btn2 = new QPushButton;
	btn2->setText("一刀999");
	btn2->show();
}

picture::~picture()
{}

void picture::sigClicked()
{
	
}
//Mat picture::importPic()
//{
//	Mat rawPic;
//	Mat scr = imread("D:/lovely pic/6489669122.jpg");
//	return rawPic;
//}

void picture::startAdjust(int argc, char** argv)
{
	if (argc == 5) {
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

			waitKey(0);
			destroyAllWindows();
			img.release();
			img_gray.release();
			display.release();
			T.release();
		}
	}


}
