#pragma once
#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <vector>
#include <string>
#include "Update.hpp"

static class TaskScheduler {
public:
    static auto all_jobs() -> std::vector<__int64>;
    static auto job_by_name(const std::string& name) -> std::vector <__int64>;
    static auto script_context() -> __int64;
    static auto blacklist_job() -> void;
    static auto lua_state() -> __int64;
};

#endif