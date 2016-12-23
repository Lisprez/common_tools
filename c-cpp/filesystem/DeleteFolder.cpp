static BOOL DeleteFolder_(const std::string& targetDirPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = { 0 };
	memcpy(l_szTmp, targetDirPath.data(), 1024);

	char l_szSrcPath[1025] = { 0 };
	memcpy(l_szSrcPath, targetDirPath.data(), 1024);

	char l_szNewSrcPath[1025] = { 0 };

	strcat(l_szTmp, "\\*");
	hFind = FindFirstFile(l_szTmp, &FindFileData);
	if (hFind == NULL || hFind == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	do
	{

		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(FindFileData.cFileName, "."))
			{
				if (strcmp(FindFileData.cFileName, ".."))
				{
					printf("The Directory found is %s\n", FindFileData.cFileName);
					sprintf(l_szNewSrcPath, "%s\\%s", l_szSrcPath, FindFileData.cFileName);
					DeleteFolder_(l_szNewSrcPath);
				}
			}
		}
		else
		{
			printf("The File found is %s\n", FindFileData.cFileName);
			char l_szSrcFile[1025] = { 0 };
			sprintf(l_szSrcFile, "%s\\%s", l_szSrcPath, FindFileData.cFileName);
			if (DeleteFile(l_szSrcFile) == 0)
			{
				std::cout << "Delete file error!!!" << std::endl;
				FindClose(hFind);
				return FALSE;
			}
		}
	} while (FindNextFile(hFind, &FindFileData));
	if (RemoveDirectory(targetDirPath.c_str()) == 0)
	{
		std::cout << "Delete folder error!!!" << std::endl;
		FindClose(hFind);
		return FALSE;
	}

	FindClose(hFind);
	return TRUE;
}

bool DeleteFolder(const std::string& folder)
{
	if (!supervisor::util::IsDirExist(folder))
	{
		return false;
	}

	try {
		if (DeleteFolder_(folder) == FALSE)
		{
			return false;
		}
		return true;
	}
	catch (std::exception& e) {
		std::cout << "[----ERROR---] Delete folder" << e.what() << std::endl;
		return false;
	}
}
