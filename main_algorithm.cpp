#include "Diag_and_Hori.h"
#include "IBR.h"
#include "STC.h"

//�������ݣ� .\Total.exe .\lena512.bmp 1.bmp 2.bmp

//Diagonal�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int diag_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
    if (argv1 != NULL) {
        Mat img = imread(argv1);
        if (!img.empty()) {
            namedWindow("ԭͼ�Ҷ�ͼ��", 1);
            imshow("ԭͼ�Ҷ�ͼ��", img);
            /*һ���ָ�ͬ��鼰����*/
            int M = img.rows;
            int N = img.cols;

            Mat img_gray = img;
            cvtColor(img, img_gray, CV_BGR2GRAY);
            Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
            Mat R = Mat::zeros(M, N, CV_8UC1);

            vector<algorithmColor> colorList;
            vector<char> coordinateList;
            int xigema = atoi(argv4);

            //MyTimer mt;
            //mt.Start();

            time_t begin1,end1,begin2,end2;
            begin1 = clock();

            /*�ֿ�*/
            RNAMCEncoding_Diagonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

            /*�������*/
            EnCode(R, M, N, coordinateList);
            //mt.End();
            end1 = clock();

            //cout << "����ѹ������:" << mt.costTime << "ms" << endl;
            //mt.Reset();

            cout << "����ѹ������:" << end1 - begin1 << "ms" << endl;

            /*������ԭͼ�����ͼ��*/
            Mat T = Mat::zeros(M, N, CV_8UC1);

            //mt.Start();
            begin2 = clock();
            Decode(T, M, N, coordinateList);
            RNAMCDecoding(T, M, N, colorList, coordinateList);
            //mt.End();
            end2 = clock();
            //cout << "��ԭͼ���ʱ:" << mt.costTime << "ms" << endl;
            //mt.Reset();
            cout << "��ԭͼ���ʱ:" << end2 - begin2 << "ms" << endl;

            cout << "����:" << colorList.size() << endl;
            cout << "PSNRֵ:" << PSNR(img_gray, T, M, N) << endl;
            double BPPValue = BPP(colorList, M, N, coordinateList);
            cout << "BPPֵ:" << BPPValue << endl;
            cout << "CRֵ:" << 8.0 / BPPValue << endl;

            namedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
            imshow("ѹ��ͼ�Ҷ�ͼ��", T);

            imwrite(argv2, img_gray);//�����������,����ļ�
            imwrite(argv3, T);//�����������

            /*�ָ�ͼ*/
            Mat display(M, N, CV_8UC1, Scalar::all(255));
            segmentDisplay(display, colorList);
            namedWindow("�ָ�ͼ", 1);
            imshow("�ָ�ͼ", display);

            waitKey(2000);
            destroyAllWindows();
            img.release();
            img_gray.release();
            display.release();
            T.release();
        }
    }

    return 0;
}

//Horizonal�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int hori_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
    if (argv1 != NULL) {
        Mat img = imread(argv1);
		if (!img.empty()) {
			namedWindow("ԭͼ�Ҷ�ͼ��", 1);
			imshow("ԭͼ�Ҷ�ͼ��", img);
			/*һ���ָ�ͬ��鼰����*/
			int M = img.rows;
			int N = img.cols;

			Mat img_gray;
			cvtColor(img, img_gray, CV_BGR2GRAY);
			Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
			Mat R = Mat::zeros(M, N, CV_8UC1);

            vector<algorithmColor> colorList;
			vector<char> coordinateList;
            int xigema = atoi(argv4);

            //ɾ��Windows.h�����ACCESS_MASK��ͻ
            //MyTimer mt;
            //mt.Start();

            //���ļ�ʱ�����Խ����ͻ
            time_t begin1,end1,begin2,end2;
            begin1 = clock();

			/*�ֿ�*/
			RNAMCEncoding_Horizonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

			/*�������*/
			EnCode(R, M, N, coordinateList);
            //mt.End();
            end1 = clock();

            //cout << "����ѹ������:" << mt.costTime << "ms" << endl;
            cout << "����ѹ������:" << end1 - begin1 << "ms" << endl;
            //mt.Reset();

			/*������ԭͼ�����ͼ��*/
			Mat T = Mat::zeros(M, N, CV_8UC1);

            //mt.Start();
            begin2 = clock();
			Decode(T, M, N, coordinateList);
			RNAMCDecoding(T, M, N, colorList, coordinateList);
            end2 = clock();
            //mt.End();
            //cout << "��ԭͼ���ʱ:" << mt.costTime << "ms" << endl;
            cout << "��ԭͼ���ʱ:" << end2 - begin2 << "ms" << endl;
            //mt.Reset();

			cout << "����:" << colorList.size() << endl;
			cout << "PSNRֵ:" << PSNR(img_gray, T, M, N) << endl;
			double BPPValue = BPP(colorList, M, N, coordinateList);
			cout << "BPPֵ:" << BPPValue << endl;
			cout << "CRֵ:" << 8.0 / BPPValue << endl;

			namedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
			imshow("ѹ��ͼ�Ҷ�ͼ��", T);
            imwrite(argv2, img_gray);//�����������
            imwrite(argv3, T);//�����������

			/*�ָ�ͼ*/
			Mat display(M, N, CV_8UC1, Scalar::all(255));
			segmentDisplay(display, colorList);
			namedWindow("�ָ�ͼ", 1);
			imshow("�ָ�ͼ", display);

            waitKey(2000);
			destroyAllWindows();
			img.release();
			img_gray.release();
			display.release();
			T.release();
		}
	}

	return 0;
}

