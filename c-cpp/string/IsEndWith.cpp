bool IsEndWith(const std::string& src, const std::string& test)
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
