constexpr int BUFFER_LENGTH = 1024;

/**
 * 获取一个指定目录下的所有目录的绝对路径
 *
 * @param path 指定的查找目录
 * @param fullPathNames
 *
 * @return int (其实这个返回值有些多余, 因为可以通过fullPathNames.size()获得), -1时表示失败, >=0 成功
 */
int  GetDirPathRecursive(const std::string& path, std::vector<std::string>& fullPathNames)
{
	WIN32_FIND_DATAA FindData;
	HANDLE hFileSearch;
	int DirCount = 0;
	char FilePathName[BUFFER_LENGTH];
	char FullPathName[BUFFER_LENGTH];
	strcpy_s(FilePathName, path.c_str());
	strcat_s(FilePathName, "\\*.*");
	hFileSearch = FindFirstFileA(FilePathName, &FindData);
	if (hFileSearch == INVALID_HANDLE_VALUE) {
		std::cout << "Open file handle error !!!" << std::endl;
		return -1;
	}

	while (::FindNextFileA(hFileSearch, &FindData)) {
		if (strcmp(FindData.cFileName, ".") == 0
			|| strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}

		if (FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) {
			sprintf_s(FullPathName, "%s\\%s", path.c_str(), FindData.cFileName);
			++DirCount;
			fullPathNames.push_back(FullPathName);

			int res = GetDirPathRecursive(FullPathName, fullPathNames);
			if (res >= 0)
			{
				DirCount += res;
			}
			else
			{
				return -1;
			}
		}
	}

	return DirCount;
}