static bool id_dir_exist(const std::string& directoryName)
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

/**
 * 对一个路径进行预处理, 去除末尾的\
 *
 * @param foldPath 绝对路径
 *
 * @return std::string
 */
static std::string preprocess_path(const std::string& foldPath)
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

/**
 * 创建一个指定的目录
 *
 * @param foldPath 指定目录的绝对路径
 *
 * @return bool
 */
bool CreateFolder(const std::string& foldPath)
{
	if (foldPath.empty())
	{
		return false;
	}

	std::string inner_folder_path = preprocess_path(foldPath);
	size_t last_backslash_index = inner_folder_path.find_last_of("\\");

	if (last_backslash_index == std::string::npos) 
	{
		// 表示是一级的相对目录，直接创建
		if (!id_dir_exist(inner_folder_path))
		{
			CreateDirectory(inner_folder_path.c_str(), nullptr);
		}
		
	}
	else
	{
		std::string parent_dir = inner_folder_path.substr(0, last_backslash_index);
		if (id_dir_exist(parent_dir))
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
