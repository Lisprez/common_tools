static bool IsDirExist(const std::string& directoryName)
{
	DWORD file_type = GetFileAttributesA(directoryName.c_str());
	if (file_type == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}

	if (file_type & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}

	return false;
}

static std::string preprocess(const std::string& foldPath)
{
	size_t len = foldPath.length();
	if (foldPath[len - 1] == '\\')
	{
		return foldPath.substr(0, len-1);
	}
	else
	{
		return foldPath;
	}
}

bool CreateFolder(const std::string& foldPath)
{
	if (foldPath.empty())
	{
		return false;
	}

	std::string inner_folder_path = preprocess(foldPath);
	size_t last_backslash_index = inner_folder_path.find_last_of("\\");

	if (last_backslash_index == std::string::npos) 
	{
		// 表示是一级的相对目录，直接创建
		if (!IsDirExist(inner_folder_path))
		{
			CreateDirectory(inner_folder_path.c_str(), nullptr);
		}
		
	}
	else
	{
		std::string parent_dir = inner_folder_path.substr(0, last_backslash_index);
		std::cout << parent_dir << std::endl;
		if (IsDirExist(parent_dir))
		{
			CreateDirectory(inner_folder_path.c_str(), nullptr);
		}
		else
		{
			CreateFolder(parent_dir);
			CreateDirectory(foldPath.c_str(), nullptr);
		}
	}

	return true;
}
