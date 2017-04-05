#include <chrono>
/**
 * 以字符串的形式获取1990年1月1日0时0分0秒至今的秒数
 *
 * @return std::string
 */
std::string GetUTC() 
{
	auto timestamp = std::chrono::seconds(std::time(nullptr));
	int seconds = std::chrono::seconds(timestamp).count();
	auto str = std::to_string(seconds);
	return str;
}