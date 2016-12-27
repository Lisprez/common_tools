void modify_content(const std::string& filePath, std::map<std::string, std::string>& modifyContent)
{
	if (IsEndWith(filePath, ".ocs") || IsEndWith(filePath, ".obj")) {
		auto content = std::make_shared<std::vector<std::string>>();
		std::ifstream file_before_modify(filePath);
		std::string line{};

		while (std::getline(file_before_modify, line))
		{
			debug2output("%s\n", line.c_str());
			if (line.empty())
			{
				continue;
			}
			content->push_back(line);
		}
		file_before_modify.close();

		for (auto& x : modifyContent)
		{
			std::regex reg(x.first);
			std::string replacement(x.second);
			for (auto& line_ : *content)
			{
				std::string result = std::regex_replace(line_, reg, replacement);
				line_ = result;
				debug2output("%s\n", line_.c_str());
			}
		}

		std::ofstream file_after_modify(filePath);
		for (auto& line_ : *content)
		{
			file_after_modify << line_ << "\n";
		}
		file_after_modify.close();
	}
}
