/**
 * 将string转换成wstring
 * 
 * @param s
 * 
 * @return std::wstring
 */
std::wstring string2wstring(const std::string& s) 
{
    std::wstring ws{};
    ws.assin(s.begin(), s.end());
}

/**
 * 将wstring转换成string
 * 
 * @param ws
 * 
 * @return std::string
 */
std::string wstring2string(const std::wstring& ws) 
{
    std::string s{};
    s.assign(ws.begin(), ws.end());
}
