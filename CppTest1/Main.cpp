#include<stdio.h>
#include<stdlib.h>
#include"opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include<io.h>
#include <map>
#include "ReadConfig.h"
#include "FDGazeVR.h"
#include "tools.h"
#include <thread>
#include <windows.h>
#include <math.h>
//#include <AFX.h>
#include "NEONvsSSE.h"
#include "bmp.h"

//#include "opencv2/core/ocl.hpp
#define ImageSize 640*480

#define M_PI       3.14159265358979323846

using namespace std;
using namespace cv;

//struct test
//{
//	char a;
//int b;
//double c;
//char d;
//};
//
////int main(void)
////{
////	IplImage* src = cvLoadImage("1.bmp", 0);//导入图片
////	int width = src->width;//图片宽度
////	int height = src->height;//图片高度
////	cout << width << " " << height << endl;
////	for (int i = -1; i < 40; i++)
////	{
////		printf("%4d ",i);
////	}
////	cout << endl;
////	for (int row = 0; row < height - 100; row++)
////	{
////		uchar* ptr = (uchar*)src->imageData + row * src->width;//获得灰度值数据指针
////		printf("%4d ", row);
////		for (int cols = 0; cols < width - 160; cols++)
////		{
////			int intensity = ptr[cols];
////			printf("%4d ",intensity);
////		}
////		cout << endl << endl;
////	}
////
////	system("pause");
////	return 0;
////
////}
//

union 
{
	int d;                                                            
	unsigned char uc[4];                                                     
} getint;

void ReadBuffer(unsigned char *buffer,int size,const char *path,int headLen)
{
	FILE *fp = fopen(path, "rb");
	if (fp == NULL)
	{
		printf("null file\n");
		return;
	}
	unsigned char ch;
	int i = 0;
	while (i++ < headLen)
	{
		ch = getc(fp);
	}

	i = 0;
	while (i<size)
	{
		buffer[i++] = getc(fp);
	}
	fclose(fp);
}

void FlippingBuffer(unsigned char *buffer, int rows,int cols)
{
	char *cpBuffer = new char[rows*cols];
	memcpy(cpBuffer, buffer, rows*cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			buffer[i * cols + j] = cpBuffer[(rows - 1 - i) * cols + j];
		}
	}
}

void ReadBmp(unsigned char* BMPhead, int headLen, unsigned char* srcData,int imgSize,char* path)
{
	FILE *fp = fopen(path, "rb");
	if (fp == NULL)
	{
		printf("null file\n");
		return;
	}
	unsigned char ch;
	int i = 0;
	while (i < headLen)
	{
		ch = getc(fp);
		BMPhead[i++] = ch;
	}

	i = 0;
	while (i< imgSize)
	{
		srcData[i++] = getc(fp);
	}
	fclose(fp);
}

void ReadData( void* srcData,int size, const char* path)
{
	FILE *fp = fopen(path, "rb");
	if (fp == NULL)
	{
		printf("null file\n");
		return;
	}

	//unsigned char ch;
	//int	i = 0;
	//while (i < size)
	//{
	//	srcData[i++] = getc(fp);
	//}

	fread(srcData, 1, size, fp);

	fclose(fp);
}

void ReadBmp(char* BMPhead, char* srcData)
{
	//ifstream ff("E:\\work\\AndroidPJ\\AndroidNewFD\\BMP\\Src\\3.bmp", ios::binary);
	//if (!ff)
	//{
	//	cout << "读取文件失败" << endl;
	//	return;
	//}
	//ff.read((char*)BMPhead, 1078);
	//int a = 0;
	//if (!ff)
	//{
	//	cout << "读取文件失败" << endl;
	//	return;
	//}
	//ff.read((char*)(srcData),200*200 );
	//ff.close();

	FILE *fp = fopen("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\3orig.bmp", "rb+");
	if (fp == NULL)
	{
		printf("null file\n");
		return;
	}
	unsigned char ch;
	int i = 0;
	while (i < 1078)
	{
		ch = getc(fp);
		BMPhead[i++] = ch;
	}

	i = 0;
	while (i<ImageSize)
	{
		srcData[i++] = getc(fp);
	}
	fclose(fp);
}

void WriteBmp(char* BMPhead, char* srcData,int size,const char *path)
{
	//ofstream ff("E:\\work\\AndroidPJ\\AndroidNewFD\\BMP\\Src\\x.bmp", ios::binary);
	//ff.write(BMPhead, 1078);
	//ff.write(srcData, 200 * 200);
	//ff.close();
	//FILE *fp = fopen("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\ans.bmp", "wb");
	FILE *fp = fopen(path, "wb");
	if (fp == NULL)
	{
		printf("write bmp erro\n");
		return;
	}
	fwrite(BMPhead,1,1078,fp);
	fwrite(srcData, 1, size, fp);
	fclose(fp);
}

//pupilx - 0.573853672	float
//pupily	24.6105938	float
//- glints	0x00338bd8 { {x = -0.478660077 y = 24.4423141 re = 1.00000000 }, { x = -0.710323632 y = 24.7452240 re = 1.00000000 }, ...}	EyeGlint[8]
//+ [0]{ x = -0.478660077 y = 24.4423141 re = 1.00000000 }	EyeGlint
//+ [1]{ x = -0.710323632 y = 24.7452240 re = 1.00000000 }	EyeGlint
//+ [2]{ x = -0.511575699 y = 24.7327137 re = 0.898312569 }	EyeGlint
//+ [3]{ x = -0.596645057 y = 24.4548512 re = 0.897987783 }	EyeGlint
//+ [4]{ x = -0.433438748 y = 24.5025082 re = 0.893479705 }	EyeGlint
//+ [5]{ x = -0.716936648 y = 24.6221352 re = 0.891170323 }	EyeGlint
//+ [6]{ x = -0.435997248 y = 24.5961857 re = 0.871681988 }	EyeGlint
//+ [7]{ x = -0.669882715 y = 24.5172863 re = 0.896231592 }	EyeGlint
//
//pupilx	161.985138	float
//pupily	80.6371307	float
//- glints	0x00438b18 { {x = 462.087494 y = 105.112503 re = 1.00000000 }, { x = 501.885712 y = 65.2857132 re = 1.00000000 }, ...}	EyeGlint[8]
//+ [0]{ x = 462.087494 y = 105.112503 re = 1.00000000 }	EyeGlint
//+ [1]{ x = 501.885712 y = 65.2857132 re = 1.00000000 }	EyeGlint
//+ [2]{ x = 453.569458 y = 61.8055573 re = 0.898312569 }	EyeGlint
//+ [3]{ x = 494.000000 y = 105.867645 re = 0.897987783 }	EyeGlint
//+ [4]{ x = 445.666656 y = 94.0222244 re = 0.893479705 }	EyeGlint
//+ [5]{ x = 512.543457 y = 82.7173920 re = 0.891170323 }	EyeGlint
//+ [6]{ x = 441.183350 y = 79.4333344 re = 0.871681988 }	EyeGlint
//+ [7]{ x = 508.700012 y = 97.5166702 re = 0.896231592 }	EyeGlint

void transpose(int* array)
{
	int i, j, t;
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<i; j++)
		{
			t = array[i*3+j];
			array[i*3+j] = array[j*3+i];
			array[j*3+i] = t;
		}
	}
}

