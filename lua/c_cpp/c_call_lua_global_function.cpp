static int C_Call_Lua_Function(lua_State* L)
{
	//push lua function to stack
	lua_getglobal(L, "lua_function_name");

	//push the argument to stack
	lua_pushxxx(L, xxx);

	// 1 argument, 0 return value, 调用成功返回默认值0
	if (lua_pcall(L, 1, 0, 0) != 0) 
	{
		// failed here ...
		return -1;
	}

	return 0;
}