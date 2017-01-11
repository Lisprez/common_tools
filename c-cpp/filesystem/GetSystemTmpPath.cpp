std::string GetSystemTmpPath(void)
{
	char folder_path_buf[1024]{0};
	unsigned long path_length = GetTempPathA(1024, folder_path_buf);
	if (path_length == 1024 || path_length == 0)
	{
		return std::string("");
	}
	else
	{
		return std::string(folder_path_buf);
	}
}