void LowBlurNone(cv::Mat& src, cv::Size se, cv::Mat &dst)
{
	dst = src.clone();

	int eh = dst.rows - se.height;
	int ew = dst.cols - se.width;

	cv::Rect roi;
	roi.x = 0;
	roi.y = 0;
	roi.height = dst.rows;
	roi.width = dst.cols;

	int sm = -se.height / 2;
	int em = se.height / 2 + 1;

	int sn = -se.width / 2;
	int en = se.width / 2 + 1;

	unsigned char **q = new unsigned char *[se.height];
	unsigned char *mm = new unsigned char[roi.width];
	//std::cout << " ==== " << roi.width << std::endl;
	//printf("====%d\n", dst.step);
	//printf("====%d\n", (int)dst.step);
	for (int i = se.height; i<eh; i++)
	{
		unsigned char *res = dst.data + (i + roi.y)*dst.step + se.width + roi.x;

		for (int qi = 0; qi<se.height; qi++)
		{
			q[qi] = src.data + (i + roi.y + sm + qi)*src.step + roi.x;
		}
		for (int j = 0; j<roi.width; j++)
		{
			int lmm = 255;
			for (int qi = 0; qi<se.height; qi++)
			{
				if (*q[qi]<lmm)
					lmm = *q[qi];
				//lmm = FASTMIN(*q[qi], lmm);
				q[qi]++;
			}
			mm[j] = lmm;
		}
		for (int j = se.width; j<ew; j++)
		{
			int qmm = 255;
			for (int qj = j + sn; qj<j + en; qj++)
			{
				if (mm[qj]<qmm)
					qmm = mm[qj];
				//qmm = FASTMIN(qmm, mm[qj]);
			}
			*res = qmm;
			res++;
		}
	}

	delete[] q;
	delete[] mm;
}

int calculator_plus_LowBlurDSP(unsigned char* srcBuffer, int srcBufferLen, int rows, int cols, int height, int width, unsigned char* imageData, int imageDataLen, int64* sumtime, unsigned char* midMat, int midMatLen)
{
#ifdef PROFILING_ON
	uint64 startTime = HAP_perf_get_time_us();
#endif
	int eh = rows - height / 2; 
	int ew = cols - width / 2;
	int sm = -height / 2;
	int sh = height / 2;
	int sw = width / 2;
	int sn = -width / 2;
	int en = width / 2 + 1;

	const unsigned char **q = new const unsigned char *[height];
	unsigned char *mm = new unsigned char[cols];

	for (int i = sh; i<eh; i++)
	{
		unsigned char *res = imageData + i * cols + sw;
		for (int qi = 0; qi<height; qi++)
		{
			q[qi] = srcBuffer + (i + sm + qi)*cols;
		}
		for (int j = 0; j<cols; j++)
		{
			int lmm = 255;
			for (int qi = 0; qi<height; qi++)
			{
				if (*q[qi]<lmm)
					lmm = *q[qi];
				q[qi]++;
			}
			mm[j] = lmm;
		}
		for (int j = sw; j<ew; j++)
		{
			int qmm = 255;
			for (int qj = j + sn; qj<j + en; qj++)
			{
				if (mm[qj]<qmm)
					qmm = mm[qj];
			}
			*res = qmm;
			res++;
		}
	}
	delete[] q;
	delete[] mm;
#ifdef PROFILING_ON
	uint64 endTime = HAP_perf_get_time_us();
	*sumtime = (int64)endTime - startTime;
#endif
	return 0;
}

int testStatic()
{
	int cc = 0;
	return ++cc;
}

void FlipImage(unsigned char* imgHead,unsigned char *buffer, int rows, int cols)
{

	for (int i = 0; i < 4; i++)
	{
		getint.uc[i] = imgHead[22 + i];
	}
	if (getint.d > 0)
	{
		FlippingBuffer(buffer, rows, cols);
	}
}
 

int OnlyShowBuffer(int rows,int cols,const char* path,int headSize = 70)
{
	Mat dst(rows,cols, CV_8UC1,Scalar(0));
	unsigned char dstdata[640 * 480 + 1078];
	ReadData(dstdata, rows*cols + headSize, path);
	memcpy(dst.data, dstdata + headSize, rows * cols);  
	//FlippingBuffer(dst.data, rows, cols);
	imshow("pahtimg", dst);
	char pathNew[512] = {0};
	int len = strlen(path);
	memcpy(pathNew, path, len);
	pathNew[len] = pathNew[len - 1];
	pathNew[len - 1] = pathNew[len - 2];
	pathNew[len - 2] = pathNew[len - 3];
	pathNew[len - 3] = pathNew[len - 4];
	pathNew[len - 4] = 'x';
	char name[128];
	sprintf(name,"C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\TestImage\\2.bmp");
	imwrite(name,dst);
	waitKey();
	return 0;
}

template <typename T>
inline void swap(T* array, unsigned int i, unsigned int j)
{
	T t = array[i];
	array[i] = array[j];
	array[j] = t;
}

/*
* 递归输出序列的全排列
*/
template <typename T>
void FullArray(T* array, size_t array_size, unsigned int index)
{
	if (index >= array_size)
	{
		for (unsigned int i = 0; i < array_size; ++i)
		{
			cout << array[i] << ' ';
		}

		cout << '\n';

		return;
	}

	for (unsigned int i = index; i < array_size; ++i)
	{
		swap(array, i, index);

		FullArray(array, array_size, index + 1);

		swap(array, i, index);
	}
}

/*
* 将数组中的元素翻转
*/
inline void Reverse(unsigned int* array, size_t array_size)
{
	for (unsigned i = 0; 2 * i < array_size - 1; ++i)
	{
		unsigned int t = array[i];
		array[i] = array[array_size - 1 - i];
		array[array_size - 1 - i] = t;
	}
}

inline int LexiNext(unsigned int* lexinum, size_t array_size)
{
	unsigned int i, j, k, t;

	i = array_size - 2;

	while (i != UINT_MAX && lexinum[i] > lexinum[i + 1])
	{
		--i;
	}

	//达到字典序最大值
	if (i == UINT_MAX)
	{
		return 1;
	}

	for (j = array_size - 1, k = UINT_MAX; j > i; --j)
	{
		if (lexinum[j] > lexinum[i])
		{
			if (k == UINT_MAX)
			{
				k = j;
			}
			else
			{
				if (lexinum[j] < lexinum[k])
				{
					k = j;
				}
			}
		}
	}

	t = lexinum[i];
	lexinum[i] = lexinum[k];
	lexinum[k] = t;

	Reverse(lexinum + i + 1, array_size - i - 1);
	return 0;
}

/*
* 根据字典序输出排列
*/
inline void ArrayPrint(int * array, size_t array_size, const unsigned int* lexinum)
{
	for (unsigned int i = 0; i < array_size; ++i)
	{
		cout << array[lexinum[i]] << ' ';
	}

	cout << '\n';
}

/*
* 基于逆序数的全排列输出
*/

int FullArray(int* array, size_t array_size)
{
	unsigned int *lexinumber = new unsigned int[array_size];

	for (unsigned int i = 0; i < array_size; ++i)
	{
		lexinumber[i] = i;
	}

	ArrayPrint(array, array_size, lexinumber);

	while (!LexiNext(lexinumber, array_size))
	{
		ArrayPrint(array, array_size, lexinumber);
	}

	delete[] lexinumber;
	return 0;
}

bool mySwap(int *a, int l, int r)
{
	for (int i = l; i < r; i++)
	{
		if (a[i] == a[r])
		{
			return false;
		}
	}
	swap(a[l], a[r]);
	return true;
}

void myFullArray(int *a, int k, int n)
{
	if (k > n - 1)
	{
		for (int i = 0; i < n; i++)
		{
			cout << a[i] << " ";

		} 
		cout << endl;
		return;
	}
	for (int i = k; i < n; i++)
	{
		if (mySwap(a, k, i))
		{
			myFullArray(a, k + 1, n);
			swap(a[k], a[i]);
			//mySwap(a, k, i);
		}
	}
}

