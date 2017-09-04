#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

namespace multidown {

	// Simply gets the file size of file.
	int get_file_size(std::ifstream* file)
	{
		file->seekg(0, std::ios::end);
		int filesize = file->tellg();
		file->seekg(std::ios::beg);
		return filesize;
	}

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
		std::ofstream outputfile;
		outputfile.open(fileOutput, std::ios::out | std::ios::binary | std::ios::app);

		// If successful, loop through chunks matching chunkName
		if (outputfile.is_open()) 
		{
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

				// Open chunk to read
				std::ifstream file_input;
				file_input.open(file_name.c_str(), std::ios::in | std::ios::binary);

				// If chunk opened successfully, read it and write it to output file.
				if (file_input.is_open())
				{
					file_found = true;
					outputfile.seekp(0, std::ios::end);
					outputfile << file_input.rdbuf();

					file_input.close();
				}
				counter++;
			}

			// Close output file.
			outputfile.close();

			printf("File assembly complete...\n");
		}
		else
		{
			printf("Error: Unable to open file for output...\n");
		}

	}


	bool file_exists(const std::string& name)
	{
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}


	void RemoveAllChunkFiles(const std::string& fileName)
	{
		for (int i = 1; ; i++)
		{
			std::string file_name{ fileName + "." + std::to_string(i) };
			if (file_exists(file_name))
			{
				std::remove(file_name.c_str());
			}
			else
			{
				break;
			}
		}
	}

}