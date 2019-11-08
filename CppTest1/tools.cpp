#include "tools.h"
#include <io.h>
#include <memory>
//namespace tools
//{
//
//	std::string cast::wtoa(const CString& cstr)
//	{
//		std::string str;
//
//		//获取宽字节字符的大小，大小是按字节计算的
//		int len = WideCharToMultiByte(CP_ACP, 0, cstr, cstr.GetLength(), NULL, 0, NULL, NULL);
//
//		//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
//		std::shared_ptr<char> buf(new char[len + 1]);
//
//		if (buf.get() != nullptr)
//		{
//			//宽字节编码转换成多字节编码
//			WideCharToMultiByte(CP_ACP, 0, cstr, cstr.GetLength(), buf.get(), len, NULL, NULL);
//
//			buf.get()[len] = '\0';
//
//			str = buf.get();
//		}
//
//		return str;
//	}
//
//	CString cast::atow(const std::string& str)
//	{
//		CString cstr;
//
//		int charLen = str.length();//计算char *数组大小，以字节为单位，一个汉字占两个字节
//
//		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), charLen, NULL, 0);//计算多字节字符的大小，按字符计算。
//
//		std::shared_ptr<TCHAR> buf(new TCHAR[len + 1]);
//		//TCHAR *buf = new TCHAR[len + 1];//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
//		if (buf.get() != nullptr)
//		{
//			MultiByteToWideChar(CP_ACP, 0, str.c_str(), charLen, buf.get(), len);//多字节编码转换成宽字节编码
//			buf.get()[len] = _T('\0');
//
//			cstr.Append(buf.get());
//		}
//
//		return cstr;
//	}
//	//#endif // !_ATL
//
//	std::string cast::wtoa(const wchar_t* wchar, int32_t wlen)
//	{
//		return std::string("");
//	}
//
//	void cast::atow(const std::string& str, wchar_t* wchar, int32_t wlen)
//	{
//
//	}
//
//	std::string cast::UTF8toASCII(const std::string& UTF8)
//	{
//		int nwLen = MultiByteToWideChar(CP_UTF8, 0, UTF8.c_str(), -1, NULL, 0);
//
//		std::shared_ptr<wchar_t> wbuf(new wchar_t[nwLen + 1]);
//		memset(wbuf.get(), 0, nwLen * 2 + 2);
//
//		MultiByteToWideChar(CP_UTF8, 0, UTF8.c_str(), UTF8.length(), wbuf.get(), nwLen);
//
//		int nLen = WideCharToMultiByte(CP_ACP, 0, wbuf.get(), -1, NULL, NULL, NULL, NULL);
//
//		std::shared_ptr<char> buf(new char[nLen + 1]);
//		memset(buf.get(), 0, nLen + 1);
//
//		WideCharToMultiByte(CP_ACP, 0, wbuf.get(), nwLen, buf.get(), nLen, NULL, NULL);
//
//		std::string str(buf.get());
//
//		return str;
//	}
//
//	std::string cast::ASCIItoUTF8(const std::string& ASCII)
//	{
//		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, ASCII.c_str(), -1, NULL, 0);
//
//		std::shared_ptr<wchar_t> wbuf(new wchar_t[nwLen + 1]);
//		memset(wbuf.get(), 0, nwLen * 2 + 2);
//
//		::MultiByteToWideChar(CP_ACP, 0, ASCII.c_str(), ASCII.length(), wbuf.get(), nwLen);
//
//		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, wbuf.get(), -1, NULL, NULL, NULL, NULL);
//
//		std::shared_ptr<char> buf(new char[nLen + 1]);
//		memset(buf.get(), 0, nLen + 1);
//
//		::WideCharToMultiByte(CP_UTF8, 0, wbuf.get(), nwLen, buf.get(), nLen, NULL, NULL);
//
//		std::string strUTF8(buf.get());
//
//		return strUTF8;
//	}
//
//	std::string cast::UnicodeToUTF8(CString unicode)
//	{
//		std::string str;
//		int len = 0;
//		len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)unicode.GetBuffer(), -1, NULL, 0, NULL, NULL);
//		char* pUtf8 = new char[len + 1];
//		if (nullptr != pUtf8)
//		{
//			memset(pUtf8, 0, len + 1);
//			WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)unicode.GetBuffer(), -1, pUtf8, len, NULL, NULL);
//			pUtf8[len] = '\0';
//			str.append(pUtf8);
//			delete pUtf8;
//			pUtf8 = nullptr;
//		}
//		return str;
//	}
//
//	CString cast::UTF8ToUnicode(const char* pUTF8)
//	{
//		CString cstr;
//		int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, NULL, 0);
//		wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
//
//		if (nullptr != pUnicode)
//		{
//			MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, (LPWSTR)pUnicode, unicodeLen);
//			pUnicode[unicodeLen] = _T('\0');
//			cstr.Append(pUnicode);
//			delete pUnicode;
//			pUnicode = nullptr;
//		}
//
//		return cstr;
//	}
//
//
//	//获取路径下所有文件
//	size_t GetFilesByPath(const std::string &path, std::vector<std::string>& vct_files, std::string ext)
//	{
//		long long hFile = 0;
//		struct _finddata_t fileinfo;
//		std::string p;
//		std::string name;
//		std::string ext_name;
//		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
//		{
//			do
//			{
//				name = std::string(fileinfo.name);
//				if (fileinfo.attrib & _A_SUBDIR)
//				{
//					if (name != "." && name != "..")
//					{
//						std::string newPath = path + "\\" + name;
//						GetFilesByPath(newPath, vct_files);
//					}
//				}
//				else
//				{
//					ext_name = name.substr(name.rfind('.') + 1);
//					if (ext != "")
//					{
//						if (ext_name == ext)
//						{
//							vct_files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//						}
//					}
//					else
//					{
//						vct_files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//					}
//				}
//			} while (_findnext(hFile, &fileinfo) == 0);
//			_findclose(hFile);
//		}
//		return vct_files.size();
//	}
//	//全路径获取文件名
//	std::string GetNameByPath(const std::string path)
//	{
//		size_t index = path.rfind('\\');
//		return path.substr(index + 1);
//	}
//
//	std::string DelNameByPath(const std::string path)
//	{
//		size_t index = path.rfind('\\');
//		return path.substr(0, index + 1);
//	}
//
//	//毫米转像素
//	void ToPixel(float gc[], double fc[], double cc[], float pixLights[])
//	{
//		pixLights[0] = static_cast<float>(gc[0] * fc[0] + cc[0]);
//		pixLights[1] = static_cast<float>(gc[1] * fc[1] + cc[1]);
//	}
//
//	void ToPixel(float gc[], float fc[], float cc[], float pixLights[])
//	{
//		pixLights[0] = gc[0] * fc[0] + cc[0];
//		pixLights[1] = gc[1] * fc[1] + cc[1];
//	}
//
//
//
//	std::string app_path(void)
//	{
//		std::string path;
//
//#if defined(_WINDOWS_)
//		char szName[MAX_PATH] = { 0 };
//		if (::GetModuleFileNameA(0, szName, MAX_PATH) > 0)
//		{
//			path = szName;
//			size_t pos = path.rfind('\\');
//			if (pos > 0)
//			{
//				path = path.substr(0, pos);
//			}
//		}
//#endif
//		return path;
//	}
//};
