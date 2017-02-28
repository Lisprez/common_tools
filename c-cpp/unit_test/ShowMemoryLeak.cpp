// 使用VC运行时提供的功能来检测是否有内存泄漏
// 当然这个只能在Debug模式下使用

#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	// all functions write here
	
	// 调用这个函数之后, debug模式下就可以看输出窗口中看到
	// 内存泄漏情况的报告
	_CrtDumpMemoryLeaks();

	return 0;
}