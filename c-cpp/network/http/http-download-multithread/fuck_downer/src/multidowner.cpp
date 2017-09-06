#include "multidowner.h"
#include "curl.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdio>
#include <vector>
#include <ctime>
#include "join-piece.h"
#include <cassert>
#include <vector>


static bool support_range = false;

struct Node
{
	FILE* fp;
	long start_pos;
	long end_pos;
	void* curl;
	std::thread::id tid;
	int chunk_index;
};


static size_t write_function(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	Node *node = (Node *)userdata;
	return fwrite(ptr, size, nmemb, node->fp);
}

int progress_func(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	int percent = 0;
	if (totalToDownload > 0)
	{
		percent = (int)(nowDownloaded / totalToDownload * 100);
	}

	if (percent % 20 == 0)
	{
		printf("....%0d%%\n", percent);
	}

	return 0;
}


static size_t curl_header_cb(void *ptr, size_t size, size_t nmemb, void *opaque)
{
	size_t realsize = size * nmemb;
	const char* accept_line = "Accept-Ranges: bytes";

	if (realsize >= strlen(accept_line) && strncmp((char *)ptr, accept_line, strlen(accept_line)) == 0)
	{
		support_range = true;
	}

	return realsize;
}

/**
 * 获取目录文件的大小, 同时检查远程Http服务器是否支持对目录文件的Range
 * 通过全局变量的support_range来标记
 */
long get_target_file_size_and_check_range_support(const char *url, const std::vector<std::string>& params)
{
	double target_file_size = 0;
	struct curl_slist* header_chunk = nullptr;
	for (const std::string& item : params)
	{
		header_chunk = curl_slist_append(header_chunk, item.c_str());
	}
	CURL* handle = curl_easy_init();
	if (!handle)
	{
		//printf("curl_easy_init error...\n");
		return -1;
	}
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, header_chunk);
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_HEADER, 1);	//只需要header头
	curl_easy_setopt(handle, CURLOPT_NOBODY, 1);	//不需要body
	curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, curl_header_cb);
	curl_easy_setopt(handle, CURLOPT_HEADERDATA, nullptr);

	if (curl_easy_perform(handle) == CURLE_OK)
	{
		//curl_easy_getinfo(handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &target_file_size);
		curl_easy_getinfo(handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &target_file_size);
	}
	else
	{
		//printf("curl_easy_perform error...\n");
		target_file_size = -1;
	}

	return target_file_size;
}


/**
 * 工作线程, 通过执行curl_easy_perform来完成真实的下载动作
 */
void* work_thread(void *pData)
{
	Node *pNode = (Node *)pData;
	int try_count = 0;
	for (;;)
	{
		try_count += 1;

		int res = curl_easy_perform(pNode->curl);

		if (res != CURLcode::CURLE_OK)
		{
			//printf("curl_easy_perform error...\n");
			std::this_thread::sleep_for(std::chrono::seconds(3));
			if (try_count >= 20)
			{
				break;
			}
			continue;
		}
		break;		
	}

	curl_easy_cleanup(pNode->curl);

	//printf("Thread %ld finished\n", pNode->tid);

	delete pNode;

	return nullptr;
}


std::string get_utc()
{
	auto timestamp = std::chrono::seconds(std::time(nullptr));
	__int64 seconds = std::chrono::seconds(timestamp).count();
	auto str = std::to_string(seconds);
	return str;
}

/**
 * 下载的入口函数
 * @threadNum 下载的线程数, 默认值是8
 * @Url 目录文件url
 * @filePathName 要落地保存的文件名
 */
