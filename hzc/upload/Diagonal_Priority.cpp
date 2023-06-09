//#include "Header Dia.h"
//#include"Header.h"
#include"./hzc/upload/BigHeader.h"
//使用改良isSameBlock阴影法判断是否同类块

//bool isSameBlock(Mat f,Mat mark, Point lt, Point rb,int xgm)
//{
//	uchar g1 = f.at<uchar>(lt);
//	uchar g2 = f.at<uchar>(Point(rb.x, lt.y));
//	uchar g3 = f.at<uchar>(Point(lt.x, rb.y));
//	uchar g4 = f.at<uchar>(rb);
//	//标准矩形
//	if (lt.x < rb.x&&lt.y < rb.y)
//	{
//		int flag = 1;
//		for (int j = lt.y; j <= rb.y; j++)
//		{
//			for (int i = lt.x; i <= rb.x; i++)
//			{
//				double i1 = (j - lt.y) / (double)(rb.y - lt.y);
//				double i2 = (i - lt.x) / (double)(rb.x - lt.x);
//				double g5 = g1 + (g2 - g1)*i2;
//				double g6 = g3 + (g4 - g3)*i2;
//				double gest = g5 + (g6 - g5)*i1;
//				//cout << g1 << " " << g2 << " " << g3 << " " << g4 << " " << g5 << " " << g6 << " " << gest << " "<<f.at<uchar>(Point(i,j))<<endl;
//				if (abs(f.at<uchar>(Point(i, j)) - gest) > xgm||mark.at<uchar>(Point(i,j))==1)
//				{
//					flag = 0;
//					break;
//				}
//			}
//			if (flag == 0)break;
//		}
//		return flag;
//	}
//	//宽为1的矩形
//	else if (lt.x != rb.x&&lt.y == rb.y)
//	{
//		int flag = 1;
//		for (int i = lt.x; i <= rb.x; i++)
//		{
//			double i2 = (i - lt.x) / (double)(rb.x - lt.x);
//			double gest = g1 + (g4 - g1)*i2;
//			if (abs(f.at<uchar>(Point(i, lt.y)) - gest) > xgm|| mark.at<uchar>(Point(i,lt.y)) == 1)
//			{
//				flag = 0;
//				break;
//			}
//		}
//		return flag;
//	}
//	//长为1的矩形
//	else if (lt.x == rb.x&&lt.y != rb.y)
//	{
//		int flag = 1;
//		for (int j = lt.y; j <= rb.y; j++)
//		{
//			double i1 = (j - lt.y) / (double)(rb.y - lt.y);
//			double gest = g1 + (g4 - g1)*i1;
//			if (abs(f.at<uchar>(Point(lt.x, j)) - gest) > xgm|| mark.at<uchar>(Point(lt.x,j)) == 1)
//			{
//				flag = 0;
//				break;
//			}
//		}
//		return flag;
//	}
//	//孤立点矩形
//	else if (lt.x == rb.x&&lt.y == rb.y)
//	{
//		//double g1 = f.at<uchar>(lt);
//		if (mark.at<uchar>(lt) == 1)return 0;
//		return 1;
//	}
//}
//
////给灰度图f已经搜索过的矩形子模式做标记
//void mark(Mat &mark, Point lt, Point rb) {
//	for (int i = lt.y; i <= rb.y; i++)
//		for (int j = lt.x; j <= rb.x; j++)
//			mark.at<uchar>(i, j) = 1;
//}
//
//void EnCode(Mat &R, int height, int width, vector<char> &Q)
//{
//	int c = 0;
//	int offsetValue = 0;
//	int count = 0;
//
//	for (int i = 0; i < height; i++)
//	{
//		c = 0;
//		offsetValue = 0;
//		count = 0;
//		//Q.push_back(' ');
//		for (int j = 0; j < width; j++)
//		{
//			int value = R.at<uchar>(i,j);
//			if (0 == value)
//			{
//				if (j == width - 1)
//				{
//					Q.push_back('0');
//				}
//			}
//			else
//			{
//				if (1 == value)
//				{
//					Q.push_back('1');
//					Q.push_back('1');
//
//				}
//				else if (2 == value)
//				{
//					Q.push_back('1');
//					Q.push_back('0');
//					Q.push_back('1');
//				}
//				else if (3 == value)
//				{
//					Q.push_back('1');
//					Q.push_back('0');
//					Q.push_back('0');
//
//				}
//
//				//位置从1开始 不是从0开始 所以多减去1
//				int b = ceil(log((double)(width - c - count)) / log(2.0f));
//				if (0 == count)
//				{
//					offsetValue = j;
//				}
//				else
//				{
//					offsetValue = j - c - 1;
//				}
//
//				b = (b == 0) ? 1 : b;
//				count = 1;
//				c = j;
//
//				for (int v = b - 1; v >= 0; v--)
//				{
//					if ((offsetValue & (1 << v)) == 0)
//					{
//						Q.push_back('0');
//					}
//					else
//					{
//						Q.push_back('1');
//					}
//				}
//			}
//		}
//	}
//}
//
//void Decode(Mat &R, int height, int width, const vector<char> &Q)
//{
//	int n = 0;
//	int count = 0;
//	//上个非零元素的位置
//	int c = 0;
//	int row = 0;
//	int num = 0;
//	for (int pos = 0; pos < Q.size(); pos++)
//	{
//		if ('1' == Q[pos])
//		{
//			pos++;
//			if ('1' == Q[pos])
//			{
//				n = 1;
//
//			}
//			else
//			{
//				pos++;
//				if ('1' == Q[pos])
//				{
//					n = 2;
//				}
//				else
//				{
//					n = 3;
//				}
//			}
//		}
//		else
//		{
//			row++;
//			count = 0;
//			c = 0;
//			num = 0;
//			continue;
//			//如果是0
//			//if(c == 0)
//			//{
//			//	row++;
//			//	continue;
//			//}
//			//else
//			//{
//			//	row++;
//			//	count = 0;
//			//	c = 0;
//			//	num = 0;
//			//	continue;
//
//			//}
//		}
//
//		int b = ceil(log((double)(width - c - count)) / log(2.0f));
//		b = b == 0 ? 1 : b;
//		count = 1;
//
//		int value = 0;
//		for (int i = b - 1; i >= 0; i--)
//		{
//			pos++;
//			if ('1' == Q[pos])
//			{
//				value += 1 << i;
//			}
//		}
//
//		if (0 == num)
//		{
//			c = c + value;
//		}
//		else
//		{
//			c = c + value + 1;
//		}
//
//		num++;
//
//
//		R.at<uchar>(row,c) = n;
//
//		if (c == (width - 1))
//		{
//			row++;
//			count = 0;
//			c = 0;
//			num = 0;
//		}
//	}
//
//	/*for(vector<char>::const_iterator it = Q.begin();it != Q.end();it++)
//	{
//		if(1 == *it)
//		{
//			it++;
//			if(1 == *it)
//			{
//				n = 1;
//
//			}
//			else
//			{
//				it++;
//				if(1 == *it)
//				{
//					n = 2;
//				}
//				else
//				{
//					n = 3;
//				}
//			}
//		}
//		else
//		{
//			//如果是0
//			if(c == 0)
//			{
//				row++;
//				continue;
//			}
//			else
//			{
//
//
//				row++;
//				count = 0;
//				c = 0;
//				num = 0;
//				continue;
//
//			}
//		}
//
//		int b = ceil(log((double)(width- c -count))/log(2.0f));
//		b = b==0? 1:b;
//		count = 1;
//
//		int value = 0;
//		for(int i = b -1;i >=0;i--)
//		{
//			it++;
//			if(*it == 1)
//			{
//				value += 1<<i;
//			}
//		}
//
//		if(0 == num)
//		{
//			c = c + value;
//		}
//		else
//		{
//			c = c + value +1;
//		}
//
//		num++;
//
//
//		(R->data.ptr + row*R->step)[c] = n;
//
//		if( c == (width -1))
//		{
//			row++;
//			count = 0;
//			c = 0;
//			num = 0;
//		}
//	}*/
//
//}
//
////寻找最大的矩形子模式
//Point REHelper(Mat f, Mat mark, int M, int N, Point start,int xgm) {
//	Point end = start;
//	Point end1, end2;
//	while (end.x < M&&end.y < N && (mark.at<uchar>(end) == 0) && (mark.at<uchar>(start) == 0) ){
//		if (!isSameBlock(f, mark,start, end,xgm)) break;
//		end.x++;
//		end.y++;
//	}
//	end.x--;
//	end.y--;
//
//	end1 = end;
//	while (end1.x < M && (mark.at<uchar>(end1) == 0)) {
//		if (!isSameBlock(f,mark, start, end1,xgm)) break;
//		end1.x++;
//	}
//	end1.x--;
//
//	end2 = end;
//	while (end2.y < N && (mark.at<uchar>(end2) == 0)) {
//		if (!isSameBlock(f, mark,start, end2,xgm)) break;
//		end2.y++;
//	}
//	end2.y--;
//
//
//	if ((end2.x - start.x + 1)*(end2.y - start.y + 1) > (end1.x - start.x + 1)*(end1.y - start.y + 1))return end2;
//	else return end1;
//
//	/*Point end_second = start;
//	flag1 = 0;
//	flag2 = 0;
//	while (flag1 == 0 || flag2 == 0) {
//		end1 = end_second;
//		while (flag1 == 0) {
//			end1.x++;
//			if (end1.x == N)flag1 = 1;
//			else if (REHelper2(f, start, end1))flag1 = 1;
//			else if (!isSameBlock(f, start, end1))flag1 = 1;
//			if (flag1 == 1)end1.x--;
//		}
//		end2 = end1;
//		while (flag2 == 0) {
//			end2.y++;
//			if (end2.y == M)flag2 = 1;
//			else if (REHelper2(f, start, end2))flag2 = 1;
//			else if (!isSameBlock(f, start, end2))flag2 = 1;
//			if (flag2 == 1)end2.y--;
//		}
//		Rect rec1(start, end1), rec2(start, end2);
//		if (rec1.area() < rec2.area())end_second = end2;
//		else end_second = end1;
//	}
//	Point end_third = start;
//	flag1 = 0;
//	flag2 = 0;
//	while (flag1 == 0 || flag2 == 0) {
//		end2 = end_third;
//		while (flag2 == 0) {
//			end2.y++;
//			if (end2.y == M)flag2 = 1;
//			else if (REHelper2(f, start, end2))flag2 = 1;
//			else if (!isSameBlock(f, start, end2))flag2 = 1;
//			if (flag2 == 1)end2.y--;
//		}
//		end1 = end2;
//		while (flag1 == 0) {
//			end1.x++;
//			if (end1.x == N)flag1 = 1;
//			else if (REHelper2(f, start, end1))flag1 = 1;
//			else if (!isSameBlock(f, start, end1))flag1 = 1;
//			if (flag1 == 1)end1.x--;
//		}
//		Rect rec1(start, end1), rec2(start, end2);
//		if (rec1.area() < rec2.area())end_third = end2;
//		else end_third = end1;
//	}
//	Point end;
//	if ((end_first.x-start.x+1)*(end_first.y-start.y+1)<=(end_second.x-start.x+1)*(end_second.y-start.y+1))end = end_second;
//	else end = end_first;
//	if ((end.x-start.x+1)*(end.y-start.y+1)<(end_third.x-start.x+1)*(end_third.y-start.y+1))end = end_third;*/
//}
//
////灰度图f编码
//void RNAMCEncoding(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm) {
//	Point start, end;
//	for (int i = 0; i < M; i++)
//		for (int j = 0; j < N; j++)
//		{
//			if (markMatrix.at<uchar>(i, j) == 0)
//			{
//				start = Point(j,i);
//				end = REHelper(f, markMatrix, M,N,start,xgm);
//				Color p1;
//				p1.setLt(start);
//				p1.setRb(end);
//				uchar g1 = f.at<uchar>(start);
//				uchar g2 = f.at<uchar>(Point(end.x, start.y));
//				uchar g3 = f.at<uchar>(Point(start.x, end.y));
//				uchar g4 = f.at<uchar>(end);
//				if (start.x < end.x&&start.y < end.y)
//				{
//					p1.setGrey(Scalar(g1, g2, g3, g4));
//					R.at<uchar>(start) = 1;
//					R.at<uchar>(end) = 2;
//				}
//				//宽为1的矩形
//				if (start.x != end.x&&start.y == end.y)
//				{
//					p1.setGrey(Scalar(g1, 0, 0, g4));
//					R.at<uchar>(start) = 1;
//					R.at<uchar>(end) = 2;
//				}
//				//长为1的矩形
//				if (start.x == end.x&&start.y != end.y)
//				{
//					p1.setGrey(Scalar(g1, 0, 0, g4));
//					R.at<uchar>(start) = 1;
//					R.at<uchar>(end) = 2;
//				}
//				//孤立点矩形
//				if (start.x == end.x&&start.y == end.y)
//				{
//					p1.setGrey(Scalar(g1, 0, 0, 0));
//					R.at<uchar>(start) = 3;
//				}
//				p.push_back(p1);
//				mark(markMatrix,start,end);
//				/*for (int i = 0; i < M; i++) {
//					for (int j = 0; j < N; j++) {
//						cout << (int)markmatrix.at<uchar>(i, j);
//					}
//					cout << endl;
//				}
//				cout << endl;*/
//			}
//		}
//	/*for (int i = 0; i < M; i++) {
//		for (int j = 0; j < N; j++) {
//			cout << (int)R.at<uchar>(i, j);
//		}
//		cout << endl;
//	}*/
//}
//
////恢复矩形子模式的值
//void RDHelper(Mat& R, Color p1) {
//	Point lt = p1.getLt();
//	Point rb = p1.getRb();
//	uchar g1 = p1.getGrey()[0];
//	uchar g2 = p1.getGrey()[1];
//	uchar g3 = p1.getGrey()[2];
//	uchar g4 = p1.getGrey()[3];
//	//标准矩形
//	if (lt.x < rb.x&&lt.y < rb.y)
//	{
//
//		for (int j = lt.y; j <= rb.y; j++)
//		{
//			for (int i = lt.x; i <= rb.x; i++)
//			{
//				double i1 = (j - lt.y) / (double)(rb.y - lt.y);
//				double i2 = (i - lt.x) / (double)(rb.x - lt.x);
//				double g5 = g1 + (g2 - g1)*i2;
//				double g6 = g3 + (g4 - g3)*i2;
//				double gest = g5 + (g6 - g5)*i1;
//				R.at<uchar>(Point(i, j)) = gest;
//			}
//		}
//	}
//	//宽为1的矩形
//	if (lt.x != rb.x&&lt.y == rb.y)
//	{
//		for (int i = lt.x; i <= rb.x; i++)
//		{
//			double i2 = (i - lt.x) / (double)(rb.x - lt.x);
//			double gest = g1 + (g4 - g1)*i2;
//			R.at<uchar>(Point(i, lt.y)) = gest;
//		}
//	}
//	//长为1的矩形
//	if (lt.x == rb.x&&lt.y != rb.y)
//	{
//		for (int j = lt.y; j <= rb.y; j++)
//		{
//			double i1 = (j - lt.y) / (double)(rb.y - lt.y);
//			double gest = g1 + (g4 - g1)*i1;
//			R.at<uchar>(Point(lt.x, j)) = gest;
//		}
//	}
//	//孤立点矩形
//	if (lt.x == rb.x&&lt.y == rb.y)
//	{
//		R.at<uchar>(Point(lt.x, lt.y)) = g1;
//	}
//}
//
////灰度图f解码
//void RNAMCDecoding(Mat& R,int M,int N,vector<Color> p,vector<char> q) {
//	for (int i = 0; i < p.size(); i++)
//		RDHelper(R, p[i]);
//}
//
////PSNR
//double PSNR(Mat f, Mat R,int M,int N) {
//	double mid = 0;;
//	for (int i = 0; i < M; i++)
//		for (int j = 0; j < N; j++) {
//			mid += pow(f.at<uchar>(i, j) - R.at<uchar>(i, j), 2);
//		}
//	return 10 * log10f(pow(255., 2)*M*N / mid);
//}
//
////BPP
//double BPP(vector<Color> p, int M, int N, vector<char> q) {
//	int a1 = 0, a2 = 0, a3 = 0;
//	for (int i = 0; i < p.size(); i++) {
//		if (p[i].getGrey()[0] != -1 && p[i].getGrey()[3] != -1) a1++;
//		else if (p[i].getGrey()[1] == -1 && p[i].getGrey()[2] == -1) a3++;
//		else  a2++;
//	}
//	double BPPValue = (q.size() + 16 * a1 + 8 * a2 + 4.0*a3) / (M*N);
//	return BPPValue;
//}
//
//void segmentDisplay(Mat &display, vector<Color> p) {
//	for (int i = 0; i < p.size(); i++) {
//		rectangle(display,p[i].getLt(),p[i].getRb(), Scalar(0),1);
//	}
//}
//
//////实现往坐标表里插入位置的功能
////void CEHelper(vector<bool>& b, int cur_pos, int last_pos = -1, int last_value = 0) {
////	//用来判断需要多少个bit位
////	int d;
////	//记录序号或者距离
////	int i;
////	if (last_pos != -1) {
////		d = N - last_pos - 1;
////		i = cur_pos - last_pos - last_value;
////	}
////	else {
////		d = N;
////		i = cur_pos;
////	}
////	int n = 0;
////	while (pow(2., n) < d)n++;
////	vector<bool> a;
////	if (i < 0) {
////		int x = N - 1 - last_pos - 1;
////		vector<bool> a1;
////		while (x) {
////			a1.push_back(x % 2);
////			x /= 2;
////		}
////		for (int j = 0; j < (n - a1.size()); j++)
////			b.push_back(0);
////		for (int j = a1.size() - 1; j >= 0; j--)
////			b.push_back(a1[j]);
////	}
////	else
////	while (i) {
////		a.push_back(i % 2);
////		i /= 2;
////	}
////	if(a.size()>n)
////	cout << a.size() << " " << n << endl;
////	/*for (int j = 0; j < (n - a.size()); j++)
////		b.push_back(0);*/
////	for (int j = a.size() - 1; j >= 0; j--)
////		b.push_back(a[j]);
////}
////
//////实现从坐标表里取出位置的功能
////int CDHelper(vector<bool>& b, vector<bool>::iterator& i, int last_pos = -1, int last_value = 0) {
////	//用来判断需要多少个bit位
////	int d;
////	if (last_pos != -1)
////		d = N - last_pos - 1;
////	else
////		d = N;
////	int n = 0;
////	while (pow(2., n) < d)n++;
////
////	int pos = 0;
////	pos += *i;
////	++i;
////	for (int j = 1; j < n; j++) {
////		pos *= 2;
////		pos += *i;
////		++i;
////	}
////	if (last_pos != -1){ 
////		if (last_value == 2) {
////			if (pos == N - 2 - last_pos)
////			{
////				for (int j = 0; j < n; j++)++i;
////				return last_pos + 1;
////			}
////			else return pos + last_value + last_pos;
////		}
////		else return pos + last_value + last_pos;
////	}
////	else return pos;
////}
////
//////R	矩阵坐标编码
////void CoordinateEncoding(Mat R, vector<bool>& b) {
////	for (int i = 0; i < M; i++) {
////		//本行是否全零
////		int flag = 0;
////		//本行是否有元素在最末尾
////		int flag1 = 0;
////		int last_pos = -1;
////		int last_value = 0;
////		for (int j = 0; j < N; j++) {
////			uchar x = R.at<uchar>(i, j);
////			if (x != 0) {
////				flag = 1;
////				b.push_back(1);
////				if (x == 1) {
////					b.push_back(1);
////				}
////				if (x == 2) {
////					b.push_back(0);
////					b.push_back(1);
////				}
////				if (x == -1) {
////					b.push_back(0);
////					b.push_back(0);
////				}
////				CEHelper(b, j, last_pos, last_value);
////				last_pos = j;
////				last_value = x;
////				if (j == N - 1)flag1 = 1;
////			}
////		}
////		if (flag == 0 || flag1 == 0)
////			b.push_back(0);
////	}
////}
////
//////R矩阵坐标解码
////void CoordinateDecoding(vector<bool>& b, Mat& R) {
////	R = Mat::zeros(M, N, CV_32FC1);
////	//当前行
////	int cur_row = 0;
////	vector<bool>::iterator i = b.begin();
////	int last_pos = -1;
////	int last_value = 0;
////	while (i != b.end()) {
////		if (*i == 0) {
////			i++;
////			cur_row++;
////			last_pos = -1;
////			last_value = 0;
////			continue;
////		}
////		else {
////			i++;
////			int x = 0;
////			if (*i == 1)
////				x = 1;
////			else {
////				i++;
////				if (*i == 1)
////					x = 2;
////				else
////					x = -1;
////			}
////			i++;
////			int pos = CDHelper(b, i, last_pos, last_value);
////			R.at<uchar>(cur_row, pos) = x;
////			//cout << cur_row << " " << pos << " " << x << endl;
////			last_value = x;
////			last_pos = pos;
////			if (pos == N - 1) {
////				cur_row++;
////				last_pos = -1;
////				last_value = 0;
////			}
////			else if (*i == 0) {
////				cur_row++;
////				last_pos = -1;
////				last_value = 0;
////				i++;
////			}
////		}
////	}
////}
//
