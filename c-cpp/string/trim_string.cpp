// trim from start
static inline std::string& ltrim(std::string &s) 
{
	s.erase(s.begin(), 
			std::find_if(s.begin(), 
						 s.end(),
						 std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string& rtrim(std::string &s) 
{
	s.erase(std::find_if(s.rbegin(), 
						 s.rend(),
						 std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			s.end());
	return s;
}

// trim from both ends
static inline std::string& trim(std::string &s) 
{
	return ltrim(rtrim(s));
}

///下面这是第二个版本, 上面的这个版本无法和UE4一起编译
///可能是因为使用了比较新的头文件之类的东西导致的
///下面的这个版本更好地使用了C++11的特性
static inline std::string trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}
