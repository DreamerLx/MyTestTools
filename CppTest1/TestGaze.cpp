//// test.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//#include "FDGaze.h"
//#include "CalibrationGaze.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "..\runlog\RunLog.h"
//#include "calibmath.h"
//#include <iostream>
//#include "devdata.h"
//typedef int int32_t;
//
//using namespace CalibrationGaze;
//
//template<typename T>
//struct FDGPoint
//{
//	T x, y;
//};
////
////struct EyeGlint
////{
////    float x;
////    float y;
////    float re;
////};
//
//struct RoiInfo
//{
//	FDGPoint<int32_t> pos;
//	int32_t width, height;
//};
//
//// 光斑点的数量
//#define GLINT_COUNT 8
///**
// * @brief 眼睛特征
// */
//struct EyeFeatureB
//{
//	int32_t reliablity;     // 置信度， 0-无效
//	RoiInfo	roi;				///< 眼睛区域
//
//	double pupilDiameter;		///< 瞳孔直径
//	FDGPoint<double> pupil;
//
//	EyeGlint		 glint[GLINT_COUNT];
//
//	FDGPoint<double> gazePoint;
//
//	double opt;
//};
////typedef struct devData{
////    int imgH;
////    int imgW;
////    int Rmax;
////    int Rmin;
////    int Vmax;
////    double ecthr_small;
////    double ecthr_large;
////
////    double kc0;
////
////    int vestmethod;
////
////    int rightorleft; //0:right, 1:left
////    int vzsign; //1: lights[:][2]>0; else -1
////    //double kappa[2]={0,0};
////
////    double smult;
////    double fc[2];
////    double cc[2];
////    double camckc[5];
////    double lights[nglints][3];
////
////    double lightsth[nglints];
////
////
////    double lights2D[nglints][2];
////
////    double lightsdis2D[nglints];
////
////    double auxCoeff[12];
////} *pDevData;
//
//int vest(EyeFeature eye, const vestPara &vpara, double &vx, double &vy, int method, const pDevData pPara);
//int vestq(EyeFeature eye, const vestPara &vpara, double &vx, double &vy, int method, const pDevData pPara, Point3D* ppp);
//
//int main(int argc, char* argv[])
//{
//	PupilGlint pRef, pTest;
//	//example for calculation
//	////double da[29] =  {217.6337, 177.6827, 234.8421, 136.6842, 0.9735, 188.8667, 140.4667, 1.0000, 261.6429, 197.3571, 0.9997, 263.8636, 159.0000, 1.0000, 164.7826, 165.9130, 1.0000, 241.1379, 228.4138, 0.9976, 165.0000, 203.1739, 1.0000, 187.7500, 230.5000, 0.9734, 756.0000, 840.0000, 41.0000};
//	//double dp[29] =  {164.586517333984,168.820236206055,136.500000000000,155.500000000000,1,138.125000000000,193.062500000000,0.976966559886932,161.149993896484,219.750000000000,0.995026290416718,219.960006713867,223.759994506836,0.989861011505127,244.277770996094,191.899993896484,0.938399910926819,249.600006103516,146.800003051758,1,146,262,0.732903718948364,0,0,0,479,840,2};
//	//float Refimage[29] = { 217.6337, 177.6827, 234.8421, 136.6842, 0.9735, 188.8667, 140.4667, 1.0000, 261.6429, 197.3571, 0.9997, 263.8636, 159.0000, 1.0000, 164.7826, 165.9130, 1.0000, 241.1379, 228.4138, 0.9976, 165.0000, 203.1739, 1.0000, 187.7500, 230.5000, 0.9734, 756.0000, 840.0000, 41.0000 };
//	//float Testimage[29] = { 164.586517333984, 168.820236206055, 136.500000000000, 155.500000000000, 1, 138.125000000000, 193.062500000000, 0.976966559886932, 161.149993896484, 219.750000000000, 0.995026290416718, 219.960006713867, 223.759994506836, 0.989861011505127, 244.277770996094, 191.899993896484, 0.938399910926819, 249.600006103516, 146.800003051758, 1, 146, 262, 0.732903718948364, 0, 0, 0, 479, 840, 2 };
//
//	////initialize the pTest.glints 
//	//pRef.pupilx = Refimage[0];
//	//pRef.pupily = Refimage[1];
//	//memcpy(pRef.glints, Refimage + 2, sizeof(float)* 24);
//
//	//// initialize the pTest.glints
//	//pTest.pupilx = Testimage[0];
//	//pTest.pupily = Testimage[1];
//	//memcpy(pTest.glints, Testimage + 2, sizeof(float)* 24);
//
//
//
//	//const int Nd = 1;
//	void* pGazePara = NULL;
//	//CalibrationGaze::InitGazeEstimation(0, 5, pGazePara);
//	//vestPara pareye = vestPara();
//	//EyeFeature eye;
//	//memcpy(eye.pg, &pRef, sizeof(float)* 26);
//	//int key = CalibrationGaze::cglintsKeyPoint(eye, pGazePara);
//
//	const int N = 90;
//	FILE *f;
//	EyeFeature e[N];
//	double v[N][3] = { 0 };
//	vestPara vp;
//	vp.kappa[0] = 0;
//	vp.kappa[1] = 0;
//	vp.R = 7.8;
//	vp.K = 5.7;
//	vp.n = 1.3375;
//	vp.backoff = 1.0;
//	void * pSmoothPara = 0;
//	//	void * pGazePara=0;
//	gazeCalData ca;
//	gazeEstData ge;
//	GazeFeature gf;
//	gazeSelectData gs;
//	EyeCalCoe ec;
//
//	InitSmooth(0.028, 13, -0.0001, 1300, pSmoothPara);
//	InitGazeEstimation(1, 5, pGazePara);
//
//	char fdatabuf[4000];
//	fopen_s(&f, "D:\\temp\\initFlashData1.dat", "rb");
//	fread_s(&fdatabuf, 4000, 4000, 1, f);
//	fclose(f);
//	InitFlashData(fdatabuf, pGazePara);
//
//	//fopen_s(&f, "D:\\temp\\gazeSelectGazeData_b2_3.dat", "rb");
//	////fwrite(pGazePara, sizeof(devData), 1, f);
//	//memset(pGazePara, 0, sizeof(devData));
//	//fread_s(pGazePara, sizeof(devData)* 1, sizeof(devData), 1, f);
//	//fclose(f);
//
//	//fopen_s(&f, "D:\\temp\\gazeSelectData2_1552286348922406.dat", "rb");
//	//fread_s(&gs, sizeof(gazeSelectData), sizeof(gazeSelectData), 1, f);
//	//fclose(f);
//
//	//int rrrr = Selection(gs, pGazePara);
//	//int r = GazeEstimation(ge, gf, pGazePara);
//	int tsize = sizeof(struct devData);
//
//	fopen_s(&f, "D:\\temp\\gazeCalibrationData_e1.dat", "rb");// e3 is right after cal
//	//fread_s(&ec, sizeof(EyeCalCoe), sizeof(EyeCalCoe), 1, f);
//	fread_s(&ca, sizeof(gazeCalData), sizeof(gazeCalData), 1, f);
//	fclose(f);
//	//ca.coeff.vp.K = 5.4;
//	//LARGE_INTEGER nFreq;
//	//LARGE_INTEGER nBeginTime;
//	//LARGE_INTEGER nEndTime;
//	//double time;
//	//QueryPerformanceFrequency(&nFreq);
//
//	//QueryPerformanceCounter(&nBeginTime);
//	//ca.coeff.vp.K = 4.2;
//	for (int k = 0; k < N; k++)
//	{
//		//printf("\n[%d]", k);
//		v[k][2] = vest(ca.eyes[k], ca.coeff.vp, v[k][0], v[k][1], 5, (pDevData)pGazePara);
//	}
//	//中间写测试函数
//	//QueryPerformanceCounter(&nEndTime);
//	//time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	//std::cout << "time is " << time << std::endl;
//	//ca.calNum = 2;
//	//ca.totalNum = 10;
//	ca.finalCal = 1;
//	//return 0;
//	//memset(&ca.coeff, 0, sizeof(ca.coeff));
//	Calibration(ca, pGazePara);
//	for (int k = 0; k < N; k++)
//	{
//		//printf("\n[%d]", k);
//		v[k][2] = vest(ca.eyes[k], ca.coeff.vp, v[k][0], v[k][1], 5, (pDevData)pGazePara);
//	}
//	EyeFeature teye = { 325.604797, 221.317368, 310.000000, 215.666656, 1.000000, 364.533325, 215.733337, 1.000000, 283.214294, 237.500000, 1.000000, 395.868408, 239.631577, 0.900000, 286.500000, 285.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 77.000000, 0.000000, 0.000000 };
//	//EyeFeature teye = { 281.787231, 194.585114, 242.000000, 200.000000, 1.000000,271.666687, 176.125000, 1.000000, 245.615387, 245.615387, 1.000000, 332.243225, 175.027023, 0.900000, 274.842102, 262.157898, 1.000000, 367.592590, 200.740738, 1.000000, 333.405396, 263.540527, 0.900000,  0.000000, 0.000000, 0.000000, 84.000000, 0.000000, 0.000000 };
//	//ge.eye = ca.eyes[0];
//	//ge.coeff = ca.coeff;
//	//int tg1 = GazeEstimation(ge, gf, pGazePara);
//
//	//fopen_s(&f, "D:\\temp\\gazeEstData_B2_1528783622659318.dat", "rb");// e3 is right after cal
//	//fread_s(&ge, sizeof(ge), sizeof(ge), 1, f);
//	//fclose(f);
//	//ge.eye.pg[0].pupily = 223;
//	//int tg = GazeEstimation(ge, gf, pGazePara);
//
//	//ge.eye = ca.eyes[25];
//	//ge.coeff = ca.coeff;
//	//GazeEstimation(ge, gf, pGazePara);
//
//	//ge.eye.timestamp = 1;;
//
//	//GazeFeature pm;
//	//ge.coeff = ca.coeff;
//	//ge.eye = ca.eyes[11];
//	//int sdfa = GazeEstimation(ge, pm, pGazePara);
//   /* fopen_s(&f, "D:\\temp\\d\\BaseCoe3.dat", "rb");
//	fread_s(&(ca.coeff),sizeof(ca.coeff),sizeof(ca.coeff),1,f);
//	fclose(f);*/
//
//	//   if (argc == 1)
//	//   {
//	//
//	//       printf("path?\n");
//	//       return 0;
//	//      }
//
//	//   fopen_s(&f, argv[1], "rb");
//
//	//   //fopen_s(&f, "D:\\work\\Project\\CalibrationGaze\\Debug\\b.dat", "rb");
//	//   Point3D tpp[16];
//	//   
//	//   double lights[8][3];
//	//   double vx, vy;
//	//   fread_s(tpp, sizeof(double)* 48, sizeof(double), 48, f);
//	//   fread_s(((pDevData)pGazePara)->lights, sizeof(double)* 24, sizeof(double), 24, f);
//	//   fread_s(&vp.R, sizeof(double), sizeof(double), 1, f);
//	//   fclose(f);
//
//	//   int rrq = vestq(e[1], vp, vx, vy, 3, (pDevData)pGazePara, tpp);
//
//	//   if (rrq)
//	//   {
//	//       printf("no solution\n");
//	//       return 0;
//	//   }
//	//   else
//	//   {
//	//       printf("%f, %f\n", vx, vy);
//	//       return 0;
//	//   }
//
//	fopen_s(&f, "D:\\temp\\t.dat", "rb");
//	for (int k = 0; k < N; k++)
//	{
//		fread_s(&(ca.eyes[k].pg), sizeof(PupilGlint) - sizeof(float) * 5, sizeof(PupilGlint) - sizeof(float) * 5, 1, f);
//		fread_s(&(ca.eyes[k].pg[0].Ex), sizeof(float) * 3, sizeof(float) * 3, 1, f);
//		/*fread_s(&(e[k].pg), sizeof(PupilGlint)-sizeof(float)* 5, sizeof(PupilGlint)-sizeof(float)* 5, 1, f);*/
//		//fread_s(&(e[k].pg[0].Ex), sizeof(float)* 3, sizeof(float)* 3, 1, f);
//	}
//	fclose(f);
//
//	// vp.R = 7.0;
//	//vp.K = 4.8*vp.R / 7.8;;
//	for (int k = 0; k < N; k++)
//	{
//		//e[k].gaze.x /= 1280;
//		//e[k].gaze.y /= 1440;
//
//		//!!below because data is 640 and program is 320, normally no use
//		//ca.eyes[k].pg[0].pupilx /= 2.0;
//		//ca.eyes[k].pg[0].pupily /= 2.0;
//		//for (int l = 0; l < 8; l++)
//		//{
//		//    ca.eyes[k].pg[0].glints[l].x /= 2.0;
//		//    ca.eyes[k].pg[0].glints[l].y /= 2.0;
//		//}
//		//ge.eye = ca.eyes[k];
//		//ge.coeff = ca.coeff;
//		//GazeFeature pm;
//		//GazeEstimation(ge, pm, pGazePara);
//		//printf("%d,\n", pm.Nglints);
//		//v[k][2] = vest(ca.eyes[k], vp, v[k][0], v[k][1], 5, (pDevData)pGazePara);
//		//v[k][2] = vest(ca.eyes[k], ca.coeff.vp, v[k][0], v[k][1], 3, (pDevData)pGazePara);
//	}
//	ca.finalCal = 1;
//	ca.calNum = 1;
//	ca.totalNum = 10;
//	ca.frameNum = 10;
//	//memcpy(ca.eyes, ca.eyes + 80, sizeof(EyeFeature)* 20);
//	Calibration(ca, pGazePara);
//
//	//fclose(f);
//
//	//ge.eye = e[0];
//	//ge.coeff = ca.coeff;
//
//	//int pos[9][2] = {{401,500},{400,449},{0,49},{100,149},{300,349},{350,399},{250,299},{150,199},{50,99}};
//	int pos[9][2] = { {55,74},{0,9},{82,92},{10,19},{20,29},{30,40},{51,61},{62,71},{72,81} };
//	char szPath[256] = { 0 };
//
//	memset(&ca, 0, sizeof(gazeCalData));
//	for (int i = 0; i <= 8; i++)
//	{
//		gazeSelectData se;
//		memset(&se, 0, sizeof(gazeSelectData));
//		se.selectNum = 10;
//		se.totalNum = pos[i][1] - pos[i][0] + 1;
//		memcpy(se.eyes, e + pos[i][0], (pos[i][1] - pos[i][0] + 1) * sizeof(EyeFeature));
//		Selection(se, pGazePara);
//		memcpy(ca.eyes + i * 10, se.eyes, 10 * sizeof(EyeFeature));
//	}
//	//fopen_s(&f,"D:\\temp\\debug_cal1C2GData2.dat","rb");
//	////fread_s(&(ca.coeff),sizeof(ca.coeff),sizeof(ca.coeff),1,f);
//	////fclose(f);
//	//fread_s(&(ca),sizeof(ca),sizeof(ca),1,f);
//	//fclose(f);
//
//	//fopen_s(&f,"D:\\temp\\debug_cal1C2GData.dat","rb");
//	//fread_s(&(ca),sizeof(ca),sizeof(ca),1,f);
//	//fclose(f);
//	ca.calNum = 1;
//	ca.frameNum = 10;
//	ca.totalNum = ca.calNum*ca.frameNum;
//	Calibration(ca, pGazePara);
//
//	//ge.eye = ca.eyes[15];
//	//ge.coeff = ca.coeff;
//	//GazeEstimation(ge);
//	//for( int k =0;k<N;k++)
//	//{
//	//	v[k][2] = vest(e[k],ca.coeff.vp, v[k][0],v[k][1],3);
//	//}
//
//
//
//	//ca.calNum = 3;
// //   ca.totalNum = ca.calNum*ca.frameNum;
//	//Calibration(ca, pGazePara);
//	//	ge.eye = ca.eyes[45];
//	//ge.coeff = ca.coeff;
//	//GazeEstimation(ge, pGazePara);
//	float  re;
//	SmoothGaze(ge, ge.eye.gaze, re, (unsigned long long)1000, pSmoothPara, 0);
//	//ca.calNum = 5;
// //   ca.totalNum = ca.calNum*ca.frameNum;
//	//Calibration(ca, pGazePara);
//	//ca.calNum = 9;
// //   ca.totalNum = ca.calNum*ca.frameNum;
//	//Calibration(ca, pGazePara);
//	//ge.eye = ca.eyes[45];
//	//ge.coeff = ca.coeff;
//	//GazeEstimation(ge, pGazePara);
//	//SmoothGaze(ge, ge.eye.gaze,re,10,pSmoothPara);
//
//
//
//
//
//	//fopen_s(&f,"D:\\temp\\t.dat","rb");
//	//for (int k = 0; k<17; k++)
//	//{
//	//	fread_s(&(ge.eye),sizeof(EyeFeature)*1,sizeof(EyeFeature),1,f);
//	//	GazeEstimation(ge, pGazePara);
//	//	printf("%f,%f\n", ge.eye.gaze.x, ge.eye.gaze.y);
//	//}
//
//
//
//	ca.calNum = 9;
//
//	//fopen_s(&f,"D:\\temp\\c.dat","wb");
//	//fwrite(&(ca.coeff),sizeof(EyeCalCoe),1,f);
//	//fclose(f);
//	//for (int i = 1; i <= 1; i++)
//	//{
//	//	for (int j = 1; j <= 20; j++)
//	//	{
//	//		EyeFeatureB feat;
//
//	//		//*{{ read binary file
//	//		sprintf_s(szPath, "%s/%d_%d.feat", "../Debug/feat", i, j);
//	//		FILE* pFile = fopen(szPath, "rb+");
//	//		if (NULL != pFile)
//	//		{
//	//			fseek(pFile, 0, SEEK_END);
//	//			int len = ftell(pFile);
//	//			fseek(pFile, 0, SEEK_SET);
//	//			int size = fread(&feat, sizeof(EyeFeatureB), 1, pFile);
//
//	//			fclose(pFile);
//	//		}
//
//	//	}
//	//}
//
//	//float gazex = 0.f, gazey = 0.f, gazesx = 0.f, gazesy = 0.f;
//
// //   char filename[128] = {0};
// //   for (int i = 0; i < 3600; i+=10)
// //   {
// //       sprintf_s(filename, "D:\\temp\\img\\%d_gaze.data", i);
//
// //       FILE* file = nullptr;
// //       fopen_s(&file, filename, "rb");
// //       if(file)
// //       {
// //           fread(&gazex, sizeof(float), 1, file);
// //           fread(&gazey, sizeof(float), 1, file);
// //           fread(&gazesx, sizeof(float), 1, file);
// //           fread(&gazesy, sizeof(float), 1, file);
//
// //           fclose(file);
//
// //           std::cout << i << ": " << gazex << ", " << gazey << ", " << gazesx << ", " << gazesy << std::endl;
// //       }
// //   }
//
//	return 0;
//}
//
//
