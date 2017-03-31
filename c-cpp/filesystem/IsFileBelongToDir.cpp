/**
 * 对于一个绝对路径进行处理,如果绝对路径以\结尾, 
 * 返回去掉\的字符串, 否定直接返回 
 *
 * @param foldPath 需要处理的绝对路径的字符串
 * @return std::string
 */
static std::string preprocess(const std::string& foldPath)
{
    size_t len = foldPath.length();
    if (foldPath[len - 1] == '\\')
    {
        return foldPath.substr(0, len - 1);
    }
    else
    {
        return foldPath;
    }
}

/**
 * 返回一个字符串表达的绝对路径的父路径, 
 * 不包括当前文件和目录本身 
 * 
 * @param path 文件或者目录的绝对路径
 * 
 * @return std::string
 */
static std::string get_parent_path(const std::string& path)
{
    std::string folder_path = preprocess(folderPath);
    if (folder_path.empty())
    {
        return "";
    }
    size_t index = folder_path.find_last_of('\\');
    if (index == std::string::npos)
    {
        return "";
    }
    return folder_path.substr(0, index);
}

/**
 * 判断一个文件(普通文件或者目录)是否位于另一个目录中 
 * 
 * @param fullPathFileName 用于判断的文件
 * @param fullPathDirName 目标目录
 * 
 * @return bool 
 */
static bool is_file_belong_to(const std::string& fullPathFileName, 
                              const std::string& fullPathDirName)
{
    std::string parent_path = get_parent_path(fullPathDirName);
    if (parent_path.compare(fullPathDirName) == 0) //表示文件的父目录和期望目录相同, 也就是文件在所指目录中
    {
        return true;
    }
    return false;
}
