#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int SafeSprintf(char* buf, int bufSize, char* format, ...)
{
	int byte_count = 0;
	va_list arg_list;
	if (!buf)
	{
		goto SafeSprintf_END_PROCESS;
	}
	va_start(arg_list, format);
	byte_count += vsnprintf(buf + byte_count, bufSize - byte_count, format, arg_list);
	va_end(arg_list);
	if (byte_count > bufSize - 1)
	{
		byte_count = bufSize - 1;
	}
	*(buf + byte_count) = '\0';
SafeSprintf_END_PROCESS:
	return byte_count;
}
