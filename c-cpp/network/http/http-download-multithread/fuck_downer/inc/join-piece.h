#pragma once

#include <string>

namespace multidown {

	void JoinFile(const std::string& chunkName, const std::string& fileOutput);
	void RemoveAllChunkFiles(const std::string& fileName);

}