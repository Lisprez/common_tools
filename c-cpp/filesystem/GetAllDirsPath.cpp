constexpr int BUFFER_LENGTH = 1024;
// return	-1: failed
// 			>=0: succeed
// 	return values stands for the target's size
int  GetAllDirsPath(const std::string& path, std::vector<std::string>& fullPathNames)
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

			int res = GetAllDirsPath(FullPathName, fullPathNames);
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