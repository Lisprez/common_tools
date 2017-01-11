#include <string>
#include <algorithm>
#include <fstream>

// for use _mkdir
#include <io.h>
#include <stdio.h>
#include <direct.h>  
#include <stdlib.h>  

#include "../inc/decompress.hpp"


static int create_multi_level_dir(char* pDir)
{
	int i = 0;
	int iRet;
	std::size_t iLen;
	char* pszDir;

	if (NULL == pDir)
	{
		return 0;
	}

	pszDir = _strdup(pDir);
	iLen = strlen(pszDir);

	for (i = 0; i < iLen; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			iRet = _access(pszDir, 0);
			if (iRet != 0)
			{
				iRet = _mkdir(pszDir);
				if (iRet != 0)
				{
					return -1;
				}
			}
			pszDir[i] = '/';
		}
	}

	iRet = _mkdir(pszDir);
	free(pszDir);
	return iRet;
}

bool Extract_Zip_File(const std::string& src_file)
{
	ziputils::unzipper zipFile;
	if (zipFile.open(src_file.c_str())) 
	{
		std::string dir_name = src_file.substr(0, src_file.length() - 4);
		if (_mkdir(dir_name.c_str()) == 0) 
		{
			auto filenames = zipFile.getFilenames();
			for (auto it = filenames.begin(); it != filenames.end(); it++) 
			{
				std::string item = *it;
				std::ofstream middleFile;
				std::size_t index = item.rfind("/");
				// 表示有子目录
				if (index != std::string::npos) 
				{
					std::string sub_folder = item.substr(0, index);
					std::replace(sub_folder.begin(), sub_folder.end(), '/', '\\');
					std::string full_folder = dir_name + "\\" + sub_folder;
					char folder[128];
					memset(folder, 0, sizeof(folder));
					strncpy(folder, full_folder.c_str(), 128);
					// 先创建这个多级目录
					create_multi_level_dir(folder);

					std::replace(item.begin(), item.end(), '/', '\\');
					middleFile.open((dir_name + "\\" + item).c_str(), std::ostream::binary);
				}
				// 表示根目录项目
				else 
				{
					middleFile.open((dir_name + "\\" + item).c_str(), std::ostream::binary);
				}
				// 将项目对应的数据写到临时文件中去
				if (zipFile.openEntry((*it).c_str())) 
				{
					zipFile >> middleFile;
					middleFile.close();
				}
				else 
				{
					zipFile.close();
					return false;
				}
			}
			zipFile.close();
			return true;
		}
		else 
		{
			zipFile.close();
			return false;
		}
	}
	else 
	{
		return false;
	}
}
