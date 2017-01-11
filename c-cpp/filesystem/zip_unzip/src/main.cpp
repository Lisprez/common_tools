#include <iostream>

#include "../inc/zip_interface.h"

int main(int argc, char* argv[])
{
//	if (CompressFolderToZipFile("abc", "abc.zip"))
//	{
//		std::cout << "zip succeed" << std::endl;
//	}
//	else 
//	{
//		std::cout << "zip failed" << std::endl;
//	}

	if (Extract_Zip_File("abc.zip"))
	{
		std::cout << "extract success" << std::endl;
	}
	else
	{
		std::cout << "extract error" << std::endl;
	}

	return 0;
}