//IBR�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int ibr_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
	IplImage* img = NULL;

    if ((img = cvLoadImage(argv1, 0)) != 0)
	{

		cvNamedWindow("ԭͼ�Ҷ�ͼ��", 1);
		cvShowImage("ԭͼ�Ҷ�ͼ��", img);
		/*һ���ָ�ͬ��鼰����*/
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
		/*�ֿ�*/
		StartNamCut(img, markMatrix, R, color_list, block_list, height, width, margin, num);

		/*�������*/
		vector<char> Q;
		EnCode(R, height, width, Q);
		end = clock();

		cout << "����ѹ������:" << end - begin << "ms" << endl;

		/*for(int i =0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				cout<<(int)(R->data.ptr+i*R->step)[j]<<" ";
			}
			cout<<endl;
		}


		cout<<"���빲��"<<Q.size()<<"λ"<<endl;
		for (vector<char>::iterator it = Q.begin();it != Q.end();it++)
		{
			cout<<*it;
		}*/

		/*for (vector<ColorNode>::iterator it = colorList.begin();it != colorList.end();it++)
		{
			cout<<(*it).g1<<" "<<(*it).g2<<" "<<(*it).g3<<" "<<(*it).g4<<endl;
		}*/

		/*������ԭͼ�����ͼ��*/
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


		cout << "��ԭͼ���ʱ:" << end - begin << "ms" << endl;


		cout << "����:" << num << endl;
		cout << "PSNRֵ:" << PSNR(img, newImg) << endl;
		double BPPValue = BPP(color_list, width, height, Q);
		cout << "BPPֵ:" << BPPValue << endl;
		cout << "CRֵ:" << 8.0 / BPPValue << endl;

		cvNamedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
		cvShowImage("ѹ��ͼ�Ҷ�ͼ��", newImg);
        cvSaveImage(argv2, img, 0);
        cvSaveImage(argv3, newImg, 0);

		//���ָ�ͼ
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
		cvShowImage("�ָ�ʾ��ͼ", sketch);

        cvWaitKey(2000);
		cvDestroyAllWindows();
	}

	return 0;
}

