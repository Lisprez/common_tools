// Char* 字符串拷贝
// 参数:目的地址, 源地址, 欲拷贝最大字节数
void SafeStrCpy(char* dest, char* src, int max_bytes)
{
	int src_len = static_cast<int>(strlen(src)) + 1;
	if (!dest)
	{
		goto SafeStrCpy_END;
	}
	if (!src)
	{
		goto SafeStrCpy_END;
	}
	if (src_len > max_bytes)
	{
		src_len = max_bytes;
	}
	memcpy(dest, src, src_len);
	*(dest+src_len-1) = '\0';

SafeStrCpy_END:
	return;
}