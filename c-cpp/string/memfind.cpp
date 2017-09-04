/**
 * 在二进制buf段中寻找一个子的buf段
 * 如果找到返回子串在二进制buf中的起始位置指针, 否则返回nullptr
 */
const char*  memfind(const char* src_str,
	             size_t src_len,
	             const char* sub_str,
	             size_t sub_len,
	             bool flag)
{
    if(NULL == src_str || NULL == sub_str || src_len <= 0)
    {
        return NULL;
    }

    if(src_len < sub_len)
    {
        return NULL;
    }

    const char* p;
    if (sub_len == 0)
    {
        sub_len = strlen(sub_str);
    }

    if(src_len == sub_len)
    {
        if(0 == (memcmp(src_str, sub_str, src_len)))
        {
            return src_str;
        }
        else
        {
            return NULL;
        }
    }

    if(flag)
    {
        for (int i = 0; i < src_len - sub_len; i++)
        {
            p = src_str + i;
            if(0 == memcmp(p, sub_str, sub_len))
	    {
                return p;
	    }
        }
    }
    else
    {
        for ( int i = (src_len - sub_len) ; i >= 0; i--  )
        {
            p = src_str + i;
            if ( 0 == memcmp(  p,sub_str,sub_len ) )
	    {
                return p;
            }
        }
    }

    return NULL;
}