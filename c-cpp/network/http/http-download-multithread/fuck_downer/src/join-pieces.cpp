#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

namespace multidown {

	std::vector<std::string> chunk_filenames{};

	/**
	 * 根据chunkName来依次拼接并最终输出文件
	 * @chunkName 分块的主文件名
	 * @fileOutput 输出文件名
	 * 
	 * e.g: chunkName = xxx => xxx.1, xxx.2, xxx.3 => target_file
	 */
	void JoinFile(const std::string& chunkName, const std::string& fileOutput)
	{
		std::string file_name;

		// Create our output file
		FILE* output_file_fp{ nullptr };
		errno_t open_output_file_status = fopen_s(&output_file_fp, fileOutput.c_str(), "ab+");
		
		// 申请一个固定长度的数组用于存入读入的内容
		char* buf = new char[1024 * 1024 * 10];

		// If successful, loop through chunks matching chunkName
		if (open_output_file_status != 0)
		{
			return;
		}

		bool file_found = true;
		int counter = 1;

		while (file_found) 
		{
			file_found = false;

			// Build the filename
			file_name.clear();
			file_name.append(chunkName);
			file_name.append(".");

			file_name.append(std::to_string(counter));
			chunk_filenames.push_back(file_name);

			// Open chunk to read
			FILE* input_file_fp{ nullptr };
			errno_t open_inputfile_status = fopen_s(&input_file_fp, file_name.c_str(), "rb");

			if (open_inputfile_status != 0)
			{
				// 实际上这里有语义上的问题, 这里假设只要打开文件出现错误就表示没有这个文件, 要退出循环
				// 而实际上打开文件失败可能后续的文件还是存在的, 这里这样做只是少了检测文件是否存在的操作
				// 速度上更快一些, 整体操作的效果上也满足要求, 也就是失败了就退出, 后面的文件也没有必要再
				// 操作了
				break;
			}
			
			// If chunk opened successfully, read it and write it to output file.
			file_found = true;
			size_t readed_size = 0;
			for (;;)
			{
				if ((readed_size = fread(buf, 1, 1024 * 1024 * 10, input_file_fp)) > 0)
				{
					fwrite(buf, 1, readed_size, output_file_fp);
				}
				else
				{
					break;
				}
			}

			fclose(input_file_fp);

			counter++;
		}

		// Close output file.
		fclose(output_file_fp);

		delete[] buf;
	}


	void RemoveAllChunkFiles(const std::string& fileName)
	{
		for (const std::string& chunk_filename : chunk_filenames)
		{
			remove(chunk_filename.c_str());
		}
	}

}