int SeparateImg( const char * path,int srcWidth,int srcHeight,Rect r1,Rect r2)
{
	Mat src(srcHeight, srcWidth, CV_8UC1);
	int len = strlen(path);
	int headLen = 0;
	int isNeedFlip = 0;
	if (path[len - 1] == 'p')
	{
		headLen = 1078;
		isNeedFlip = 1;
	}
	else
	{
		headLen = 70;
	}
	ReadBuffer(src.data, srcHeight *srcWidth, path, headLen);

	if (isNeedFlip == 1)
	{
		FlippingBuffer(src.data,srcWidth, srcHeight);
	}
	//imshow("1", src);

	Mat dst;
	dst = src(r1);
	//imshow("2", dst);
	char pathNew[1024] = { 0 };
	
	memcpy(pathNew, path, len);
	pathNew[len] = 'p';
	pathNew[len - 1] = 'm';
	pathNew[len - 2] = 'b';
	pathNew[len - 3] = pathNew[len - 4];
	pathNew[len - 4] = 'L';
	imwrite(pathNew, dst);

	dst = src(r2);
	pathNew[len - 4] = 'R';
	imwrite(pathNew, dst);
	//waitKey();
	return 0;
}

int CombineImg(const char* path1, const char* path2)
{
	Mat src1 = imread(path1, 1);
	Mat src2 = imread(path2, 1);
	Mat dst(src1.rows, src1.cols * 2, src1.type());
	imshow("src1", src1);
	imshow("src2", src2);
	//Mat dst1(,,)
	//src1.copyTo(dst(Rect(0,src1.cols,src1.cols,src1.rows)));
	Mat dst1 = dst((Rect(0, 0, src1.cols, src1.rows)));
	Mat dst2 = dst((Rect(src2.cols, 0, src2.cols, src2.rows)));

	src1.copyTo(dst1);
	src2.copyTo(dst2);
	imshow("1", dst);
	waitKey();
	return 0;
}

//获取路径下所有文件
size_t GetFilesByPath(const std::string &path, std::vector<std::string>& vct_files, std::string ext = "")
{
	long long hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	std::string name;
	std::string ext_name;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			name = std::string(fileinfo.name);
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (name != "." && name != "..")
				{
					std::string newPath = path + "\\" + name;
					GetFilesByPath(newPath, vct_files);
				}
			}
			else
			{
				ext_name = name.substr(name.rfind('.') + 1);
				if (ext != "")
				{
					if (ext_name == ext)
					{
						vct_files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}
				}
				else
				{
					vct_files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return vct_files.size();
}

int testMap()
{
	map<string, string> map_t;
	cout << map_t["input"] << endl;
	map_t["input"] = "1";
	cout << map_t["input"] << endl;
	return 0;
}

//int main(int argc, char *argv[])
//{
//	//wchar_t w_ch[128];
//	//char ch[128] = "123";
//	//swprintf(w_ch, L"%S", ch);
//	//wprintf(L"%s", w_ch);
//	char cfgfilepath[512] = "C:/Users/LiXiang/Desktop/config.ini";
//	map<string, string> cfg_map;


//	memset(pg.glints, -1, sizeof(pg.glints));
//	ReadConfigFile(cfgfilepath, cfg_map, pg);
//	for (int i = 0; i < 8; i++)
//	{
//		cout << pg.glints[i].x << " ";
//	}
//	cout << endl;
//
//	memset(pg.glints, -1, sizeof(pg.glints));
//	ReadConfigFile(cfgfilepath, cfg_map, pg);
//	for (int i = 0; i < 8; i++)
//	{
//		cout << pg.glints[i].y << " ";
//	}
//	cout << endl;
//
//	string s;
//	int a = 70;
//	s = to_string(a);
//	cout << s << endl;
//
//	//testMap();
//
//	//string path = "C:/Users/LiXiang/Desktop/R0.bmp";
//	//CombineImg(path.c_str(), path.c_str());
//
//	//Mat pngImg;
//	//string path = "C:/Users/LiXiang/Desktop/5.jpg";
//	//pngImg = imread(path,1);
//	//Mat grayImg;
//	//cvtColor(pngImg, grayImg, COLOR_BGR2GRAY);
//
//	////imshow("00", grayImg);
//	//imwrite("C:/Users/LiXiang/Desktop/grayOri.bmp", grayImg);
//
//	//cout << grayImg.rows << " " << grayImg.cols << endl;
//	//cv::Mat element5(3, 3, CV_8U, cv::Scalar(1));
//	//Mat dst;
//	//cv::morphologyEx(grayImg, dst, cv::MORPH_OPEN, element5);
//	//for (int i = 0; i < grayImg.rows; i++)
//	//{
//	//	for (int j = 0; j < grayImg.cols; j++)
//	//	{
//	//		if (grayImg.data[i*grayImg.cols + j] < 202 )
//	//		{
//	//			grayImg.data[i*grayImg.cols + j] = 0;
//	//		}
//	//		else
//	//		{
//	//			grayImg.data[i*grayImg.cols + j] = 255;
//	//		}
//	//	}
//	//}
//	//imshow("01", grayImg);
//	//imwrite("C:/Users/LiXiang/Desktop/gray1.bmp", grayImg);
//	//Mat close;
//	//Mat open;
//	//resize(grayImg,dst,Size(grayImg.cols * 2,grayImg.rows * 2));
//	//imshow("2", grayImg);
//	//imwrite("C:/Users/LiXiang/Desktop/ori.bmp", dst);
//	//cv::morphologyEx(dst, open, cv::MORPH_OPEN, element5);
//	//imwrite("C:/Users/LiXiang/Desktop/open.bmp", open);
//	//cv::morphologyEx(dst, close, cv::MORPH_CLOSE, element5);
//	//imwrite("C:/Users/LiXiang/Desktop/colse.bmp", close);
//
//	//Mat res2 = 0.5*close + 0.5*dst;
//	//Mat res;
//	//resize(res2, res, Size(grayImg.cols, grayImg.rows),0,0,0);
//	//imwrite("C:/Users/LiXiang/Desktop/res.bmp", res);
//	//
//	//imshow("1", res);
//	//waitKey(0);
//
//	//OnlyShowBuffer(200, 200, "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\TestImage\\LowBlur2330.pgm");
//	//char path[512];
//	//Rect r1;
//	//r1.x = 0;
//	//r1.y = 0;
//	//r1.width = 400;
//	//r1.height = 400;
//
//	//Rect r2;
//	//r2.x = 400;
//	//r2.y = 0;
//	//r2.width = 400;
//	//r2.height = 400;  
//
//	//if (argc > 0)
//	//{
//	//	vector<std::string> vct_files;
//	//	GetFilesByPath(argv[1], vct_files);
//
//	//	for (int i = 0; i < vct_files.size(); i++)
//	//	{
//	//		//sprintf(path, "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\Fd_Dsp3\\7\\%d.pgm", i);
//	//		SeparateImg(vct_files[i].c_str(), 800, 400, r1, r2);
//	//	}
//	//}
//	//else
//	//{
//	//	printf("no argv!\n");
//	//}
//	
//	//OnlyShowBuffer(480 / 7, 640 / 7, "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\TestImage\\MT640-2.bmp");
//	//OnlyShowBuffer(200, 256 , "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\src200-256.bmp");
//	//int a[8] = { 1,1,3,4};
//	//myFullArray(a,0,3);
//	//getint.d = 1;
//	//printf("%hhu,%hhu,%hhu,%hhu\n", getint.uc[0], getint.uc[1], getint.uc[2], getint.uc[3]);
//	//uint32_t stride = ( 130 + 127)&-128;
//	//cout << stride << endl;
//	system("pause");
//	return 0;
//}

int Convert2Bmp(int argc,char* argv[],int width,int height,int headLen)
{
	if (argc > 0)
	{
		vector<std::string> vct_files;
		GetFilesByPath(argv[1], vct_files);
		Mat dst(height , width, CV_8UC1);
		for (int i = 0; i < vct_files.size(); i++)
		{
			ReadBuffer(dst.data,width*height, vct_files[i].c_str(),headLen);
			string pathNew = argv[1] + string("/") + to_string(i) + ".bmp";
			imwrite(pathNew,dst);
		}
	}
	else   
	{
		printf("no argv!\n");
		return -1;
	}
	return 0;
}

int SumImage(const char* filePath)
{
	Mat src = imread(filePath, 0);
	int sum = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			sum += src.data[i *  src.cols + j];
			//sum += src.data[i *  src.cols];
			//printf("%d %d \n",i, (int)src.data[i *  src.cols]); 
		}
	}
	return sum;
}

