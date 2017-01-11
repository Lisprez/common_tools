// filenamePrefix 只取用其前3个字符作为前缀
std::string ProduceTmpFileName(const std::string& parentDirectory, const std::string& filenamePrefix)
{
	char file_name_buf[BUFFER_LENGTH];
	unsigned long file_name_len = GetTempFileNameA(parentDirectory.c_str(), filenamePrefix.c_str(), 0, file_name_buf);
	unsigned len = filenamePrefix.length();
	if (file_name_len <= parentDirectory.length() + (len > 3 ? 3 : len))
	{
		return std::string("");
	}
	else
	{
		return std::string(file_name_buf);
	}
}
