/**
 * 用于获取第i行的头的字符在整体文件中的位置(position)
 * 注意: 要弄清楚一个文件的行尾结束符是'\r\n', 还是'\n'
 *
 * @param buf
 * @param lineNo 指定行号
 * @param format 文件格式(dos => '\r\n', unix => '\n', mac => '\r')
 *
 * @return size_t
 */
size_t get_indexed_line_head_position(const std::string& buf, int lineNo, const std::string& format)
{
	size_t location = 0;
	std::string deli;
	if (format == "dos")
	{
		deli = "\r\n";
	}
	else if (format == "unix")
	{
		deli = "\n";
	}
	else if (format == "mac")
	{
		deli = "\r";
	}

	for (auto i = 0; i < lineNo - 1; i++)
	{
		auto index = buf.find(deli, location);
		if (index == -1)
		{
			return -1; //表示没有指定的分隔符
		}
		location = index + deli.length();
	}

	return location;
}


/**
 * 将content插入到filePath指定文件的第line_no行开头的位置
 *
 * @param filePath
 * @param line_no 行号(从1开始)
 * @param content
 *
 * @return void
 */
void insert_content_to_file(const std::string& filePath, int line_no, const std::string& content)
{
	std::string old_content = get_file_content(filePath);
	size_t third_line_location = get_line_head_index(old_content, line_no, "dos");
	std::string head = old_content.substr(0, third_line_location);
	std::string tail = old_content.substr(third_line_location);
	std::ofstream fwstream(filePath, std::ios::out | std::ios::trunc);
	fwstream << head;
	fwstream << content;
	fwstream << tail;
	fwstream.close();
}