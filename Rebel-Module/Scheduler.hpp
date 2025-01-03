#pragma once
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "Globals.hpp"
#include "Execution.hpp"


using VTFunctionType = uintptr_t(__fastcall*)(uintptr_t, uintptr_t, uintptr_t);
using roblox_function = std::intptr_t(__fastcall*)(std::intptr_t L);

class CScheduler
{
private:
	std::unique_ptr<std::intptr_t[]> vfClone = nullptr;
	std::intptr_t* vfBackup = nullptr;
	std::intptr_t size = 0;
public:
	std::mutex Pending;

	static std::condition_variable QueueCV;
	static std::queue<std::string> ScriptQueue;

	bool Running = true;

	static int SchedulerHook();


	void Initialize();
	void AddScript(const std::string& Script);


};

inline auto Scheduler = std::make_unique<CScheduler>();

