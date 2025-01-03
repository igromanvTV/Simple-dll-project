#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <vector>
#include "Luau/VM/include/lua.h"

static auto aslr2(int64_t address) -> int64_t
{
	return address + reinterpret_cast<int64_t>(GetModuleHandle(NULL));
}

namespace Update
{
		const uintptr_t LuaO_NilObject = aslr2(0x41132B8); // 11.12.24
		const uintptr_t LuaH_DummyNode = aslr2(0x4112A28); // 11.12.24
		const uintptr_t LuaC_step1 = aslr2(0x238C5B0); // 11.12.24
}