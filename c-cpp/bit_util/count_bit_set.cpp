unsigned int get_bit_sets(unsigned int v)
{
    unsigned int c = 0;
    for (c = 0; v; c++) {
        v &= v - 1;
    }
}