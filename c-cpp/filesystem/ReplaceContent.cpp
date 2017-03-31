/**
 * 判断一个字符串是否以另一个字符串作为结尾
 *
 * @param src: const std::string&
 * @param test: const std::string&
 * 
 * @return bool
 */

static bool IsEndWith(const std::string& src, const std::string& test)
{
    size_t src_len = src.length();
    size_t test_len = test.length();
    if (src_len < test_len)
    {
        return false;
    }
    std::string end_str = src.substr(src_len - test_len, src_len - 1);
    if (test == end_str)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * 修改文本文件中的内容, 在文件中寻找到map中的key, 并替换成value
 * 注意: 这是一个完全匹配并替换的过程, 比如 abc_def匹配abc_def, 但是它不匹配abc_defg, 
 * 
 * @param filePath: const std::string& 需要修改的文件的绝对路径
 * @param modifyContent: std::map<std::string, std::string> 要修改的内容组成的map
 * 
 * @return void
 */
void modify_content(const std::string& filePath, std::map<std::string, std::string>& modifyContent)
{
	if (IsEndWith(filePath, ".ocs") || IsEndWith(filePath, ".obj")) {
		auto content = std::make_shared<std::vector<std::string>>();
		std::ifstream file_before_modify(filePath);
		std::string line{};

		while (std::getline(file_before_modify, line))
		{
			debug2output("%s\n", line.c_str());
			if (line.empty())
			{
				continue;
			}
			content->push_back(line);
		}
		file_before_modify.close();

		for (auto& x : modifyContent)
		{
			// set this for pattern match entity world
			std::regex reg(R"(\b)" + x.first R"(\b)");
			std::string replacement(x.second);
			for (auto& line_ : *content)
			{
				std::string result = std::regex_replace(line_, reg, replacement);
				line_ = result;
				debug2output("%s\n", line_.c_str());
			}
		}

		std::ofstream file_after_modify(filePath);
		for (auto& line_ : *content)
		{
			file_after_modify << line_ << "\n";
		}
		file_after_modify.close();
	}
}
