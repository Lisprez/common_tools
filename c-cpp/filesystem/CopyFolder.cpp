/**
 * 递归复制一个目录到一个的目录中的所有内容到一个新的目录
 * 
 * @param sourceDirPath
 * @param targetDirPath
 *
 * @return BOOL
 */
static BOOL copy_folder(const std::string& sourceDirPath, const std::string& targetDirPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = { 0 };
	memcpy(l_szTmp, sourceDirPath.data(), sourceDirPath.size());


	char l_szSrcPath[1025] = { 0 };
	char l_szDesPath[1025] = { 0 };
	memcpy(l_szSrcPath, sourceDirPath.data(), sourceDirPath.size());
	memcpy(l_szDesPath, targetDirPath.data(), targetDirPath.size());

	char l_szNewSrcPath[1025] = { 0 };
	char l_szNewDesPath[1025] = { 0 };

	strcat(l_szTmp, "\\*");

	hFind = FindFirstFile(l_szTmp, &FindFileData);

	if (hFind == NULL || hFind == INVALID_HANDLE_VALUE) 
	{
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
					copy_folder(l_szNewSrcPath, l_szNewDesPath);
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

/**
 * 完整复制一个目录到一个新的目录
 *
 * @param sourceFolder
 * @param destFolder
 *
 * @return bool
 */
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

	try 
	{
		if (copy_folder(sourceFolder, destFolder) == FALSE)
		{
			std::cout << "[----ERROR----] Copy old version file for backup error !!!" << std::endl;
			return false;
		}
		return true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}
