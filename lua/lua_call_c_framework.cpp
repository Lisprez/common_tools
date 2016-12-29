#include "lua.h"

int function_name(lua_State* L) {
	// operation here
	// todo

	// The number of object push to the lua stack
	return 0;
}

const struct luaL_Reg myLib[] = {
	{"export_name", function_name},
	{nullptr, nullptr}
};

// This is for lua use interface like this:
// require("LIB_NAME")
// here the LIB_NAME.dll is in the lua find path
extern "C" __declspec(dllexport) int luaopen_LIB_NAME(lua_State* L)
{
	luaL_register(L, "LIB_NAME", myLib);

	return 0;
}