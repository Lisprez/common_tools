bool IsFileExists(const std::string& filePath)
{
	DWORD dwAttrib = GetFileAttributes(filePath.c_str());
	return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

/**
 * 速度最快的用标准库来检测一个文件是否存在的实现
 * 上面的实例是调用Win32 API来完成的, 无法跨平台
 */
bool file_exists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}