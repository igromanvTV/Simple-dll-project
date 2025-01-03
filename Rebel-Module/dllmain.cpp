#include "Execution.hpp"
#include "Scheduler.hpp"
#include "Communication.hpp"
#include "Luau/VM/include/lualib.h"

//Made by REx Team for you <3

void main()
{

	TaskScheduler* scheduler;
	scheduler->blacklist_job();
	lua_state = scheduler->lua_state();

	Identity::set_context(lua_state, 8);
	lua_State* test = (lua_State*)lua_state;
	Scheduler->Initialize();
	luaL_sandboxthread((lua_State*)lua_state);

	lua_createtable((lua_State*)lua_state, 0, 0);
	lua_setfield((lua_State*)lua_state, -10002, "_G");
	lua_newtable((lua_State*)lua_state);
	lua_setglobal((lua_State*)lua_state, "shared");

	Execution::execute_script(lua_state, "print('Skid module works!')");
	CCommunication communication;
	communication.InitializeScriptServer(1337);



	while (1) {
		std::string script = communication.ReceiveScript();

		Scheduler->AddScript(script.c_str());
	}
}




int __stdcall DllMain(void* Module, DWORD Reason, void* Reserve)
{
	
	if (Reason == 1)
	{
		std::thread(main).detach();
	}
	
	return true;
}