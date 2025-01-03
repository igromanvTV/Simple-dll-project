#include "TaskScheduler.h"
#include "Luau/Compiler/include/Luau/Compiler.h"
#include "Luau/VM/src/lapi.h"

auto TaskScheduler::all_jobs() -> std::vector<__int64> {
    std::vector<__int64> jobs;
    __int64 task_scheduler = Defs::rbx_getscheduler();
    __int64* current_job = *reinterpret_cast<__int64**>(task_scheduler + Offsets::TaskScheduler::job_start);

    do {
        jobs.push_back(*current_job);
        current_job += 2;
    } while (current_job != *reinterpret_cast<__int64**>(task_scheduler + Offsets::TaskScheduler::job_end));

    return jobs;
}

static auto all_job_by_name(const std::string& name) -> std::vector <__int64> {
    std::vector<__int64> jobs = TaskScheduler::all_jobs();
    std::vector <__int64> last_job;

    for (__int64& job : jobs) {
        if (std::string* job_name = reinterpret_cast<std::string*>(job + Offsets::TaskScheduler::job_name); *job_name == name) {
            last_job.push_back(job);
        }
    }

    return last_job;
}

auto TaskScheduler::job_by_name(const std::string& name) -> std::vector <__int64> {
    std::vector<__int64> jobs = all_jobs();
    std::vector <__int64> last_job;

    for (__int64& job : jobs) {
        if (std::string* job_name = reinterpret_cast<std::string*>(job + Offsets::TaskScheduler::job_name); *job_name == name) {
            last_job.push_back(job);
            break;
        }
    }

    return last_job;
}

auto is_loaded()
{
    auto a = all_job_by_name("WaitingHybridScriptsJob");
      if (a.size() == 2)
      {
          return true;
      }
      else
      {
          return false;
      }
}



static __int64 blacklisted_job;
auto TaskScheduler::blacklist_job() -> void
{
    if (!is_loaded())
    {
       blacklisted_job = all_job_by_name("WaitingHybridScriptsJob")[0];
    }
    else
    {
        auto jobs = all_job_by_name("WaitingHybridScriptsJob");
        for (int i = 0; i < jobs.size(); i++)
        {
            auto script_context = *reinterpret_cast<__int64*>(jobs[i] + 504);

            __int64 arg1 = 0;
            __int64 arg2 = 0;
            __int64 state = Defs::rbx_getstate(script_context + 280, &arg1, &arg2);

            __int64 rstate = Defs::decryptstate(state + 136);
            lua_pushvalue((lua_State*)rstate, LUA_REGISTRYINDEX);

            auto table = hvalue(index2addr((lua_State*)rstate, -1));
            if (table->sizearray == 4)
                blacklisted_job = jobs[i];
        }
    }
}

auto TaskScheduler::script_context() -> __int64 {
    auto job = all_job_by_name("WaitingHybridScriptsJob");
    __int64 a2;
        for (int i = 0; i < job.size(); i++)
        {
            if (job[i] != blacklisted_job)
            {
                a2 = job[i];
                break;
            }
        }

   
    return *reinterpret_cast<__int64*>(a2 + 504);
}

auto TaskScheduler::lua_state() -> __int64 {
    __int64 sc = script_context();
    __int64 arg1 = 0;
    __int64 arg2 = 0;
    __int64 state = Defs::rbx_getstate(sc + 280, &arg1, &arg2);

    auto part = Defs::decryptstate(state + 136);
    return part;
}