int CutImage(const char* filePath,int x,int y,int width,int height)
{
	Mat src = imread(filePath, 0);
	Mat dst = src((Rect(x, y, width, height)));
	imshow("1", dst);
	waitKey();
	imwrite("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\cut.bmp", dst);
	return 0;
}

class A
{
public:
	A();
	A(int t);
	A(const A &a);
	void SetX(const A &a);
	//~A();
	int GetX();
private:
	int x;
};
A::A(int t)
{
	x = t;
}
A::A(const A &a)
{
	x = a.x;
}

void A::SetX(const A &a)
{
	x = a.x;
	return;
}
 
int A::GetX()
{
	return x;
}

int resize(const uint8_t *src, int srcHeight, int srcWidth, uint8_t *dst, int dstHeight, int dstWidth)
{
	if (src == nullptr || dst == nullptr)
	{
		return -1;
	}
	float hRatio = srcHeight * 1.0 / dstHeight;
	float wRatio = srcWidth * 1.0 / dstWidth;
	for (int i = 0; i < dstHeight; ++i)
	{
		for (int j = 0; j < dstWidth; ++j)
		{
			int sY = (i) * hRatio + 1;
			int sX = (j) * wRatio + 1;
			dst[i * dstWidth + j] = src[sY*srcWidth + sX];
		}
	}

	return 0;
}


struct node
{
	float pupilx;
	float pupily;
	EyeGlint glints[8];
};

//pupilx 483.272400 float
//pupily 135.935150 float
//- glints 0x0064d638 { {x = 496.923096 y = 154.769226 re = 1.00000000 }, { x = 505.771423 y = 109.914284 re = 1.00000000 }, ...} EyeGlint[8]
//+ [0]{ x = 496.923096 y = 154.769226 re = 1.00000000 } EyeGlint
//+ [1]{ x = 505.771423 y = 109.914284 re = 1.00000000 } EyeGlint
//+ [2]{ x = 454.272736 y = 184.193176 re = 1.00000000 } EyeGlint
//+ [3]{ x = 499.000000 y = 206.500000 re = 0.899999976 } EyeGlint
//+ [4]{ x = 449.500000 y = 208.500000 re = 0.899999976 } EyeGlint
//+ [5]{ x = 449.200012 y = 62.4000015 re = 0.899999976 } EyeGlint
//+ [6]{ x = 487.666687 y = 250.111115 re = 0.728999913 } EyeGlint
//+ [7]{ x = 0.000000000 y = 0.000000000 re = 0.000000000 } EyeGlint

void ClipPic(uint_fast8_t* pDstDataLeft, uint_fast8_t* pDstDataRight, const uint_fast8_t* pSrcData, int32_t nWidth, int32_t nHeight)
{
	for (int32_t i = 0; i < nHeight; i++)
	{
		memcpy(&pDstDataLeft[i * nWidth / 2], &pSrcData[i * nWidth], nWidth / 2);
		memcpy(&pDstDataRight[i * nWidth / 2], &pSrcData[i * nWidth + nWidth / 2], nWidth / 2);
	}
}

void CvClipPic(Mat& pDstDataLeft, Mat& pDstDataRight, const Mat pSrcData)
{
	pDstDataLeft = pSrcData(Rect(0, 0, 640, 480));
	pDstDataRight = pSrcData(Rect(640, 0, 640, 480));
}

void SIMDClipPic(uint_fast8_t* pDstDataLeft, uint_fast8_t* pDstDataRight, const uint_fast8_t* pSrcData, int32_t nWidth, int32_t nHeight)
{

	//(((unsigned long)(pSrcData) & 15) == 0) ? printf("src yes\n") : printf("src no\n");
	//(((unsigned long)(pDstDataLeft) & 15) == 0) ? printf("L yes\n") : printf("L no\n");
	//(((unsigned long)(pDstDataRight) & 15) == 0) ? printf("R yes\n") : printf("R no\n");

	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i += 16)
		{
			pSrcData += 16;
			auto data_src = vld1q_u8(pSrcData);
			if (i < nWidth / 2)
			{
				vst1q_u8(pDstDataLeft, data_src);
				pDstDataLeft += 16;
			}
			else
			{
				vst1q_u8(pDstDataRight, data_src);
				pDstDataRight += 16;
			}
		}
	}

	//auto data_src = vld1q_u8(pSrcData);
	//pSrcData += 16;
	//auto data_b = vld1q_u8(q[1]);
	//q[1] += 16;
	//auto result = vminq_u8(data_a, data_b);
	//for (int qi = 2; qi < se.height; qi++)
	//{
	//	auto data_c = vld1q_u8(q[qi]);
	//	q[qi] += 16;
	//	result = vminq_u8(result, data_c);
	//}
	//dstp = &mm[j];
	//vst1q_u8(dstp, result);
}

template <typename Key, typename Value>
class BST {

private:
	// 树中的节点为私有的结构体, 外界不需要了解二分搜索树节点的具体实现
	struct Node {
		Key key;
		Value value;
		Node *left;
		Node *right;

		Node(Key key, Value value) {
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}

		Node(Node *node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	Node t;
	//Node root(&t); // 根节点
	int count;  // 树中的节点个数
};

struct APICALL
{
	std::string isCall;
	std::string isSuccess;
	std::string apiName;
	APICALL(int str1, int str2, int str3)
	{
		isCall = str1;
		isSuccess = str2;
		apiName = str3;
	}
	APICALL(APICALL *api)
	{

	}
};

template <typename Key, typename Value>
class CLogParser {

private:
	std::string filename;