multidown::DownloadStatus my_downLoad(int threadNum, std::string Url, const std::string& filePathName, const std::vector<std::string>& params)
{
	std::vector<std::thread*> threads;
	std::thread* thread_ptr{ nullptr };
	std::vector<FILE*> file_pointers;
	curl_global_init(CURL_GLOBAL_ALL);
	std::string file_chunk_name{ std::move(get_utc()) };

	long file_length = get_target_file_size_and_check_range_support(Url.c_str(), params);
	int real_thread_num = threadNum;

	if (file_length <= 0)
	{
		//printf("Get the file length error...\n");
		return multidown::DownloadStatus::TARGET_FILE_SIZE_ERROR;
	}
	
	if (!support_range)
	{
		real_thread_num = 1;
	}

	long part_size = file_length / real_thread_num;

	for (int i = 0; i <= real_thread_num; i++)
	{
		Node *pNode = new Node();
		FILE* fp;
		errno_t res = fopen_s(&fp, (file_chunk_name + "." + std::to_string(i + 1)).c_str(), "wb");
		if (res == 0)
		{
			file_pointers.push_back(fp);
		}
		else
		{
			return multidown::DownloadStatus::OPEN_CHUNK_FILE_ERROR;
		}

		if (i < threadNum)
		{
			pNode->start_pos = i * part_size;
			pNode->end_pos = (i + 1) * part_size - 1;
		}
		else
		{
			if (file_length % threadNum != 0)
			{
				pNode->start_pos = i * part_size;
				pNode->end_pos = file_length - 1;
			}
			else
			{
				break;
			}
		}

		CURL *curl = curl_easy_init();

		pNode->curl = curl;
		pNode->fp = fp;
		pNode->chunk_index = i + 1;
		pNode->fp = fp;

		char range[64] = { 0 };
		snprintf(range, sizeof(range), "%ld-%ld", pNode->start_pos, pNode->end_pos);

		// Config the easy structure
		struct curl_slist* header_chunk = nullptr;
		for (const std::string& item : params)
		{
			header_chunk = curl_slist_append(header_chunk, item.c_str());
		}
		CURL* handle = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_chunk);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pNode);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);
		curl_easy_setopt(curl, CURLOPT_RANGE, range);

		thread_ptr =  new std::thread(work_thread, pNode);
		pNode->tid = thread_ptr->get_id();
		threads.push_back(thread_ptr);
	}

	for (auto thread : threads)
	{
		thread->join();
	}

	for (auto fp : file_pointers)
	{
		fclose(fp);
	}

	curl_global_cleanup();

	//printf("All threads finished...\n");

	multidown::JoinFile(file_chunk_name, filePathName);
	multidown::RemoveAllChunkFiles(file_chunk_name);
	

	return multidown::DownloadStatus::ALL_THREAD_FINISHED;
}


namespace multidown {

	unsigned char ToHex(unsigned char x)
	{
		return  x > 9 ? x + 55 : x + 48;
	}

	unsigned char FromHex(unsigned char x)
	{
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		else assert(0);
		return y;
	}

	std::string UrlEncode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') ||
				(str[i] == '_') ||
				(str[i] == '.') ||
				(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}

	std::string UrlDecode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%')
			{
				assert(i + 2 < length);
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high * 16 + low;
			}
			else strTemp += str[i];
		}
		return strTemp;
	}

	bool MultiDownload(const std::string& url, const std::string& filePathName, int threadNum /*= 8*/)
	{
		std::string decoded_url = UrlDecode(url);
		std::string delimiter{ "?" };

		std::string::size_type delimiter_pos = decoded_url.find(delimiter);
		std::vector<std::string> parameter{};
		if (delimiter_pos != std::string::npos)
		{
			std::string real_file_url = decoded_url.substr(0, delimiter_pos);
			std::string parameter_part = decoded_url.substr(delimiter_pos + 1, decoded_url.length());
			std::istringstream parameter_part_stream(parameter_part);
			std::string middle;
			while (std::getline(parameter_part_stream, middle, '&'))
			{
				parameter.push_back(middle);
			}

			for (std::string& item : parameter)
			{
				item.replace(item.find("="), 1, 1, ':');
			}
		}

		multidown::DownloadStatus res = my_downLoad(threadNum, url, filePathName, parameter);

		switch (res) {
		case multidown::DownloadStatus::OPEN_CHUNK_FILE_ERROR:
		case multidown::DownloadStatus::TARGET_FILE_SIZE_ERROR:
			return false;
		case multidown::DownloadStatus::ALL_THREAD_FINISHED:
			return true;
		default:
			printf("Unknown error...\n");
			return false;
		}
	}

}