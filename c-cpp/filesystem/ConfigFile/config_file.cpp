#include "config_file.h"

#include <Windows.h>

config_file::ConfigFile::ConfigFile()
{
    
}

config_file::ConfigFile::~ConfigFile()
{
    delete config_file_parser_;
}

static bool IsFileExists(const std::string& filePath)
{
    DWORD dwAttrib = GetFileAttributes(filePath.c_str());
    return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

void config_file::ConfigFile::Setup(const std::string& configFileName)
{
    config_file_name_ = configFileName;
    config_file_parser_ = new config_file_parser::ConfigFileParser(configFileName);
}

config_file::ConfigFile& config_file::ConfigFile::Get()
{
    static ConfigFile config_file_instance{};
    return config_file_instance;
}

bool config_file::ConfigFile::IsReadable() const
{
    return config_file_parser_->IsReadable();
}


std::tuple<std::string, bool> config_file::ConfigFile::Read(const std::string& key)
{
    if (IsReadable())
    {
        return config_file_parser_->Get(key);
    }
    else
    {
        return std::tuple<std::string, bool>("", false);
    }
}

void config_file::ConfigFile::Write(const std::string& key, const std::string& value) const
{
    config_file_parser_->Set(key, value);
}
