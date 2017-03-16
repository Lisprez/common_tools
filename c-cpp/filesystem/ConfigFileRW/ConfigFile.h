#pragma once
#include <string>
#include <map>

namespace config_file_rw {

	class ConfigFile {
	public:
		ConfigFile(const std::string& fileName);
		~ConfigFile();

		std::tuple<std::string, bool> Get(const std::string& key);
		void Set(const std::string& key, const std::string& value);
		bool IsReadable() const;

	private:
		std::string file_name_;
		std::map<std::string, std::string>* key_values_ = nullptr;
		bool readable_ = false;
	};
}
