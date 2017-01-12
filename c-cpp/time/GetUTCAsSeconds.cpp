std::string getUTC() 
{
	auto timestamp = std::chrono::seconds(std::time(nullptr));
	int seconds = std::chrono::seconds(timestamp).count();
	auto str = std::to_string(seconds);
	return str;
}