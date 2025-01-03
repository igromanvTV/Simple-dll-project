#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <vector>
#include "Luau/VM/src/lstate.h"


static uintptr_t max_capabilities = 0x3FFFF00 | 0xFFFFFFFFCFFui64;
static uintptr_t  lua_state = 0;

static int64_t menu_job = 0;

#define RBX_PRINT_NORMAL 0
#define RBX_PRINT_INFO 1
#define RBX_PRINT_WARN 2
#define RBX_PRINT_ERROR 3

static auto aslr(int64_t address) -> int64_t
{
	return address + reinterpret_cast<int64_t>(GetModuleHandle(NULL));
}

namespace Offsets
{

	static int64_t decryptstate = 0xAFE360; //11.12.2024
	static int64_t print = 0x12F21D0; //11.12.2024
	static int64_t getscheduler = 0x2DD80A0; //11.12.2024
	static int64_t getstate = 0xD44D30; //11.12.2024
	static int64_t taskDefer = 0xED0220; //11.12.2024
	static int64_t spawn = 0xE4F750; //11.12.2024 .....


	static int64_t luavm_load = 0xB012F0; //11.12.2024

	namespace Proto
	{
		static int64_t SizeP = 40; //21.11.24 ?? not using
		static int64_t Add = 2; //21.11.24 ?? not using
	}

	namespace TaskScheduler
	{
		static int64_t job_start = 0x198;
		static int64_t job_end = 0x1A0;			
		static int64_t job_name = 0x90;
	}

	namespace LuaState
	{
		static int64_t userdata = 0x78;

		static int64_t top = 4; //11.12.2024

		static int64_t script_context = 0x1F8;
	}

}


namespace Defs
{
	using GetSchedulerFunction = int64_t(__cdecl*)();
	static GetSchedulerFunction rbx_getscheduler = reinterpret_cast<GetSchedulerFunction>(aslr(Offsets::getscheduler));

	using SpawnFunction = int64_t(__fastcall*)(int64_t state);
	static SpawnFunction rbx_spawn = reinterpret_cast<SpawnFunction>(aslr(Offsets::spawn));

	using DeferFunction = int64_t(__fastcall*)(int64_t state);
	static DeferFunction rbx_taskDef = reinterpret_cast<DeferFunction>(aslr(Offsets::taskDefer));

	using PrintFunction = int64_t(__fastcall*)(int type, const char* source);
	static PrintFunction rbx_print = reinterpret_cast<PrintFunction>(aslr(Offsets::print));

	using GetStateFunction = int64_t(__fastcall*)(int64_t script_context, int64_t* a1, int64_t* a2);
	static GetStateFunction rbx_getstate = reinterpret_cast<GetStateFunction>(aslr(Offsets::getstate));

	using DecryptStateFunction = int64_t(__fastcall*)(int64_t a1);
	static DecryptStateFunction decryptstate = reinterpret_cast<DecryptStateFunction>(aslr(Offsets::decryptstate));

	using LuaVmLoadFunction = int64_t(__fastcall*)(int64_t state, std::string* source, const char* chunk, int environment);
	static LuaVmLoadFunction rbx_luavmload = reinterpret_cast<LuaVmLoadFunction>(aslr(Offsets::luavm_load));

}