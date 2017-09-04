#include "multidowner.h"

#include <string>
#include <iostream>



int main(int argc, const char* argv[])
{
	std::string url{ "http://127.0.0.1/fuck.zip" };
	std::string file_path_name{ "chao_fuck.zip" };
	bool res = multidown::MultiDownload(url, file_path_name);

	if (res)
	{
		std::cout << "download success";
	}
	else
	{
		std::cout << "download error";
	}

	return 0;
}