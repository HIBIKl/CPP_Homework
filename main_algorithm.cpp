#include "Diag_and_Hori.h"
#include "IBR.h"
#include "STC.h"

//������
long compression_time;//����ʱ��
long decode_time;//����ʱ��
unsigned long long blocks;//����
double psnr_value;//psnrֵ
double bpp_value;//bppֵ
double cr_value;//crֵ
long long qsc_time;//qsc����ʱ��
int region_nums; //��������

//Diagonal�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int diag_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
    if (argv1 != NULL) {
        Mat img = imread(argv1);
        if (!img.empty()) {

            //namedWindow("ԭͼ�Ҷ�ͼ��", 1);
            //imshow("ԭͼ�Ҷ�ͼ��", img);

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


            time_t begin1,end1,begin2,end2;
            begin1 = clock();

            /*�ֿ�*/
            RNAMCEncoding_Diagonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

            /*�������*/
            EnCode(R, M, N, coordinateList);
            //mt.End();
            end1 = clock();


            cout << "����ѹ������:" << end1 - begin1 << "ms" << endl;
            compression_time = end1-begin1;
            /*������ԭͼ�����ͼ��*/
            Mat T = Mat::zeros(M, N, CV_8UC1);

            begin2 = clock();
            Decode(T, M, N, coordinateList);
            RNAMCDecoding(T, M, N, colorList, coordinateList);
            end2 = clock();

            cout << "��ԭͼ���ʱ:" << end2 - begin2 << "ms" << endl;
            decode_time = end2 - begin2;

            cout << "����:" << colorList.size() << endl;
            blocks = colorList.size();

            cout << "PSNRֵ:" << PSNR(img_gray, T, M, N) << endl;
            psnr_value = PSNR(img_gray, T, M, N);

            cout << "BPPֵ:" << BPP(colorList, M, N, coordinateList) << endl;
            bpp_value = BPP(colorList, M, N, coordinateList);

            cout << "CRֵ:" << 8.0 / bpp_value << endl;
            cr_value = 8.0 / bpp_value;


            //namedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
            //imshow("ѹ��ͼ�Ҷ�ͼ��", T);

            imwrite(argv2, img_gray);//����Ҷ�ͼ
            imwrite(argv3, T);//��������ͼ��

            /*�ָ�ͼ*/
            Mat display(M, N, CV_8UC1, Scalar::all(255));
            segmentDisplay(display, colorList);

            //namedWindow("�ָ�ͼ", 1);
            //imshow("�ָ�ͼ", display);
            imwrite("./segment.bmp",display);
            //�ȴ�
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

//Horizonal�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int hori_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
    if (argv1 != NULL) {
        Mat img = imread(argv1);
		if (!img.empty()) {

            //namedWindow("ԭͼ�Ҷ�ͼ��", 1);
            //imshow("ԭͼ�Ҷ�ͼ��", img);

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

            time_t begin1,end1,begin2,end2;
            begin1 = clock();

			/*�ֿ�*/
			RNAMCEncoding_Horizonal(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

			/*�������*/
			EnCode(R, M, N, coordinateList);
            end1 = clock();


            cout << "����ѹ������:" << end1 - begin1 << "ms" << endl;
            compression_time = end1-begin1;

			/*������ԭͼ�����ͼ��*/
			Mat T = Mat::zeros(M, N, CV_8UC1);

            begin2 = clock();
			Decode(T, M, N, coordinateList);
			RNAMCDecoding(T, M, N, colorList, coordinateList);
            end2 = clock();

            cout << "��ԭͼ���ʱ:" << end2 - begin2 << "ms" << endl;
            decode_time = end2 - begin2;

            cout << "����:" << colorList.size() << endl;
            blocks = colorList.size();

            cout << "PSNRֵ:" << PSNR(img_gray, T, M, N) << endl;
            psnr_value = PSNR(img_gray, T, M, N);

            cout << "BPPֵ:" << BPP(colorList, M, N, coordinateList) << endl;
            bpp_value = BPP(colorList, M, N, coordinateList);

            cout << "CRֵ:" << 8.0 / bpp_value << endl;
            cr_value = 8.0 / bpp_value;

            //namedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
            //imshow("ѹ��ͼ�Ҷ�ͼ��", T);
            imwrite(argv2, img_gray);//�����������
            imwrite(argv3, T);//�����������

			/*�ָ�ͼ*/
			Mat display(M, N, CV_8UC1, Scalar::all(255));
			segmentDisplay(display, colorList);
            //namedWindow("�ָ�ͼ", 1);
            //imshow("�ָ�ͼ", display);
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

//IBR�������ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
int ibr_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4)
{
	IplImage* img = NULL;

    if ((img = cvLoadImage(argv1, 0)) != 0)
	{

        //cvNamedWindow("ԭͼ�Ҷ�ͼ��", 1);
        //cvShowImage("ԭͼ�Ҷ�ͼ��", img);
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
        compression_time = end - begin;

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
        decode_time = end - begin;

        cout << "����:" << num << endl;
        blocks = num;

        cout << "PSNRֵ:" << PSNR(img, newImg) << endl;
        psnr_value = PSNR(img, newImg);

        cout << "BPPֵ:" << BPP(color_list, width, height, Q) << endl;
        bpp_value = BPP(color_list, width, height, Q);

        cout << "CRֵ:" << 8.0 / BPP(color_list, width, height, Q) << endl;
        cr_value = 8.0 / BPP(color_list, width, height, Q);
        //cvNamedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
        //cvShowImage("ѹ��ͼ�Ҷ�ͼ��", newImg);
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
        //cvShowImage("�ָ�ʾ��ͼ", sketch);
        cvSaveImage("./segment.bmp",sketch);

        //cvWaitKey(2000);
		cvDestroyAllWindows();
	}

	return 0;
}

//STC�������ֱ�����2.ԭ��ͼ3.ת���Ҷ�ͼ�ļ���4.ת��RNAMC�ļ��� ��5.ͬ��췧ֵ 6.��ֵ��ֵ 7.���ֵ 8.�з� 1 ˮƽ 0��ֱ��
int stc_main(const char* argv1,const char* argv2,const char* argv3,const char* argv4,const char* argv5,const char* argv6,const char* argv7)
{
    int nmb = 0;
	IplImage* img1;
    if ((img1 = cvLoadImage(argv1, 0)) != 0)   //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
    {
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
        //IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);

		start = clock();
		cout << "building tree" << endl;
		BuildTreeT(img1, root, P, C, num, epsilon, 0, 0, M - 1, N - 1);
		cout << "making  Q" << endl;
		LevelOrder(Q, root);//Ѱ��ͬ��飬��������������ɫ��,�����

		end = clock();
		time = end - start;
		cout << "��������ʱ��:" << time << "ms" << endl;
        compression_time = time;


		start = clock();

		end = clock();

		time = end - start;

        //ofstream fout("Results.txt");
        cout << "��������ʱ��:  " << time << "  ms" << endl << endl;
        decode_time = time;
		cout << "epsilon =  " << epsilon << endl << endl;

        //fout << "epsilon =  " << epsilon << endl << endl;

		cout << "================================================" << endl << endl;

		//ofstream fout("Results.txt",ios::app);


        cout << "����:" << P.size() << endl << endl;
        blocks = P.size();
        //fout << "����:" << P.size() << endl << endl;

		cout << fixed << setprecision(4) << "BPP:" << BPP(P, M, N, Q) << endl << endl;
        //fout << fixed << setprecision(4) << "BPP:" << BPP(P, M, N, Q) << endl << endl;
        bpp_value = BPP(P, M, N, Q);
        cout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;
        //fout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;
        cr_value = 8.0/BPP ( P , M , N , Q );

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
        qsc_time = converge_time;
        cout<<"pooint 1"<<endl;
        //fout << "converge_time of QSC:  " << converge_time << "  ms" << endl << endl;

		Region** pixel_region = new Region * [M * N];
        cout<<"pooint 2"<<endl;

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
        cout<<"pooint 3"<<endl;

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

        //cvShowImage("����ϲ�ʾ��ͼ1", seg);
        //cvShowImage("����ϲ�ʾ��ͼ2", seg_line);
        cvSaveImage("region_merge_1.bmp",seg);
        cvSaveImage("region_merge_2.bmp",seg_line);
		MakeImggest(imggest, P, C, all_region);

		cout << "PSNR of recontructured:  " << STC_PSNR(img1, imggest) << endl << endl;
        psnr_value = STC_PSNR(img1, imggest);
		//cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;	
        //fout << "PSNR of recontructured:  " << STC_PSNR(img1, imggest) << endl << endl;

        //cvNamedWindow("�ҶȻ�ͼ��", CV_WINDOW_AUTOSIZE);
        //cvShowImage("�ҶȻ�ͼ��", img1); //��ʾԭʼ�Ҷ�ͼ��

        //cvNamedWindow("QSC����ָ���ͼ��", CV_WINDOW_AUTOSIZE);     //����ָ���ͼ��
        //cvShowImage("QSC����ָ���ͼ��", imggest);//����ת����ĻҶ�ͼ��   //����ָ���ͼ��

        cvSaveImage(argv2, img1, 0);//��ͼ��д���ļ�
        cvSaveImage(argv3, imggest, 0);//��ͼ��д���ļ�
		//��ʾ��ͼ
        //cvNamedWindow("�ָ�ʾ��ͼ", CV_WINDOW_AUTOSIZE);
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




            //cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ��

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
            //cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ��
			//��ʾ��ͼ����
		}

		cvSaveImage("��Ԫ���ָ�ʾ��ͼ.bmp", img1, 0);//��ͼ��д���ļ� , added by zyp
		cvSaveImage("��Ԫ������ָ���ͼ��.bmp", imggest, 0);//��ͼ��д���ļ� , added by zyp �ؽ����ͼ��

		cvSaveImage("��Ԫ������ϲ�ʾ��ͼ1.bmp", seg, 0);//��ͼ��д���ļ� , added by zyp  ����ϲ����þ�ֵ�����ͼ��
		cvSaveImage("��Ԫ������ϲ�ʾ��ͼ2.bmp", seg_line, 0);//��ͼ��д���ļ� , added by zyp


		for (int i = 0; i < C.size(); i++)
		{
			if (C[i].x2 - C[i].x1 == 1)
				nmb++;

		}

		//cout << "2*2��������"<< nmb << endl;
        cout << "����������  " << reg_num << endl << endl;
        region_nums = reg_num;
        //fout << "����������  " << reg_num << endl << endl;
		//�ָ���
		cout << "================================================" << endl << endl;
        //fout.close();


        //cvWaitKey(2000); //�ȴ�����
        cvReleaseImage(&img1);
		cvReleaseImage(&imggest);
        cvReleaseImage(&seg);
        cvReleaseImage(&seg_line);
		cvDestroyAllWindows();//�ر�
        delete seg;
        delete[] pixel_region;
        delete root;
        delete[] all_region;
        delete UpperLeft;
        delete Upper;
		return 0;
    }

    else

        return -1;

}

