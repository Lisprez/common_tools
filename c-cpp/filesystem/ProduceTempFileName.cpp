constexpr int BUFFER_LENGTH = 1024

std::string ProduceTempFileName(void)
{
	char foler_path_buf[BUFFER_LENGTH];
	char file_name_buf[BUFFER_LENGTH];

	unsigned long foler_len = GetTempPathA(BUFFER_LENGTH, foler_path_buf);
	if (foler_len == BUFFER_LENGTH || foler_len == 0)
	{
		return std::string("");
	}
	else
	{
		unsigned long file_name_len = GetTempFileNameA(foler_path_buf, "SupervisorUpdate_", 0, file_name_buf);
		if (file_name_len <= foler_len)
		{
			return std::string("");
		}
		else
		{
			return std::string(file_name_buf);
		}
	}
}
