#include <fstream>
#include <tuple>

#include "Windows.h"
#include "config_file_parser.h"

static bool IsFileExists(const std::string& filePath)
{
    DWORD dwAttrib = GetFileAttributes(filePath.c_str());
    return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

static std::tuple<char, int> GetFirstNoneSpaceCharOfLine(const std::string& line)
{
    int i = 0;
    for (; line[i] == ' ';) { ++i; }
    return std::tuple<char, int>(line[i], i);
}

static void ReadFileToMap(const std::string& fileName,
    std::map<std::string, std::string>& key_values)
{
    std::ifstream reader;
    reader.open(fileName, std::ifstream::in);
    std::string line_content{};
    while (std::getline(reader, line_content))
    {
        char first_no_space_char = std::get<0>(GetFirstNoneSpaceCharOfLine(line_content));
        int no_space_index = std::get<1>(GetFirstNoneSpaceCharOfLine(line_content));
        if (first_no_space_char == '#')
        {
            key_values.insert({ line_content.substr(no_space_index, line_content.length()), "comments" });
        }
        else if (first_no_space_char == '\n')
        {
            key_values.insert({ "\n", "spaceline" });
        }
        else
        {
            size_t equal_sign_index = line_content.find_first_of('=');
            if (equal_sign_index == std::string::npos)
            {
                return;
            }
            size_t to_left = 0;
            for (to_left = equal_sign_index - 1; line_content[to_left] == ' ';)
            {
                --to_left;
            }
            std::string key = line_content.substr(no_space_index, to_left - no_space_index + 1);
            size_t to_right = 0;
            for (to_right = equal_sign_index + 1; line_content[to_right] == ' ';)
            {
                ++to_right;
            }
            std::string value = line_content.substr(to_right, line_content.length() - to_right);
            key_values.insert({ key, value });
        }
    }
    reader.close();
}

config_file_parser::ConfigFileParser::ConfigFileParser(const std::string& fileName)
    : key_values_(new std::map<std::string, std::string>())
{
    if (IsFileExists(fileName))
    {
        ReadFileToMap(fileName, *key_values_);
        if (!key_values_->empty())
        {
            readable_ = true;
        }
    }
    file_name_ = fileName;
}

config_file_parser::ConfigFileParser::~ConfigFileParser()
{
    std::ofstream writer;
    writer.open(file_name_, std::ofstream::out | std::ofstream::trunc);
    std::string finalize_string{};
    for (const auto& pair : *key_values_)
    {
        if (pair.first[0] == '#')
        {
            finalize_string.append(pair.first).append("\n");
        }
        else if (pair.first[0] == '\n')
        {
            finalize_string.append("\n");
        }
        else
        {
            finalize_string.append(pair.first).append(" = ").append(pair.second).append("\n");
        }
    }
    writer << finalize_string;
    writer.close();
    delete key_values_;
    readable_ = false;
}

bool config_file_parser::ConfigFileParser::IsReadable() const
{
    return readable_;
}

std::tuple<std::string, bool> config_file_parser::ConfigFileParser::Get(const std::string& key) const
{
    if (!IsReadable())
    {
        return std::tuple<std::string, bool>("", false);
    }

    auto res = key_values_->find(key);
    if (res == key_values_->end())
    {
        return std::tuple<std::string, bool>("", false);
    }
    else
    {
        return std::tuple<std::string, bool>(res->second, true);
    }
}

void config_file_parser::ConfigFileParser::Set(const std::string& key, const std::string& value) const
{
    (*key_values_)[key] = value;
}