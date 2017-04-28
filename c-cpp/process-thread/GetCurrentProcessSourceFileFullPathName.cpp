/**
 * 在运行时获取进程镜像文件的路径(不支持中文)
 *
 * @return std::string
 */
std::string get_process_image_file_path()
{
	char path[2048];
	GetModuleFileNameA(nullptr, path, sizeof(path));
	return path;
}