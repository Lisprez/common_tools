#pragma once

#include <tuple>
#include <string>

#include "config_file_parser.h"

namespace config_file {

    class ConfigFile {
    public:
        // 禁用默认的copy构建与复制构建
        // 禁用默认的移动copy构建与移动复制构建
        ConfigFile(const ConfigFile&) = delete;
        ConfigFile& operator =(const ConfigFile&) = delete;
        ConfigFile(const ConfigFile&&) = delete;
        ConfigFile& operator =(const ConfigFile&&) = delete;

        static ConfigFile& Get();
        ~ConfigFile();

        void Setup(const std::string& configFileName);
        std::tuple<std::string, bool> Read(const std::string& key);
        void Write(const std::string& key, const std::string& value) const;
        bool IsReadable() const;

    private:
        // 构造函数放在私有声明中,防止有其它访问方法来解决类实例
        ConfigFile();
        
    private:
        std::string config_file_name_;
        config_file_parser::ConfigFileParser* config_file_parser_ = nullptr;
    };
}