	int a = 0;
	APICALL t;
	//APICALL apiCall(&t);

};

extern int a;

int WriteCor(const char* path,PupilGlint pg)
{
	FILE *fp = fopen(path, "wb");
	if (fp == NULL)
	{
		printf("write cor erro\n");
		return -1;
	}
	fwrite(&pg, 1, sizeof(pg), fp);

	fclose(fp);
	return 0;
}

void test3arr(int a[][3][2])
{
	printf("test3arr %d\n",a[1][1][1]);
}

bool printfreset()
{
	freopen("test1.txt", "w", stdout);
	printf("test file\n");
	return true;
}

//全路径获取文件名
std::string GetNameByPath(const std::string path)
{
	size_t index = path.rfind('\\');
	return path.substr(index + 1);
}

int DataConvertBmp(int rows,int cols, const std::string path)
{
	Mat dst(rows, cols, CV_8UC1);
	std::vector<std::string> vctB;
	GetFilesByPath(path, vctB, "data");

	for (int i = 0; i < vctB.size(); i++)
	{
		ReadData(dst.data, dst.rows * dst.cols, vctB[i].c_str());
		std::string filename = vctB[i] + ".bmp";
		//FlippingBuffer(dst.data, rows, cols);
		imshow("dst", dst);
		imwrite(filename, dst);
	}
	return 0;
}

std::string DelNameByPath(const std::string path)
{
	size_t index = path.rfind('\\');
	return path.substr(0, index + 1);
}

//存相机图 回调
//std::shared_ptr<unsigned char> src(new unsigned char[1280 * 480]);
//memcpy(src.get(), image, 1280 * 480);
//PushCameraImageCall(3, src, 1280 * 480, 1280, 480, timestamp);

//前置相机RGB图像错帧检测
void ErrRGBFrameDetect()
{
	string path = "G:\\EyeImage\\agp3\\huatu\\11051758\\1\\AfterDetect\\";
	std::vector<std::string> vctB;
	string bmpPath = "G:\\EyeImage\\agp3\\huatu\\11051758\\1";
	GetFilesByPath(bmpPath, vctB, "bmp");

	for (int k = 0; k < vctB.size(); k++)
	{
		Mat src = imread(vctB[k], 1);
		int width = src.cols;
		int height = src.rows;
		int sumone = 0;
		int lastDif = 0;
		int dif[1280] = { 0 };
		for (int i = 1; i < 256; i++)
		{
			for (int j = 0; j < height; j++)
			{
				sumone += abs(src.data[3 * (j * width + i) + 1] - src.data[3*(j * width + i - 1) + 1]);
			}
			dif[i - 1] = sumone;
			if (i == 1)
			{
				lastDif = sumone;
			}
			else
			{
				if (abs(sumone - lastDif) > 3000)
				{
					//printf("error row = %d\n", i);
					//errCnt++;
					//if (errCnt > )
					{

						string filename = GetNameByPath(vctB[k]);
						string filepath = path + filename;
						DWORD dwError;

						//tools::cast::atow()
						if (CopyFile(vctB[k].c_str(), filepath.c_str(), FALSE)) {
							printf("Copy file succeeds. \n");
						}
						else {
							dwError = GetLastError();
							switch (dwError) {
							case ERROR_FILE_NOT_FOUND:
								printf("The source file does not exist. \n");
								printf("Error: %ld \n", dwError);
								break;
							default:
								printf("The new file already exists. \n");
								printf("Error: %ld \n", dwError);
								break;
							}
						}
						printf("%s\n", vctB[k].c_str());
						break;
					}
				}
				else
				{
					lastDif = sumone;
				}
			}
			sumone = 0;
		}
		//printf("1\n");
		//imshow("src", src);
		//waitKey();
	}
}

//图像错帧检测
void ErrFrameDetect()
{
	string path = "G:\\EyeImage\\agp3\\huatu\\11051427\\AfterDetect\\";

	std::vector<std::string> vctB;
	string bmpPath = "G:\\EyeImage\\agp3\\huatu\\11051427";
	GetFilesByPath(bmpPath, vctB, "bmp");

	for (int k = 0; k < vctB.size(); k++)
	{
		int errCnt = 0;
		Mat src = imread(vctB[k], 0);
		imshow("src", src);
		//waitKey();

		int width = src.cols;
		int height = src.rows;
		int sumone = 0;
		int lastDif = 0;
		int dif[480] = { 0 };
		unsigned char res[1280];
		unsigned short us16x8[8] = { 0 };
		for (int i = 1; i < height; i++)
		{
			for (int j = 0; j < 256; j += 16)
			{
				auto v0 = vld1q_u8(&src.data[(i - 1) * width + j]);
				auto v1 = vld1q_u8(&src.data[i * width + j]);
				auto resv = vabdq_u8(v1, v0);
				vst1q_u8(&res[j], resv);
				//sumone += abs(src.data[i * width + j] - src.data[(i - 1) * width + j]);
			}


			//for (int j = 0; j < 256; j++)
			//{
			//	sumone += res[j];
			//}

			memset(us16x8, 0, sizeof(us16x8));
			auto vres = vld1q_u16(us16x8);
			for (int j = 0; j < 256; j += 16)
			{
				auto v0_8x8 = vld1_u8(&res[j]);
				auto v1_8x8 = vld1_u8(&res[j + 8]);
				auto v_16x8 = vaddl_u8(v0_8x8, v1_8x8);
				vres = vaddq_u16(vres, v_16x8);
			}
			vst1q_u16(us16x8, vres);
			for (int j = 0; j < 8; j++)
			{
				sumone += us16x8[j];
			}

			dif[i - 1] = sumone;
			if (i == 1)
			{
				lastDif = sumone;
			}
			else
			{
				if (abs(sumone - lastDif) > 1000)
				{
					//printf("error row = %d\n", i);
					//errCnt++;
					//if (errCnt > )
					{

						string filename = GetNameByPath(vctB[k]);
						string filepath = path + filename;
						DWORD dwError;

						//tools::cast::atow()
						if (CopyFile(vctB[k].c_str(), filepath.c_str(), FALSE)) {
							printf("Copy file succeeds. \n");
						}
						else {
							dwError = GetLastError();
							switch (dwError) {
							case ERROR_FILE_NOT_FOUND:
								printf("The source file does not exist. \n");
								printf("Error: %ld \n", dwError);
								break;
							default:
								printf("The new file already exists. \n");
								printf("Error: %ld \n", dwError);
								break;
							}
						}
						printf("%s\n", vctB[k].c_str());
						break;
					}
				}
				else
				{
					lastDif = sumone;
				}
			}
			sumone = 0;
		}
	}
}


#ifdef __ANDROID__
#include <arm_neon.h>
#endif

#ifdef __ANDROID__
bool IsErrFrame(const unsigned char *image, int width, int height)
{
	int sumonce = 0;
	int lastDif = 0;
	int errCnt = 0;
	//    int dif[480] = {0};
	unsigned char res[1280];
	unsigned short us16x8[8] = { 0 };
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < 256; j += 16)
		{
			auto v0 = vld1q_u8(&image[(i - 1) * width + j]);
			auto v1 = vld1q_u8(&image[i * width + j]);
			auto resv = vabdq_u8(v1, v0);
			vst1q_u8(&res[j], resv);
			//sumone += abs(src.data[i * width + j] - src.data[(i - 1) * width + j]);
		}


		//for (int j = 0; j < 256; j++)
		//{
		//	sumone += res[j];
		//}

		memset(us16x8, 0, sizeof(us16x8));
		auto vres = vld1q_u16(us16x8);
		for (int j = 0; j < 256; j += 16)
		{
			auto v0_8x8 = vld1_u8(&res[j]);
			auto v1_8x8 = vld1_u8(&res[j + 8]);
			auto v_16x8 = vaddl_u8(v0_8x8, v1_8x8);
			vres = vaddq_u16(vres, v_16x8);
		}
		vst1q_u16(us16x8, vres);
		for (int j = 0; j < 8; j++)
		{
			sumonce += us16x8[j];
		}

		//        dif[i - 1] = sumonce;
		if (i == 1)
		{
			lastDif = sumonce;
		}
		else
		{
			if (abs(sumonce - lastDif) > 1000)
			{
				return true;
			}
			else
			{
				lastDif = sumonce;
			}
		}
		sumonce = 0;
	}
	return false;
}
#endif


#ifdef __ANDROID__
if (IsErrFrame(image, width, height))
{
	return;
}
#endif



