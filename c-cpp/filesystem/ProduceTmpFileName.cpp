/**
 * 生成一个临时文件名
 *
 * @param parentDirectory 这个临时文件所在的目录的绝对路径
 * @param filenamePrefix 临时文件名的前缀, 注意:这个前缀无论多长,只取其前3个字母
 *
 * @return std::string 返回生成临时文件名的全路径, 失败返回的空字符串
 */
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
