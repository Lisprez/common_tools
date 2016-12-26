bool IsFileExists(const std::string& filePath)
{
	DWORD dwAttrib = GetFileAttributes(filePath.c_str());
	return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}