/**
 * 返回一个无符号整形数的二进制表示中有多少位被置位
 * 
 * @param v 输入的无符号的整数
 * 
 * @return unsigned int
*/
unsigned int get_bit_sets(unsigned int v)
{
    unsigned int c = 0;
    for (c = 0; v; c++) 
	{
        v &= v - 1;
    }
}