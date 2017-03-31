/**
 * 重命名一个文件到另一个文件, 如果目标文件已经存在则覆盖它的内容
 * 
 * @param oldFullPathName
 * @param newFullPathName
 * 
 * @return 0表示发生了错误, 非0表示成功
 */

static inline int rename_file(const std::string& oldFullPathName, 
                              const std::string& newFullPathName)
{
    return MoveFileEx(oldFullPathName.c_str(), 
                      newFullPathName.c_str(), 
                      MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
}
