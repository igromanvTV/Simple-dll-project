#include "Scheduler.hpp"
#include "Luau/VM/include/lualib.h"

VTFunctionType OldSchedulerVF{NULL};
std::condition_variable CScheduler::QueueCV = {};
std::queue<std::string> CScheduler::ScriptQueue = {};


auto all_jobs() -> std::vector<int64_t> {
	std::vector<int64_t> jobs;
	int64_t task_scheduler = Defs::rbx_getscheduler();
	int64_t* current_job = *reinterpret_cast<int64_t**>(task_scheduler + Offsets::TaskScheduler::job_start);

	do {
		jobs.push_back(*current_job);
		current_job += 1;
	} while (current_job != *reinterpret_cast<int64_t**>(task_scheduler + Offsets::TaskScheduler::job_end));

	return jobs;
}

auto job_by_name(const std::string& name) -> int64_t {
	std::vector<int64_t> jobs = all_jobs();
	intptr_t last_job = 0;

	for (std::intptr_t job : jobs) {
		if (std::string* job_name = reinterpret_cast<std::string*>(job + Offsets::TaskScheduler::job_name); *job_name == name) {
			last_job = job;
			break;
		}
	}

	return last_job;
}


void SetCa1pabilities(Proto* Proto, uintptr_t* CapFlags)
{
	if (!Proto)
		return;

	Proto->userdata = CapFlags;
	for (int i = 0; i < Proto->sizep; ++i)
		SetCa1pabilities(Proto->p[i], CapFlags);
}

static uintptr_t MaxCapabilities = 0xEFFFFFFFFFFFFFFF;

int CScheduler::SchedulerHook()
{

		if (!ScriptQueue.empty())
		{

			TaskScheduler* scheduler;
			lua_State* lua1_state = (lua_State*)scheduler->lua_state();


			static std::string startScript{ ("script=Instance.new(\"LocalScript\");\t") };
			const std::string& luaScript{ (startScript + ScriptQueue.front().c_str())};

			Execution::execute_script((uintptr_t)lua1_state, luaScript);

			ScriptQueue.pop();

		}

		return 0;
}




static auto scheduler_hook(lua_State* rl) -> int
{

	CScheduler::SchedulerHook();
	return 0;
}

void CScheduler::Initialize()
{

	TaskScheduler* scheduler;
	lua_State* ua_state = (lua_State*)scheduler->lua_state();



		lua_getglobal(ua_state, "game");
		lua_getfield(ua_state, -1, "GetService");
		lua_pushvalue(ua_state, -2);
		lua_pushstring(ua_state, "RunService");
		lua_pcall(ua_state, 2, 1, 0);

		lua_getfield(ua_state, -1, "Stepped");
		lua_getfield(ua_state, -1, "Connect");
		lua_pushvalue(ua_state, -2);
		lua_pushcfunction(ua_state, scheduler_hook,0);
		lua_pcall(ua_state, 2, 0, 0);
		lua_pop(ua_state, 2);

	
		
}



void CScheduler::AddScript(const std::string& Script)
{
	{	
		ScriptQueue.push(Script);

	}
}