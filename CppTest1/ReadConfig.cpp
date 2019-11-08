//
// Created by LiXiang on 2018/12/15.
//
//#include "FDGazeVR.h"
//#include <tools.h>
#include "ReadConfig.h"
#include "tools.h"

int ReadConfigFile(const char * cfgfilepath, map<string, string> &cfg_map, PupilGlint &pg)
{
	fstream cfgFile;
	cfgFile.open(cfgfilepath);
	if (!cfgFile.is_open())
	{

		return -1;
	}

	char tmp[1000];
	while (!cfgFile.eof())//循环读取每一行
	{
		cfgFile.getline(tmp, 1000);//每行读取前1000个字符，1000个应该足够了
		string line(tmp);
		size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value
		if (pos != string::npos)
		{
			string tmpKey = line.substr(0, pos);//取=号之前
			string tmpValue = line.substr(pos + 1);

			unsigned int nSize = tmpValue.size();
			if (nSize > 0 && tmpValue[nSize - 1] == '\r')
			{
				tmpValue = tmpValue.substr(0, nSize - 1);
			}

			cfg_map[tmpKey] = tmpValue;
		}
		if (cfg_map["input"] == "1")
		{
			//cfgFile.getline(tmp, 1000);
			//line = tmp;
			if (line.find("{") == string::npos)
			{
				continue;
			}
			int i = 0;
			do
			{
				cfgFile.getline(tmp, 1000);
				line = tmp;

				pos = line.find(' ');//找到每行的“ ”号位置，之前是x之后是y
				if (pos != string::npos)
				{
					string tmpX = line.substr(0, pos);//取=号之前
					string tmpY = line.substr(pos + 1);
					unsigned int nSize = tmpY.size();
					if (nSize > 0 && tmpY[nSize - 1] == '\r')
					{
						tmpY = tmpY.substr(0, nSize - 1);
					}

					float x = stringToNum<float>(tmpX);
					float y = stringToNum<float>(tmpY);
					if (i == 0)
					{
						pg.pupilx = x;
						pg.pupily = y;
					}
					else
					{
						pg.glints[i - 1].x = x;
						pg.glints[i - 1].y = y;
					}
					i++;
				}
				
			} while (line.find("}") == string::npos);
		}
	}
	cfgFile.close();
	return 0;
}

//int ReadConfigFile(const char * cfgfilepath, map<string,string> &cfg_map,PupilGlint &pg)
//{
//    fstream cfgFile;
//    cfgFile.open(cfgfilepath);
//    if(!cfgFile.is_open())
//    {
//        //LOGE("can't open config");
//		printf("can't open config\n");
//        return -1;
//    }
//
//    char tmp[1000];
//	bool isEnd = false;
//    while(!isEnd)//循环读取每一行
//    {
//        cfgFile.getline(tmp,1000);//每行读取前1000个字符，1000个应该足够了
//        string line(tmp);
//        size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value
//        if(pos!=string::npos)
//        {
//            string tmpKey = line.substr(0,pos);//取=号之前
//            string tmpValue = line.substr(pos+1);
//            cfg_map[tmpKey] = tmpValue;
//        }
//        if(cfg_map["input"] == "1")
//        {
//            int i = 0;
//            do
//            {
//                cfgFile.getline(tmp,1000);
//                line = tmp;
//                if(line.find("{") != string::npos)
//                {
//                    continue;
//                }
//                pos = line.find(' ');//找到每行的“ ”号位置，之前是x之后是y
//                if(pos!=string::npos)
//                {
//                    string tmpX = line.substr(0,pos);//取=号之前
//                    string tmpY = line.substr(pos+1);
//                    float x = stringToNum(tmpX);
//                    float y = stringToNum(tmpY);
//                    if( i == 0)
//                    {
//                        pg.pupilx = x;
//                        pg.pupily = y;
//                    }
//                    else
//                    {
//                        pg.glints[i - 1].x = x;
//                        pg.glints[i - 1].y = y;
//                    }
//                    i++;
//                }
//            }while(line.find("}") == string::npos);
//        }
//		isEnd = cfgFile.eof();
//    }
//	cfgFile.close();
//	return 0;
//}
//
