constexpr int BUFFER_LENGTH = 1024;

/**
 * 获取指定目录中的所有文件的绝对路径(递归)
 *
 * @param path 指定的查找目录的绝对路径
 * @fullPathNames
 * 
 * @return int 文件的数量 >= 0 表示成功, -1表示失败
 */
int  GetFilePathRecursive(const std::string& path, std::vector<std::string>& fullPathNames)
{
	WIN32_FIND_DATAA FindData;
	HANDLE hFileSearch;
	int FileCount = 0;
	char FilePathName[BUFFER_LENGTH];
	char FullPathName[BUFFER_LENGTH];
	strcpy_s(FilePathName, path.c_str());
	strcat_s(FilePathName, "\\*.*");
	hFileSearch = FindFirstFileA(FilePathName, &FindData);
	if (hFileSearch == INVALID_HANDLE_VALUE) 
	{
		std::cout << "Open file handle error !!!" << std::endl;
		return -1;
	}

	while (::FindNextFileA(hFileSearch, &FindData)) 
	{
		if (strcmp(FindData.cFileName, ".") == 0
			|| strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}

		sprintf_s(FullPathName, "%s\\%s", path.c_str(), FindData.cFileName);
		FileCount++;
		fullPathNames.push_back(FullPathName);

		if (FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) 
		{
			std::cout << "<DIR>" << std::endl;
			int res = GetFilePathRecursive(FullPathName, fullPathNames);
			if (res >= 0)
			{
				FileCount += res;
			}
			else
			{
				return -1;
			}
		}
	}

	return FileCount;
}
