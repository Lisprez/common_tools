#pragma once

#include <string>

bool Extract_Zip_File(const std::string& src_file);
bool CompressFolderToZipFile(const std::string& sourceFolder, const std::string& zipFileName);