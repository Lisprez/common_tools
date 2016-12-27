BOOL ApplyFunctionToFile(const std::string& srcFolder,
                         std::map<std::string, std::string> modifyContent,
                         std::function<void(const std::string& filePath,
                                            std::map<std::string,std::string>)> modifier)
{
    WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = { 0 };
	std::cout << srcFolder.c_str() << std::endl;
	memcpy(l_szTmp, srcFolder.data(), srcFolder.size());


	char l_szSrcPath[1025] = { 0 };
	memcpy(l_szSrcPath, srcFolder.data(), srcFolder.size());

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
					ApplyFunctionToFile(l_szNewSrcPath, modifyContent, modifier);
				}
			}
		}
		else
		{
			printf("The File found is %s\n", FindFileData.cFileName);
			char l_szSrcFile[1025] = { 0 };
			char l_szDesFile[1025] = { 0 };
			sprintf(l_szSrcFile, "%s\\%s", l_szSrcPath, FindFileData.cFileName);
			modifier(l_szSrcFile, modifyContent);
		}
	} while (FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	return TRUE;
}
