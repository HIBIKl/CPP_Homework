#include "Header.h"

//RNAM=矩形NAM
//使用改良isSameBlock阴影法判断是否同类块
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


//矩阵编码
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
//矩阵解码
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
Point REHelper(Mat f, Mat mark, int M, int N, Point start, int xgm) {
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

//灰度图f编码（第一步）
void RNAMCEncoding(Mat f, Mat& R, Mat& markMatrix, int M, int N, vector<Color>& p, vector<char>& q, int xgm) {
	//p为颜色表，q为坐标表，xgm为误差容许量
	//传入的markMatrix已经是所有元素都是0的矩阵变量了
	Point start, end;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			if (markMatrix.at<uchar>(i, j) == 0)//保险
			{
				start = Point(j, i);
				//REHelper寻找最大的矩形子模式
				end = REHelper(f, markMatrix, M, N, start, xgm);
				//start与end应为对角
				Color p1;
				p1.setLt(start);
				p1.setRb(end);
				//画图来解释会很简单
				uchar g1 = f.at<uchar>(start);
				//左上角
				uchar g2 = f.at<uchar>(Point(end.x, start.y));
				//右上角
				uchar g3 = f.at<uchar>(Point(start.x, end.y));
				//左下角
				uchar g4 = f.at<uchar>(end);
				//右下角
				//这样每一个坐标的正方形就确定了
				//（但是每一个坐标？这不是已经成为矩阵类了么）
				if (start.x < end.x && start.y < end.y)
				{
					p1.setGrey(Scalar(g1, g2, g3, g4));
					R.at<uchar>(start) = 1;
					R.at<uchar>(end) = 2;
				}//一般情况

				//特殊情况下
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
void RDHelper(Mat& R, Color p1) {
	//lt may be "left top " and rb equals to "right bottom"
	Point lt = p1.getLt();
	Point rb = p1.getRb();
	//获取灰度值
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
				//计算近似灰度值
				double g5 = g1 + (g2 - g1) * i2;
				double g6 = g3 + (g4 - g3) * i2;
				double gest = g5 + (g6 - g5) * i1;
				//赋值
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
void RNAMCDecoding(Mat& R, int M, int N, vector<Color> p, vector<char> q) {
	for (int i = 0; i < p.size(); i++)
		RDHelper(R, p[i]);//非REHelper
}

//计算灰度值的函数
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
double BPP(vector<Color> p, int M, int N, vector<char> q) {
	int a1 = 0, a2 = 0, a3 = 0;
	for (int i = 0; i < p.size(); i++) {
		if (p[i].getGrey()[0] != -1 && p[i].getGrey()[3] != -1) a1++;
		else if (p[i].getGrey()[1] == -1 && p[i].getGrey()[2] == -1) a3++;
		else  a2++;
	}
	double BPPValue = (q.size() + 16 * a1 + 8 * a2 + 4.0 * a3) / (M * N);
	return BPPValue;
}

void segmentDisplay(Mat& display, vector<Color> p) {
	for (int i = 0; i < p.size(); i++) {
		rectangle(display, p[i].getLt(), p[i].getRb(), Scalar(0, 0, 0));
	}
}