bool SaveBmp1(const char * fileName, unsigned char *imgBuffer, int imWidth, int imHeight)
{
	if (!imgBuffer)
	{
		return 0;
	}
	int biBitCount = 8;
	int colorTablesize = 1024;	//灰度图像颜色表
	int lineByte = (imWidth * biBitCount / 8 + 3) / 4 * 4;
	FILE *fp = fopen(fileName, "wb");
	if (!fp)
	{
		return 0;
	}
	LBITMAPFILEHEADER filehead;
	filehead.bfType = 0x4D42;
	filehead.bfSize = sizeof(LBITMAPFILEHEADER) + sizeof(LBITMAPINFOHEADER) +
		colorTablesize + lineByte * imHeight;
	filehead.bfReserved1 = 0;
	filehead.bfReserved2 = 0;
	filehead.bfOffBits = 54 + colorTablesize;
	//写位图文件头进文件
	fwrite(&filehead, sizeof(LBITMAPFILEHEADER), 1, fp);

	//申请位图文件信息头结构变量， 填写文件信息头信息
	LBITMAPINFOHEADER infoHead;
	infoHead.biBitCount = biBitCount;
	infoHead.biClrImportant = 0;
	infoHead.biClrUsed = 0;
	infoHead.biSize = 40;
	infoHead.biWidth = imWidth;
	infoHead.biHeight = imHeight;
	infoHead.biPlanes = 1;
	infoHead.biCompression = 0;
	infoHead.biSizeImage = lineByte * imHeight;
	infoHead.biXPelsPerMeter = 0;
	infoHead.biYPelsPerMeter = 0;
	fwrite(&infoHead, sizeof(LBITMAPINFOHEADER), 1, fp);
	//fwrite(&filehead, sizeof(LBITMAPFILEHEADER), 1, fp);

	LRGBQUAD *pColorTable = new LRGBQUAD[256];

	for (int i = 0; i < 256; i++)
	{
		pColorTable[i].rgbBlue = i;
		pColorTable[i].rgbGreen = i;
		pColorTable[i].rgbRed = i;
		//pColorTable[i].rgbReserved = 0;
	}

	fwrite(pColorTable, sizeof(LRGBQUAD), 256, fp);


	//写位图数据进文件
	fwrite(imgBuffer, imHeight*lineByte, 1, fp);

	fclose(fp);
	return 1;
}

void MySaveBmp(const char *filename, unsigned char *rgbbuf, int width, int height)
{
	MyBITMAPFILEHEADER bfh;
	MyBITMAPINFOHEADER bih;
	/* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
	bfh.bfType = 0x4d42;
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = sizeof(MyBITMAPFILEHEADER) + sizeof(MyBITMAPINFOHEADER) + width * height * 3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(MyBITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = -height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	printf("filename=%s \n", filename);
	FILE *file = fopen(filename, "wb");
	if (!file)
	{
		printf("Could not write file\n");
		return;
	}

	/*Write headers*/
	fwrite(&bfh, sizeof(bfh), 1, file);
	fwrite(&bih, sizeof(bih), 1, file);

	fwrite(rgbbuf, width*height * 3, 1, file);
	fclose(file);
}

void ConvertRGBBmp(const char *imgPath, int width, int height, const char *dstPath)
{
	unsigned char *img = new unsigned char[width * height * 3];
	//Mat src(height, width, CV_8UC3);
	//ReadData(src.data, height * width * 3, imgPath);
	//imwrite(dstPath, src);

	ReadData(img, height * width * 3, imgPath);
	MySaveBmp(dstPath, img, width, height);

	delete[] img;
	return;
}

void ReadBMPHead(const char* path, MyBITMAPFILEHEADER* bfh, MyBITMAPINFOHEADER* bih)
{
	unsigned char tmp[1024];
	ReadData(tmp, sizeof(MyBITMAPFILEHEADER) + sizeof(MyBITMAPINFOHEADER), path);
	memcpy(bfh,tmp,sizeof(MyBITMAPFILEHEADER));
	memcpy(bih,tmp + sizeof(MyBITMAPFILEHEADER), sizeof(MyBITMAPINFOHEADER));
	printf("finish\n");
	return;
}

void pathConvert_Single2Double(string& s) {
	string::size_type pos = 0;
	while ((pos = s.find('\\', pos)) != string::npos) {
		s.insert(pos, "\\");
		pos = pos + 2;
	}
}


