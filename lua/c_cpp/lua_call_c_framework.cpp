#include "lua.h"

int function_name(lua_State* L) {
	// operation here
	// todo

	// m objects pushed to the lua stack
	return m;
}

const struct luaL_Reg myLib[] = {
	{"export_name", function_name},
	{nullptr, nullptr}
};

// This is for lua use interface like this:
// require("LIB_NAME")
// here the LIB_NAME.dll is in the lua find path
// 注意: LIB_NAME.dll不能被改成其它的名字,否则就无法加载,文件名要和符号表中的名字保持一致
extern "C" __declspec(dllexport) int luaopen_LIB_NAME(lua_State* L)
{
	luaL_register(L, "LIB_NAME", myLib);

	return 0;
}