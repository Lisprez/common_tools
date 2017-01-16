#include <ctime>

static int GetATimeStamp(char* buf, int bufSize)
{
	time_t raw_time;
	struct tm* time_info = nullptr;
	int len = 0;
	time(&raw_time);
	time_info = localtime(&raw_time);
	len = strftime(buf, bufSize, "%Y/%m/%d_%H:%M:%S", time_info);
	buf[len - 1] = '\0';

	return len;
}
