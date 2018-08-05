#pragma once
#include "Includes.h"
#include "Scan.h"
#include "ret.h"
#define luas_getglobal -10002
#define getglobal(l,g)			 robloxlua::rlua_getfield(l, luas_getglobal, g)
DWORD getfieldaddr = RoBlOxScAns(0x7298A0);
DWORD settopaddr = RoBlOxScAns(0x72BA00);
DWORD pushstringaddr = RoBlOxScAns(0x72AC40);
DWORD pushvalueaddr = RoBlOxScAns(0x72AD10);
DWORD setfieldaddr = RoBlOxScAns(0x72B630);
DWORD pushnumberaddr = RoBlOxScAns(0x72ABB0);
DWORD getmetatableaddr = RoBlOxScAns(0x729B60);
DWORD pcalladdr = RoBlOxScAns(0x72A670);
DWORD rawrjzaddr = RoBlOxScAns(0x7229C7);
DWORD ScriptContext = RoBlOxScAns(0x6C2B56);
int ScriptContextLs;
int lua_States;


namespace robloxlua {

	typedef int(__cdecl* Lua_getfield)(int LuaState, int ID, const char* Field);
	Lua_getfield rlua_getfield = (Lua_getfield)retc(getfieldaddr);

	typedef int(__cdecl* Lua_settop)(int LuaState, int ID);
	Lua_settop rlua_settop = (Lua_settop)retc(settopaddr);

	typedef int(__stdcall* Lua_pushstring)(int LuaState, const char* String);
	Lua_pushstring rlua_pushstring = (Lua_pushstring)pushstringaddr;

	typedef int(__stdcall* Lua_pushvalue)(int LuaState, int ID);
	Lua_pushvalue rlua_pushvalue = (Lua_pushvalue)retc(pushvalueaddr);

	typedef int(__cdecl* Lua_setfield)(int LuaState, int ID, const char* Field);
	Lua_setfield rlua_setfield2 = (Lua_setfield)retc(setfieldaddr);

	typedef int(__thiscall* Lua_pushnumber)(int LuaState, double Number);
	Lua_pushnumber rlua_pushnumber = (Lua_pushnumber)retc(pushnumberaddr);

	typedef signed int(__cdecl* Lua_getmetatable)(int LuaState, int ID);
	Lua_getmetatable rlua_getmetatable = (Lua_getmetatable)retc(getmetatableaddr);

	typedef int(__cdecl* Lua_pcall)(int LuaState, int NumberOfArguments, int NumberOfResults, int ErrorFunctionCallback);
	Lua_pcall rlua_pcall = (Lua_pcall)retc(pcalladdr);

}

using namespace robloxlua;
void lua_bpcall(DWORD rL, int NumberOfArguments, int NumberOfResults, int ErrorFunctionCallback)
{
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(RoBlOxScAns(0x7229C7)), "\xEB", 1, 0);
	rlua_pcall(rL, NumberOfArguments, NumberOfResults, ErrorFunctionCallback);
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(RoBlOxScAns(0x7229C7)), "\x74", 1, 0);
}
#define pop(L,n)            robloxlua::rlua_settop(L, -(n)-1)
void lua_setfield(int L, int idx, const char *k) {

	using namespace robloxlua;
	rlua_pushvalue(L, idx);
	if (rlua_getmetatable(L, -1)) {
		rlua_getfield(L, -1, "__newindex");
		rlua_pushvalue(L, -3);
		rlua_pushstring(L, k);
		rlua_pushvalue(L, -6);
		lua_bpcall(L, 3, 0, 0);
		pop(L, 3);
	}
	else {
		pop(L, 1);
		rlua_setfield2(L, idx, k);
	}
}