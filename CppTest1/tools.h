//
// Created by LiXiang on 2018/12/15.
//

#ifndef SYSTEMTEST_TOOLS_H
#define SYSTEMTEST_TOOLS_H

#include <string>
#include <sstream>
#include <vector>
//#include <afx.h>

using namespace std;

template <class Type>
float stringToNum(const string& str)
{
	istringstream iss(str);
	float num;
	iss >> num;
	return num;
}
//namespace tools
//{
//	struct cast
//	{
//		static std::string wtoa(const CString& cstr);
//
//		static CString atow(const std::string& str);
//
//		static std::string wtoa(const wchar_t* wchar, int32_t wlen);
//
//		static void atow(const std::string& str, wchar_t* wchar, int32_t wlen);
//
//		static std::string UTF8toASCII(const std::string& UTF8);
//
//		static std::string ASCIItoUTF8(const std::string& ASCII);
//
//		static std::string UnicodeToUTF8(CString unicode);
//
//		static CString UTF8ToUnicode(const char* pUTF8);
//	};
//
//	//��ȡ·���������ļ�
//	size_t GetFilesByPath(const std::string &path, std::vector<std::string>& vct_files, std::string ext = "");
//	//ȫ·����ȡ�ļ���
//	std::string GetNameByPath(const std::string path);
//	//ȫ·��ȥ���ļ���
//	std::string DelNameByPath(const std::string path);
//
//	//����ת����
//	void ToPixel(float gc[], double fc[], double cc[], float pixLights[]);
//	void ToPixel(float gc[], float fc[], float cc[], float pixLights[]);
//
//
//	//��ȡӦ�ó���·��
//	std::string app_path(void);
//
//
//};


#endif //SYSTEMTEST_TOOLS_H
