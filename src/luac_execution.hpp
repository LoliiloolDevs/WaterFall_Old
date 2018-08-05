#pragma once
#include "Includes.h"
#include "roblox_lua.h"

std::vector<std::string> split(std::string script) 
{
	std::vector<std::string> luacrobloxsplit;
	std::stringstream fuckdatshit(script);
	std::istream_iterator<std::string> begin(fuckdatshit);
	std::istream_iterator<std::string> end;
	std::vector<std::string> fuckbro(begin, end);
	return fuckbro;
}

void execute(std::string input) {
	try {
		std::vector<std::string> In = split(input);

		if (In.at(0) == "getfield") {
			rlua_getfield(lua_States, stoi(In.at(1)), In.at(2).c_str());
		}

		else if (In.at(0) == "getglobal") {
			getglobal(lua_States, In.at(1).c_str());
		}

		else if (In.at(0) == "setfield") {
			lua_setfield(lua_States, stoi(In.at(1)), In.at(2).c_str());
		}

		else if (In.at(0) == "pushvalue") {
			rlua_pushvalue(lua_States, stoi(In.at(1)));
		}

		else if (In.at(0) == "pushstring") {
			rlua_pushstring(lua_States, In.at(1).c_str());
		}

		else if (In.at(0) == "pushnumber") {
			rlua_pushnumber(lua_States, stoi(In.at(1)));
		}

		else if (In.at(0) == "pcall") {
			lua_bpcall(lua_States, stoi(In.at(1)), stoi(In.at(2)), stoi(In.at(3)));

		}

		else if (In.at(0) == "emptystack") {
			rlua_settop(lua_States, stoi(In.at(1)));
		}
	}
	catch (...) {}
}

void Execution(std::string file)
{
	std::ifstream the_file("C:\\WaterFall\\" + file);
	std::string s;
	std::vector<std::string> lines;
	while (std::getline(the_file, s))
	{
		execute(s);
		std::cout << s << std::endl;
	}
}