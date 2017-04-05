/**
 * 安全地实现字符串的复制
 * 
 * @param dest 目标缓冲区
 * @param src 源缓冲区
 * @param max_bytes dest缓冲区的最大空间
 * 
 * @return int (由于是字符串复制,当返回值和max_bytes相等的时候, 应该知道实际有意义的复制是max_bytes-1, dest的最后一byte被填入的\0,
 *			   有任何一人指针是空的时候就返回0
 */
int SafeStrCpy(char* dest, char* src, int max_bytes)
{
	int src_len_with_zero = 0;

	if (!dest || !src)
	{
		goto SafeStrCpy_END;
	}
	
	src_len_with_zero = static_cast<int>(strlen(src)) + 1;
	if (src_len_with_zero > max_bytes)
	{
		src_len_with_zero = max_bytes;
	}
	memcpy(dest, src, src_len_with_zero);
	*(dest+src_len-1) = '\0';

SafeStrCpy_END:
	return src_len_with_zero;
}