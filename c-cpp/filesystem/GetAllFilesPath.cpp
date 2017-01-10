// return 	>= 0: succeed
// 			-1: failed
// support absoluate path and also relative path
constexpr int BUFFER_LENGTH = 1024;

int  GetAllFilesPath(const std::string& path, std::vector<std::string>& fullPathNames)
{
	WIN32_FIND_DATAA FindData;
	HANDLE hFileSearch;
	int FileCount = 0;
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

		sprintf_s(FullPathName, "%s\\%s", path.c_str(), FindData.cFileName);
		FileCount++;
		fullPathNames.push_back(FullPathName);

		if (FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) {
			std::cout << "<DIR>" << std::endl;
			int res = GetAllFilesFullPath(FullPathName, fullPathNames);
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