//STC�������ֱ�����2.ԭ��ͼ3.ת���Ҷ�ͼ�ļ���4.ת��RNAMC�ļ��� ��5.ͬ��췧ֵ 6.��ֵ��ֵ 7.���ֵ 8.�з� 1 ˮƽ 0��ֱ��
int stc_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4,const char* argv5,const char* argv6,const char* argv7)
{
    int nmb = 0;
	IplImage* img1;
	//cout << "start" << endl;
    if ((img1 = cvLoadImage(argv1, 0)) != 0)   //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
		//	if(( img1 = cvLoadImage("cameraman.tif", 0)) != 0)
	{
		//	 cout << "img readed" << endl;
		  /*int sum=0;
		  for (int row=0;row<img1->height;row++)
		  {
		  uchar* p=(uchar*) (img1->imageData+row*img1->widthStep);
		  for (int col=0;col<img1->width;col++)
		  {

			  sum+=*p;
			  printf("%3d ", *p++);

			}
			printf("\n\n");
		   }
			printf("\n%d\n",sum);*/

			//// added by zyp begin
		   //cout << "Display the data matrix of the source image:" << endl;
			//for(int y = 0;y<img1->height;y++)
		 //  {
			   //	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);

			   //	for (int x = 0;x<img1->width;x++)
			   //	{
			   //		printf ("%5d",*ptr++);
			   //	}
		 //          printf("\n\n");
		 //  }
			//// added by zyp end




		time_t start, end, time, converge_start, converge_end, converge_time; //��ʱ����


		IplImage* imggest = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels); //����ͬ����ͼ��gest
		cvSetZero(imggest);

        int num = atoi(argv7);
		int M = img1->height;  //��(after)
		int N = img1->width;   //��(before)
        double epsilon = atof(argv4);


		vector<doubleCoordinate> C;//���������
		vector<colorListStandard>P;//������ɫ��
		vector<char> Q;//������������
		treeNode* root = new treeNode; //���������
		InitialNode(root);
        thresU = atof(argv5);
        thresVar = atof(argv6);
		//��������ͼ��
		IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
		/* for(int y = 0;y<M;y++)
		  {
			  uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

				  for (int x = 0;x<N;x++)
				  {
				   ptrsketch[x]=255;
				  }
		   }*/
		   //����ͼ���ʼ�����

		start = clock();
		cout << "building tree" << endl;
		BuildTreeT(img1, root, P, C, num, epsilon, 0, 0, M - 1, N - 1);
		cout << "making  Q" << endl;
		LevelOrder(Q, root);//Ѱ��ͬ��飬��������������ɫ��,�����

		end = clock();
		time = end - start;
		cout << "��������ʱ��:" << time << "ms" << endl;



		start = clock();

		end = clock();

		time = end - start;

		ofstream fout("Results.txt");
        cout << "��������ʱ��:  " << time << "  ms" << endl << endl;

		cout << "epsilon =  " << epsilon << endl << endl;
		fout << "epsilon =  " << epsilon << endl << endl;

		cout << "================================================" << endl << endl;

		//ofstream fout("Results.txt",ios::app);


		cout << "����:  " << P.size() << endl << endl;

		fout << "����:  " << P.size() << endl << endl;

		cout << fixed << setprecision(4) << "BPP:" << BPP(P, M, N, Q) << endl << endl;
		fout << fixed << setprecision(4) << "BPP:  " << BPP(P, M, N, Q) << endl << endl;

		//cout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	
		//fout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	







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
		Region_Segm(UpperLeft, UpperRight, PreLowerLeft, 0, 0, M, N, all_region, P, C, Q, num);


		converge_end = clock();
		converge_time = converge_end - converge_start;
		cout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;

		fout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;

		Region** pixel_region = new Region * [M * N];


		IplImage* seg = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
		for (unsigned int i = 0; i < P.size(); i++)
		{
			int x1 = C[i].x1, x2 = C[i].x2;
			int y1 = C[i].y1, y2 = C[i].y2;

			for (int y = y1; y <= y2; y++)
			{
				uchar* ptrsketch = (uchar*)(seg->imageData + y * seg->widthStep);

				for (int x = x1; x <= x2; x++)
				{
					ptrsketch[x] = FindParent(all_region[i])->Mean;
					pixel_region[y * N + x] = FindParent(all_region[i]);
				}
			}
		}


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

		cvShowImage("����ϲ�ʾ��ͼ1", seg);
		cvShowImage("����ϲ�ʾ��ͼ2", seg_line);

		MakeImggest(imggest, P, C, all_region);

		cout << "PSNR of recontructured:  " << STC_PSNR(img1, imggest) << endl << endl;
		//cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;	
		fout << "PSNR of recontructured:  " << STC_PSNR(img1, imggest) << endl << endl;

		cvNamedWindow("�ҶȻ�ͼ��", CV_WINDOW_AUTOSIZE);
		cvShowImage("�ҶȻ�ͼ��", img1); //��ʾԭʼ�Ҷ�ͼ��
		cvNamedWindow("QSC����ָ���ͼ��", CV_WINDOW_AUTOSIZE);     //����ָ���ͼ��
		cvShowImage("QSC����ָ���ͼ��", imggest);//����ת����ĻҶ�ͼ��   //����ָ���ͼ��

        cvSaveImage(argv2, img1, 0);//��ͼ��д���ļ�
        cvSaveImage(argv3, imggest, 0);//��ͼ��д���ļ�
		//��ʾ��ͼ
		cvNamedWindow("�ָ�ʾ��ͼ", CV_WINDOW_AUTOSIZE);
		if (N >= 256 || M >= 256)
		{
			//��������ͼ��
			IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
			for (int y = 0; y < M; y++)
			{
				uchar* ptrsketch = (uchar*)(sketch->imageData + y * sketch->widthStep);

				for (int x = 0; x < N; x++)
				{
					ptrsketch[x] = 255;
				}
			}
			//����ͼ���ʼ�����

			 // ��ԭʼͼ���мӾ���ʱ��ֻ�轫cvRectangle��cvShowImage("�ָ�ʾ��ͼ",sketch512��sketch);�е�sketch��sketch512��Ϊimg1���ɣ����������޸ģ�


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




			cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ�� 

			//��ʾ��ͼ����
		}
		else //�Ŵ�ͼ��
		{
			//��������ͼ��
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
			//����ͼ���ʼ�����
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
			cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ�� 
			//��ʾ��ͼ����
		}

		cvSaveImage("��Ԫ���ָ�ʾ��ͼ.bmp", img1, 0);//��ͼ��д���ļ� , added by zyp
		cvSaveImage("��Ԫ������ָ���ͼ��.bmp", imggest, 0);//��ͼ��д���ļ� , added by zyp �ؽ����ͼ��

		cvSaveImage("��Ԫ������ϲ�ʾ��ͼ1.bmp", seg, 0);//��ͼ��д���ļ� , added by zyp  ����ϲ����þ�ֵ�����ͼ��
		cvSaveImage("��Ԫ������ϲ�ʾ��ͼ2.bmp", seg_line, 0);//��ͼ��д���ļ� , added by zyp


		//// added by zyp begin
	   //cout << "Display the data matrix of the ��Ԫ���ָ�ʾ��ͼ.bmp:" << endl;
		//for(int y = 0;y<img1->height;y++)
	 //  {
		   //	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);

		   //	for (int x = 0;x<img1->width;x++)
		   //	{
		   //		printf ("%5d",*ptr++);
		   //	}
	 //          printf("\n\n");
	 //  }
		//// added by zyp end


		//// added by zyp begin
	   //cout << "Display the data matrix of the ��Ԫ������ָ���ͼ��.bmp:" << endl;
		//for(int y = 0;y<imggest->height;y++)
	 //  {
		   //	uchar* ptr = (uchar*) (imggest->imageData+y*imggest->widthStep);

		   //	for (int x = 0;x<imggest->width;x++)
		   //	{
		   //		printf ("%5d",*ptr++);
		   //	}
	 //          printf("\n\n");
	 //  }
		//// added by zyp end


		//// added by zyp begin
	   //cout << "Display the data matrix of the ��Ԫ������ϲ�ʾ��ͼ1.bmp:" << endl;
		//for(int y = 0;y<seg->height;y++)
	 //  {
		   //	uchar* ptr = (uchar*) (seg->imageData+y*seg->widthStep);

		   //	for (int x = 0;x<seg->width;x++)
		   //	{
		   //		printf ("%5d",*ptr++);
		   //	}
	 //          printf("\n\n");
	 //  }
		//// added by zyp end


		//// added by zyp begin
	   //cout << "Display the data matrix of the ��Ԫ������ϲ�ʾ��ͼ2.bmp:" << endl;
		//for(int y = 0;y<seg_line->height;y++)
	 //  {
		   //	uchar* ptr = (uchar*) (seg_line->imageData+y*seg_line->widthStep);

		   //	for (int x = 0;x<seg_line->width;x++)
		   //	{
		   //		printf ("%5d",*ptr++);
		   //	}
	 //          printf("\n\n");
	 //  }
		//// added by zyp end


		for (int i = 0; i < C.size(); i++)
		{
			if (C[i].x2 - C[i].x1 == 1)
				nmb++;

		}

		//cout << "2*2��������"<< nmb << endl;
		cout << "����������  " << reg_num << endl << endl;

		fout << "����������  " << reg_num << endl << endl;
		//�ָ���
		cout << "================================================" << endl << endl;
		fout.close();


		cvWaitKey(0); //�ȴ�����


		cvReleaseImage(&img1);
		cvReleaseImage(&imggest);
		cvDestroyAllWindows();//�ر�

		//���ô���
		//char zyp;
		//cin >> zyp; 


		return 0;

	}

	else

		return -1;

}

