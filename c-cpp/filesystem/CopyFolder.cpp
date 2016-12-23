static BOOL CopyFolder_(const std::string& sourceDirPath, const std::string& targetDirPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = { 0 };
	memcpy(l_szTmp, sourceDirPath.data(), 1024);


	char l_szSrcPath[1025] = { 0 };
	char l_szDesPath[1025] = { 0 };
	memcpy(l_szSrcPath, sourceDirPath.data(), 1024);
	memcpy(l_szDesPath, targetDirPath.data(), 1024);

	char l_szNewSrcPath[1025] = { 0 };
	char l_szNewDesPath[1025] = { 0 };

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

					sprintf(l_szNewDesPath, "%s\\%s", l_szDesPath, FindFileData.cFileName);

					sprintf(l_szNewSrcPath, "%s\\%s", l_szSrcPath, FindFileData.cFileName);
					CreateDirectory(l_szNewDesPath, NULL);
					CopyFolder_(l_szNewSrcPath, l_szNewDesPath);
				}
			}
		}
		else
		{
			printf("The File found is %s\n", FindFileData.cFileName);
			char l_szSrcFile[1025] = { 0 };
			char l_szDesFile[1025] = { 0 };
			sprintf(l_szDesFile, "%s\\%s", l_szDesPath, FindFileData.cFileName);
			sprintf(l_szSrcFile, "%s\\%s", l_szSrcPath, FindFileData.cFileName);
			BOOL l_bRet = CopyFile(l_szSrcFile, l_szDesFile, TRUE);

		}


	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	return TRUE;
}

bool supervisor::util::CopyFolder(const std::string& sourceFolder, const std::string& destFolder)
{
	if (!IsDirExist(sourceFolder))
	{
		return false;
	}

	if (CreateDirectory(destFolder.c_str(), nullptr) == 0)
	{
		std::cout << "[----ERROR----] Create backup folder error !!!" << std::endl;
		return false;
	}

	try {
		if (CopyFolder_(sourceFolder, destFolder) == FALSE)
		{
			std::cout << "[----ERROR----] Copy old version file for backup error !!!" << std::endl;
			return false;
		}
		return true;
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
		return false;
	}
}
