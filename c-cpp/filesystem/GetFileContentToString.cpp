#include <string>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <fstream>

/**
 * 读取文件内容到字符串, (打开文件失败抽出异常)
 *
 * @param filePath
 *
 * @return std::string
 */
std::string get_file_content(const std::string& filePath)
{
	std::FILE* fp = std::fopen(filePath.c_str(), "rb");
	if (!fp)
	{
		throw(errno); //文件的内容可能为空,所以只能通过抛出异常的方式来告诉出现了错误
	}

	std::string content;
	std::fseek(fp, 0, SEEK_END);
	content.resize(std::ftell(fp));
	std::rewind(fp);
	std::fread(&content[0], 1, content.size(), fp);
	std::fclose(fp);

	return content;
}