int main(int argc, char *argv[])
{
	//int x, y;
	//char ch0 = '\xff';
	//char ch1 = '\xf';
	//printf("%c,%c\n", ch0,ch1);
	//scanf("%2d%2d", &x, &y);
	//printf("%2d", x * y);

	//MyBITMAPFILEHEADER bfh,bfh2;
	//MyBITMAPINFOHEADER bih,bih2;
	//ReadBMPHead("G:\\EyeImage\\agp3\\huatu\\1\\dst\\img_01.bmp", &bfh, &bih);
	//ReadBMPHead("G:\\EyeImage\\agp3\\huatu\\1\\dst\\img_02.bmp", &bfh2, &bih2);

	//int a[2] = {};
	////int b[3] = {};
	//char b[2] = { 'B','M' };
	//printf("%d \n", *((short*)b));

	//string path = "G:\\EyeImage\\agp3\\huatu\\11051758";
	//std::vector<std::string> vctB;
	//GetFilesByPath(path, vctB, "data");

	//for (int i = 0; i < vctB.size(); i++)
	//{
	//	std::string dstname = vctB[i] + ".bmp";
	//	//FlippingBuffer(dst.data, rows, cols);
	//	ConvertRGBBmp(vctB[i].c_str(), 1280, 720, dstname.c_str());

	//}

	ErrRGBFrameDetect();


	//int a[5] = { 0 ,2,3,3,4 };
	//for (int i = 0; i < 5; i++)
	//{
	//	printf("%d\n", a[i]);
	//}

	//ErrFrameDetect();

	//PupilGlint pg;
	//float pgf[26];
	//ReadData((unsigned char*)&pg,sizeof(pgf),"G:\\EyeImage\\DspTest\\1_1564132931418697.cor");
	////memcpy(&pg, &pgf, sizeof(pgf));

	//double test;
	//memset(&test, 0, sizeof(test));
	//if (test == 0)
	//{
	//	printf("test success\n");
	//}

	//int arr[2][3][2] = { {(-1,1)} ,
	//					{{-4,4},{-5,5},{-6,6} }

	//				};
	//printf("%d, %d, %d,%d\n", arr[1][2][0], arr[1][2][1], arr[1][1][0],arr[1][1][1]);
	//test3arr(arr);

	//printf("%lf\n",atan2(1, -1) * 180.0 / M_PI);


	//PupilGlint pg;
	//float pgf[28] = { 268.489349, 294.830719, 250.399994, 255.199997, 1.000000, 229.333328, 264.666656, 0.409091, 191.142853, 235.857147, 0.729000 };
	//memcpy(&pg, &pgf, sizeof(pgf));
	//WriteCor("D:\\EyeImage\\pico\\PICO\\calibrationErr\\1.cor",pg);

	//double anh = 0.006724;
	//double antest = acos(0.9);
	//double ang = acos(anh);
	//double res = ang * 180.0 / M_PI ;
	//printf("%lf\n", res);
	//char ch = '\101';
	//char a = 1;
	//a = ~a; 
	//int s[8][8];
	//printf("%d %c\n", sizeof(s), ch);
	//const char* filePath = "F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\src.data";
	//Mat dst(68, 92, CV_8UC1);
	//ReadData(dst.data, 68 * 92, filePath);
	//imshow("dst", dst);
	//waitKey();

	//imwrite("F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\src.bmp", dst);

	//int rows = 480, cols = 640;
	//const char* filePath = "G:\\EyeImage\\DspTest\\crash\\crash.data";
	//Mat dst(rows, cols, CV_8UC1);
	////int t = dst.total();
	////printf(" t = %d, %d\n", 640*480,1 << 20);
	//ReadData(dst.data, rows * cols, filePath);
	////FlippingBuffer(dst.data, rows, cols);
	//imshow("dst", dst);
	//imwrite("G:\\EyeImage\\DspTest\\crash\\crash.bmp", dst);

	//filePath = "F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\dstData.data";
	//Mat dst1(68, 128, CV_8UC1);
	//ReadData(dst1.data, 68 * 128, filePath);
	//FlippingBuffer(dst1.data, 68, 128);

	//imshow("dst1", dst1);
	//imwrite("F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\dstData.bmp", dst1);
	
	//int rows = 480, cols = 640;
	//Mat dst(rows, cols, CV_8UC1);

	//std::string path = "G:\\EyeImage\\DspTest\\log\\1909201448\\ErrorImg";
	//std::vector<std::string> vctB;
	//GetFilesByPath(path, vctB, "data");

	//for (int i = 0; i < vctB.size(); i++)
	//{
	//	ReadData(dst.data, rows * cols, vctB[i].c_str());
	//	std::string filename = vctB[i] + ".bmp";
	//	//FlippingBuffer(dst.data, rows, cols);
	//	imshow("dst", dst);
	//	imwrite(filename, dst);
	//}




	//waitKey();

	//filePath = "F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\gls.data";
	//Mat dst2(61, 73, CV_8UC1);
	//ReadData(dst2.data, 61 * 73, filePath);
	//imwrite("F:\\secondwork\\lixiang\\NEW_FD\\WindowsNewFD\\image\\gls.bmp", dst2);

	//const char* filePath = "D:\\eyeImage\\DspTest\\dst1280-480.bmp";
	//Mat dst1(480, 640, CV_8UC1);
	//Mat dst2(480, 640, CV_8UC1);
	//Mat src = imread(filePath, 0);
	//double runtime;
	//LARGE_INTEGER Frequency;//计数器频率  
	//LARGE_INTEGER start_PerformanceCount;//起始计数器  
	//LARGE_INTEGER end_PerformanceCount;//结束计数器  
	//QueryPerformanceFrequency(&Frequency);
	////QueryPerformanceCounter(&start_PerformanceCount);

	////for (int i = 0; i < 100; i++)
	////{
	////	CvClipPic(dst1, dst2, src);
	////}
	////QueryPerformanceCounter(&end_PerformanceCount);

	////double runtime = (double)(end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart) * 1000 / (double)Frequency.QuadPart;
	////printf("Cv ClipPic runtime = %lf\n", runtime);

	//QueryPerformanceCounter(&start_PerformanceCount);

	////for (int i = 0; i < 100; i++)
	//{
	//	ClipPic(dst1.data, dst2.data, src.data, src.cols, src.rows);
	//}
	////for (int i = 0; i < 100; i++)
	////{
	////	CvClipPic(dst1, dst2, src);
	////}
	////for (int i = 0; i < 100; i++)
	////{
	////	SIMDClipPic(dst1.data, dst2.data, src.data, src.cols, src.rows);
	////}
	////imshow("dst1", dst1);
	////imshow("dst2", dst2);
	////waitKey();

	//QueryPerformanceCounter(&end_PerformanceCount);

	//runtime = (double)(end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart) * 1000 / (double)Frequency.QuadPart;
	//printf("Once ClipPic runtime = %lf\n", runtime);

	////ocl::setUseOpenCL(true);
	//double runtimetol = 0;
	//for (int i = 0; i < 100; i++)
	//{
	//	QueryPerformanceCounter(&start_PerformanceCount);
	//	{
	//		ClipPic(dst1.data, dst2.data, src.data, src.cols, src.rows);
	//	}
	//	QueryPerformanceCounter(&end_PerformanceCount);
	//	runtime = (double)(end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart) * 1000 / (double)Frequency.QuadPart;
	//	printf("ClipPic runtime = %lf\n", runtime);
	//	runtimetol += runtime;
	//}
	//printf("ClipPic runtimetol / 100 = %lf\n", runtimetol / 100);

	//PupilGlint et = { };
	//memset(&et, 0, sizeof(et));
	//float pgt[23] = { 483.272400, 135.935150, 496.923096, 154.769226, 1.000000, 505.771423, 109.914284, 1.000000, 454.272736, 184.193176, 1.000000,
	//	499.000000, 206.500000, 0.899999976, 449.500000, 208.500000, 0.899999976, 449.200012 ,62.4000015 ,0.899999976,487.666687 ,250.111115 ,0.728999913 };
	//memcpy(&et, pgt, sizeof(pgt));
	//FILE *fp = fopen(filePath, "wb");
	//fwrite(&et, sizeof(et), 1, fp);
	//fclose(fp);

	//filePath = "E:\\work\\SDK_Project\\bin\\x64\\P3_Release_NewVersion_ForASeeGlass\\20190524-114109\\src0.bmp";
	//Mat src = imread(filePath, 0);
	//imshow("0", src);
	//for (int i = 0; i < 480; i++)
	//{
	//	int x, y;
	//	x = i * 2;
	//	y = i * 2 + 1;
	//	for (int j = 0; j < 640; j++)
	//	{
	//		int a = j & 1;
	//		if (j & 1)
	//		{
	//			src.data[i * 640 + j] = x;
	//		}
	//		else
	//		{
	//			src.data[i * 640 + j] = y;
	//		}
	//	}
	//}
	//imwrite("E:\\work\\SDK_Project\\bin\\x64\\P3_Release_NewVersion_ForASeeGlass\\20190524-114109\\srcTest.bmp", src);

	//Mat dst(400,500,CV_8UC1);
	//resize(src.data, 480,640, dst.data,400,500);
	//imshow("1", dst);
	//waitKey();
	//imwrite("E:\\work\\SDK_Project\\bin\\x64\\P3_Release_NewVersion_ForASeeGlass\\20190524-114109\\dst.bmp", dst);

	//dst.total();
	//cv::resize(src, dst, cv::Size(500, 400), INTER_NEAREST);

	//imwrite("E:\\work\\SDK_Project\\bin\\x64\\P3_Release_NewVersion_ForASeeGlass\\20190524-114109\\dstcv.bmp", dst);
	//A a1(3);
	//A a2 = A(a1);
	//
	//cout << a2.GetX() << endl;

	//int sum = SumImage("E:\\work\\SDK_Project\\bin\\x64\\P3_Release_NewVersion_ForASeeGlass\\20190524-114109\\src0.bmp");
	//printf("sum = %d\n", sum);
	//FILE *f;
	//char fdatabuf[4000];
	//fopen_s(&f, "E:\\work\\AndroidProject\\SystemTest\\pico\\initFlashData1.dat", "rb");
	//fread_s(&fdatabuf, 4000, 4000, 1, f);
	//fclose(f);

	//Mat test(480, 640, CV_8UC1, Scalar(255));
	////for (int i = 0; i < test.rows; i++)
	////{
	////	for (int j = 0; j < test.cols; j++)
	////	{

	////		test.data[i * 640 + j] = (unsigned char)i;
	////	}
	////}
	//imwrite("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\test255.bmp", test);
	//Convert2Bmp(argc,argv,400,400,70);
	//int sum = SumImage("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\1crash.bmp");
	//CutImage("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\1crash.bmp", 128, 0, 384, 480);
	//printf("%d\n", sum); //1687200  第一列2805

	system("pause");
	return 0;
}

inline int prePos(int m, int n, int index)
{   
	//找到前驱
	return (index%m)*n + index / m;
}

inline int nextPos(int m, int n, int index)
{
	return (index%n)*m + index / n;
}

void trans(unsigned char *matrix, int m, int n)
{
	int len = m * n;
	for (int i = 0; i< len; i++)
	{
		int pre = prePos(m, n, i), next = nextPos(m, n, i);
		//指针向两方向同时移动
		while (pre > i && next > i && pre != next && prePos(m, n, pre) != next)
		{
			pre = prePos(m, n, pre);
			next = nextPos(m, n, next);
		}
		if (pre < i || next < i)//此环已被处理过
			continue;
		int cur = i, val = matrix[i];
		pre = prePos(m, n, cur); 
		while (pre != i)//移动环中的元素
		{
			matrix[cur] = matrix[pre];
			cur = pre;
			pre = prePos(m, n, cur);
		}
		matrix[cur] = val;
	}
}

