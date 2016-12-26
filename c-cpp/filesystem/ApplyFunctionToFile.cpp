int ApplyFunctionToFile(const std::string& srcFolder, 
						std::function<int(const std::string&, const std::string&)> comment_remover,
						const std::string& dstFolder)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = { 0 };
	std::cout << srcFolder.c_str() << std::endl;
	memcpy(l_szTmp, srcFolder.data(), srcFolder.size());


	char l_szSrcPath[1025] = { 0 };
	char l_szDesPath[1025] = { 0 };
	memcpy(l_szSrcPath, srcFolder.data(), srcFolder.size());
	memcpy(l_szDesPath, dstFolder.data(), dstFolder.size());

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
					ApplyFunctionToFile(l_szNewSrcPath, comment_remover, l_szNewDesPath);
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
			comment_remover(l_szSrcFile, l_szDesFile);
		}
	} while (FindNextFile(hFind, &FindFileData));

	FindClose(hFind);
	return TRUE;
}
