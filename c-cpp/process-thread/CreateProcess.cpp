/**
 * 创建一个进程
 * 
 * 如果要给进程传递命令行参数, 有两种方式:
 * 1. 直接将应用程序路径和命令行参数拼接到一个buf中, 然后传递到CreateProcess的第二个参数, 第一个参数留空, 这样让操作系统的API
 *    来自行解析参数
 * 2. 第二种方式是应用程序通过参数1来传递, 而应用程序的参数通过参数2来传递, 这种方式没有实践过
 */

void CreateProcess()
{
	STARTUPINFO si;
	PROCESS_INFOMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(nullptr,
			cmd, //注意: 这里有一个要点, 那就是放在这里的要么是字面量的"application_full_path param1 param2", 要么就要通过
				 //char[] 这样的形式去传, 传静态的字符串可能失败, 因为系统要去这个buf进行处理. 
			nullptr,
			nullptr,
			FALSE,
			0,
			nullptr,
			nullptr,
			&si,
			&pi))
		{
			std::cout << "Error Exit!" << std::endl;
		}
}