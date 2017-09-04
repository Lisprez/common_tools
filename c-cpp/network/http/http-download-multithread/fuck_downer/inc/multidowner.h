#pragma once

#include <string>

namespace multidown {

	enum class DownloadStatus {
		TARGET_FILE_SIZE_ERROR,
		OPEN_CHUNK_FILE_ERROR,
		ALL_THREAD_FINISHED,
	};

	bool MultiDownload(const std::string& url, const std::string& filePathName, int threadNum = 8);

}
