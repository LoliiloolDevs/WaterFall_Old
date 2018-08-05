#include "Includes.h"
#include "luac_execution.hpp"

/* 
WaterFall LuaC Leaked , OLD LuaC Source of WaterFall , you're allowed to use it ONLY if you credit me ! 

For update addresses : roblox_lua.h
Last update : 08/05/2018

Retcheck by eternal
FreeConsole Bypass by idk who :/ 
*/

void Console(const char*title)
{
	AllocConsole();
	SetConsoleTitleA(title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConHan = GetConsoleWindow();
	::SetWindowPos(ConHan, NULL, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConHan, SW_NORMAL);
}
void RblxConsole()
{
	DWORD Rblx;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &Rblx);
	*(BYTE*)(&FreeConsole) = 0xC3;
}

void luastatescan()
{
	DWORD Scc = *(DWORD*)(ScriptContext + 0x2);
	ScriptContextLs = Module::ScriptContextScan((char*)&Scc);
	lua_States = ScriptContextLs + 56 * 1 + 164 + *(DWORD *)(ScriptContextLs + 56 * 1 + 164);
} 

std::string in() {
	std::string execute;
	getline(std::cin, execute);
	return execute;
}

void Main()
{
	RblxConsole();
	Console("WaterFall_LuaC");
	std::cout << "\nWelcome to the old source of WaterFall LuaC" << std::endl;
	std::cout << "Exploit made by NoBye" << std::endl;
	Sleep(1200);
	std::cout << "================================================" << std::endl;
	std::cout << "Scanning...";
	Sleep(650);
	luastatescan();
	std::cout << "OK" << std::endl;
	std::cout << "For use the LuaC executor just enter the name of file with extension like : sparkles.txt or fire.luac" << std::endl;
	while (true) {
		try {
			std::cout << "=> ";
			std::string inp = in();
			Execution(inp);
		}
		catch (std::exception) {

		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&Main, NULL, NULL, NULL);
	}
	return TRUE;
}