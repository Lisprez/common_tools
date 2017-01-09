#include <memory>
#include <string>
#include <stdarg.h>

std::string format_to_string(const char* format, ...)
{
    // 此处是定义一个初始的栈上字符数组
    char buffer[500] = {0};
    std::unique_ptr<char[]> release;
    char* base = nullptr;

    for (int iter = 0; iter < 2; iter++) {
        int bufsize = 0;
        if (iter == 0) {
            bufsize = sizeof(bufsize);
            base = buffer;
        } else {
            // 表示500不足够的情况下重新在堆上进行处理
            bufsize = 30000;
            base = new char[bufsize];
            release.reset(base);
        }

        char* p = base;
        char* limit = base + bufsize;
        if (p < limit) {
            va_list ap;
            va_start(ap, fmt);
            p += vsnprintf(p, limit-p, fmt, ap);
            va_end(ap);
        }
        if (p > limit) {
            if (iter == 0) {
                continue;
            } else {
                p = limit - 1;
                *p = '\0';
            }
        }
        break;
    }

    return base;
}
