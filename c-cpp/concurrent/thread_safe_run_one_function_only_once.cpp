#include <thread>

std::once_flag once_flag;

std::call_once(once_flag, [&]{
    // 在这里调用那个只需要线程安全的执行一次的函数 f
    f();
});
