#include <ctime>

/**
 * 返回一个指定格式的时间戳
 * @buf: 接受输出的buf地址
 * @bufSize: 接受输出的buf的大小
 * @timeFormatString: 输出时间字符串的格式, 例如:"%Y/%m/%d_%H:%M:%S
 */
static int GetATimeStamp(char* buf, int bufSize, const char* timeFormatString)
{
	time_t raw_time;
	struct tm* time_info = nullptr;
	int len = 0;
	time(&raw_time);
	time_info = localtime(&raw_time);
	len = strftime(buf, bufSize, timeFormatString, time_info);
	buf[len] = '\0';

	return len;
}

//-------------------------------------------------------------------------------------
#include <ctime>

static std::string GetATimeStamp(const std::string& timeFormatString)
{
	std::array<char, 40> buf{};
	time_t raw_time;
	struct tm* time_info = nullptr;
	time(&raw_time);
	time_info = localtime(&raw_time);
	int len = strftime(buf.data(), buf.size(), timeFormatString, time_info);
	if (len == 0)
	{
		return "";
	}
	else
	{
		return std::string(std::begin(buf), std::end(buf));
	}
}