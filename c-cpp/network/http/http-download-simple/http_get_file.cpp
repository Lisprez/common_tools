// 切记：在链接libcurl.lib的时候一定要指定一个预编译选项
// 因为这里是静态库，所以一定要是定义下面这个宏
// CURL_STATICLIB
// 否则无法通过编译

#include "curl/curl.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}


bool supervisor::util::HttpGetFile(const std::string& staticUrlPath, const std::string& toSavedFilePath)
{
	CURL* curl = nullptr;
	CURLcode res;
	FILE* hd_src;
	struct stat file_info;
	try {
		stat(toSavedFilePath.c_str(), &file_info);
		fopen_s(&hd_src, toSavedFilePath.c_str(), "wb");
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_URL, staticUrlPath.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, hd_src);
			curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
				(curl_off_t)file_info.st_size);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cout << "[----ERROR----] curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
				fclose(hd_src);
				curl_easy_cleanup(curl);
				curl_global_cleanup();
				return false;
			}
			else
			{
				std::cout << "[supervisor log] curl perform succeed." << std::endl;
			}
		}
		else
		{
			std::cout << "[----ERROR----] Curl init error!" << std::endl;
			fclose(hd_src);
			curl_global_cleanup();
			return false;
		}

		fclose(hd_src);
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		return true;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		fclose(hd_src);
		if (curl != nullptr)
		{
			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
		return false;
	}
}
