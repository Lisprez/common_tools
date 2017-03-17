#pragma once
#include <string>
#include <map>

namespace config_file_parser {

    class ConfigFileParser {
    public:
        ConfigFileParser(const std::string& fileName);
        ~ConfigFileParser();

        std::tuple<std::string, bool> Get(const std::string& key) const;
        void Set(const std::string& key, const std::string& value) const;
        bool IsReadable() const;

    private:
        std::string file_name_;
        std::map<std::string, std::string>* key_values_ = nullptr;
        bool readable_ = false;
    };
}