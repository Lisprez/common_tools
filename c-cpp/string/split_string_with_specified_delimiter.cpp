#include <sstream>

/**
 * abc;defg;hij => [abc, defg, hij]
 * abc;defg;hij; => [abc, defg, hij]
 * abc => [abc]
 */
std::vector<std::string> split_string_with_specified_delimiter(const std::string& str, const char delimiter)
{
	std::vector<std::string> str_array{};
	std::string middle_str;
	std::istringstream str_stream(str);
	while (std::getline(str_stream, middle_str, delimiter)
	{
		str_array.push_back(middle_str);
	}

	return str_array;
}