//int main()
//{
//	//unsigned char *vec = new unsigned char[4*4];
//	//int m = 4, n = 4;
//	//for (int i = 0; i < m*n; i++)
//	//{
//	//	vec[i] = i;
//	//}
//	//for (int i = 0; i< m; i++)//输出矩阵转置之前的值
//	//{
//	//	for (int j = 0; j < n; j++)
//	//		printf("%2d ", vec[i*n + j]);
//	//	cout << endl;
//	//}
//	//cout << endl;
//	//trans(vec, m, n);
//	//for (int i = 0; i< n; i++)//输出矩阵转置之后的值
//	//{
//	//	for (int j = 0; j< m; j++)
//	//		printf("%2d ", vec[i*m + j]);
//	//	cout << endl;
//	//}
//	int xx = 0;
//	int n = 0;
//	while (~scanf("%d",&n))
//	{
//		xx = 0;
//		while (n--)
//		{
//			int x = 0;
//			scanf("%d", &x);
//			xx ^= x;
//		}
//		printf("%d\n", xx);
//	}
//
//	system("pause");
//	return 0;
//}

void beifen()
{
	//char path3[256] = "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\Fd_Dsp3\\dsptestimg\\3\\2160.0800.A.679799226.00.bmp";
	//char path4[256] = "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\Fd_Dsp3\\dsptestimg\\4\\1_4_1527321286514025.bmp";
	//Mat dst(480, 640, CV_8UC1, Scalar(0));
	//Mat src3(480, 640, CV_8UC1, Scalar(0));
	//unsigned char dstdata[640 * 480 + 1078];
	//ReadData(dstdata, 640*480 + 1078,path4);
	//unsigned char BMPhead[1078];
	//unsigned char src[640 * 480];


	//ReadBmp(BMPhead, src, path3);

	//for (int i = 0; i < 1; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		getint.uc[j] = BMPhead[22 + j];
	//		printf("%hhu ", getint.uc[j]);
	//	}
	//	printf("\n%d\n", getint.d);
	//}
	//printf("\n%hhu\n", BMPhead[18]);

	//memcpy(dst.data,dstdata + 1078,640*480);
	//memcpy(src3.data, src, 640 * 480);

	//for (int i = 0; i < 640 * 50; i++)
	//{
	//	src3.data[i] = 255;
	//}

	//for (int i = 0; i < 640 * 50; i++)
	//{
	//	src[i] = 255;
	//}

	//imshow("src", src3);

	//WriteBmp((char*)BMPhead,(char*)src,640*480, "E:\\bmp\\3.bmp");

	//imshow("dst", dst);
	//imwrite("E:\\bmp\\2160.0800.A.679799226.00.bmp", dst);

	//int i_testStatic = 0;
	//while (i_testStatic++ < 10)
	//{
	//	printf("%d ", testStatic());
	//}
	//cout << endl;
	//char BMPhead[1078];
	//char src[640*480];
	//ReadBmp(BMPhead,src);
	//WriteBmp(BMPhead,src);

	//Mat src = cv::imread("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\3orig.bmp", 0);
	////Mat dst = src.clone();
	//Rect roi = Rect(303-128,184-128,256,256);
	//Mat dst = src(roi);
	//imshow("dst1",dst);
	//imwrite("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\3orig256.bmp", dst);
	//waitKey();
	//char BMPhead[1078];
	//char srcData[640*480];
	//char dstData[640 * 480];
	//char ansData[91*68];
	//unsigned char midMat[640 * 480];
	//ReadBmp(BMPhead, srcData);

	//int64 sumtime = 0;
	//calculator_plus_LowBlurDSP((unsigned char*)srcData,640*480,480,640,5,5,(unsigned char*)dstData,640*480,&sumtime,midMat,640*480);

	////memcpy(dst.data, dstData, 640 * 480);
	////imshow("dst", dst);
	////waitKey();
	//char path[1024] = "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\dst0.bmp";
	//WriteBmp(BMPhead, dstData,640*480,path);
	//char pathans[1024] = "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\ans111.bmp";

	//for (int i = 0; i < 68; i++)
	//{
	//	for (int j = 0; j < 91; j++)
	//	{
	//		//ansData[((67 - i) * 91) + j] = dstData[(i * 7 +2 )* 640 + (j * 7) + 2];
	//		ansData[(i * 91) + j] = dstData[(i * 7 + 2) * 640 + (j * 7) + 2];
	//	}
	//}

	//FlippingBuffer(ansData,68,91);

	//printf("%hhu,%hhu,%hhu,%hhu\n", BMPhead[2], BMPhead[3],BMPhead[4],BMPhead[5]);

	//BMPhead[2] = 98;
	//BMPhead[3] = 28;
	//BMPhead[4] = 0;

	//BMPhead[18] = 91;
	//BMPhead[19] = 0;
	//BMPhead[22] = 68;
	//BMPhead[23] = 0;
	//
	//char lowpath[512] = "C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\xloworig.bmp";
	//
	//char lowbuffer[68 * 91];
	//ReadBuffer(lowbuffer, 68 * 91, lowpath);
	//FlippingBuffer(lowbuffer, 68, 91);

	//Mat ans(68, 91, CV_8UC1, Scalar(0));
	//memcpy(ans.data, lowbuffer, 68 * 91);
	//imshow("001",ans);
	//imwrite("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\ansMat.bmp",ans);
	//waitKey();

	//WriteBmp(BMPhead, ansData, 6188, pathans);

	///*彩图转灰度图*/
	////Mat srcImage = cv::imread("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\3orig128.bmp", 1);
	////Mat grayImage;
	////cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	////imwrite("C:\\Qualcomm\\Hexagon_SDK\\3.3.3\\examples\\common\\calculator_c++14\\3orig128.bmp", grayImage);
	////imshow("11", grayImage);
	////waitKey();


	////int a[9] = { 1,2,3,4,5,6,7,8,9 };
	////transpose(a);
	////for (int i = 0; i < 3; i++)
	////{
	////	for (int j = 0; j < 3; j++)
	////	{
	////		cout << a[i * 3 + j] << " ";
	////	}
	////	cout << endl;
	////}
}

#ifdef PDAGP3
#define RAD 1.4//拟合圆半径最大值
#define CIRC_ERR 47//拟合圆半径最大误差(像点在圆外)
#define CIRC_ERR_MINUS (-82)//拟合圆半径最大误差(像点在圆内)
#define CROSS_POINT_MAX_DIST 0.070//直线交点最大误差的最大值
#define MULTPL_RAD	1.3
#define LIMIT_ANGLE	49//最大夹角
#define PAR	0.54
#define FIT_WEIGHT	10000

#define IRIS_K		6
static const Point3D IRIS_CAMO(0, 0, 0);
#define MAX_DIST_TO_IRIS	-1//光斑到瞳孔中心的最远距离

#define POI_DIST_L_G_MAX 500//直线交点到物点距离/直线交点到像点距离(最大值)
#define POI_DIST_L_G_MIN 80//直线交点到物点距离/直线交点到像点距离(最小值)
#define SIDE_MAX_MIN_RATIO_MAX 2.7//最大边长与最小边长比的最大值
#define SIDE_MAX_MIN_RATIO_MIN 0.6//最大边长与最小边长比的最小值
#define INNER_ANGLE_ERR_ABS	57//最大内角误差（绝对）
#define INNER_ANGLE_ERR_REL 1.7//最大内角误差（相对）
#define POI_L_G_ANGLE_MAX 180//直线交点与物点向量 和 直线交点与像点向量 最大夹角
#define POI_X_MAX	(0.7)
#define POI_X_MIN	(-0.7)
#define POI_Y_MAX	(30.3)
#define POI_Y_MIN	(20.2)
#define FIT_OUT_MAX	(40)
#define FIT_OUT_MIN	(13)
#define FIT_OUT_DIFF_MAX    (31)//fitting3差值最大值

#define VALID_GLINT_CNT_MIN	2
#define POI_REFER_X	(0)
#define POI_REFER_Y	(0)
#define MIN_COS_VALUE	0

#define POI_RANGE_X_MAX		(0.5)
#define POI_RANGE_X_MIN		(-0.5)
#define POI_RANGE_Y_MAX		(24.3)
#define POI_RANGE_Y_MIN		(23.2)
#endif