#include "multidowner.h"

#include <map>
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>


int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		printf("Usage: fuck_downer FileName Url\n"
			"\tFileName: your local filename to saved for.\n"
			"\tURL: the http url of download target\n"
			);

		return -1;
	}


	const char* file_path_name = argv[1];
	const char* url = argv[2];

	bool res = multidown::MultiDownload(url, file_path_name);

	if (res)
	{
		printf("Download success\n");
	}
	else
	{
		printf("Download error\n");
	}

	return 0;
}