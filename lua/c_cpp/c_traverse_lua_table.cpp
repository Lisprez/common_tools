/**
 * 函数的功能是遍历lua传递到C++中的Table
 *
 * @param L
 * @param table_loc table在lua栈上的逆向索引
 *
 * @return void
 */
void traverse_table(lua_State *L, int table_loc) 
{
    // 向栈顶加入一个nil，目的是为了构成一个调用lua_next的环境
    lua_pushnil(L);
    // 此时的栈情景如下:
    // -1 => nil, -2 => table

    while (lua_next(L, table_loc)) 
	{
        // -1 => value, -2 => key, -3 => table
        lua_pushvalue(L, -2);
        // -1 => key, -2 => value, -3 => key, -4 => table
        auto key = lua_tostring(L, -1);
        auto value = lua_tostring(L, -2);
        lua_pop(L, 2);
        // -1 => key, -2 => table
        // 可以看到到这里就又回到了可以调用lua_next的要求条件
    }
    // 循环结束的时候，表又被回到了栈顶端
}
