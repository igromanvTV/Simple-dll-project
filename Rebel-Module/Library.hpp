#pragma once
#include "Luau/VM/include/lualib.h"
#include "Luau/VM/src/lmem.h"
#include "Luau/VM/src/lstate.h"
#include "Luau/VM/src/lapi.h"
#include "Luau/VM/src/lgc.h"



class Library
{
public:
	virtual void Initialize(lua_State*) {};
};