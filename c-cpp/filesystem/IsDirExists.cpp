bool IsDirExist(const std::string& directoryName)
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
