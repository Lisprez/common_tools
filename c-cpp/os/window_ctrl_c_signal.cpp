#include <Windows.h>

BOOL WINAPI CtrlHandler(DWORD event)
{
	switch (event) {
	case CTRL_BREAK_EVENT:
		printf("catch break console event.\n");
		break;
	case CTRL_C_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_CLOSE_EVENT:
		printf("just ignore\n");
		break;
	default:
		printf("unkown key\n");
		return(FALSE);
	}
}

// 注册这个处理函数
SetConsoleCtrlHandler(CtrlHandler, true);

// 取消注册这个处理函数
SetConsoleCtrlHandler(CtrlHandler, false);