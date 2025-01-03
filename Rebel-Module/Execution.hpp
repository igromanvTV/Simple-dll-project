#pragma once
#include "TaskScheduler.h"

#include "Luau/Compiler/include/Luau/BytecodeBuilder.h"
#include "Luau/Compiler/include/Luau/Compiler.h"
#include "Luau/Common/include/Luau/BytecodeUtils.h"
#include "Compressor/include/xxhash.h"
#include "Compressor/include/zstd.h"
#include <future>
#include <sstream>
#include "Luau/Compiler/include/luacode.h"
#include "Luau/VM/include/lua.h"




class CBytecodeEncoder : public Luau::BytecodeEncoder
{
	inline void encode(uint32_t* Data, size_t Count) override
	{
		for (auto i = 0u; i < Count;)
		{
			auto& Opcode = *(uint8_t*)(Data + i);
			i += Luau::getOpLength(LuauOpcode(Opcode));
			Opcode *= 227;
		}
	}
};



namespace Identity
{



	static auto set_context(uintptr_t thread, int level)
	{

		uintptr_t userdata = *reinterpret_cast<uintptr_t*>(thread + 120);
		*reinterpret_cast<uintptr_t*>(userdata + 0x30) = level;
		*reinterpret_cast<uintptr_t*>(userdata + 0x48) = max_capabilities;

	}

	static auto get_context(uintptr_t thread)
	{
		uintptr_t userdata = *reinterpret_cast<uintptr_t*>(thread + 120);

		return *reinterpret_cast<uintptr_t*>(userdata + 0x30);
	}
}


namespace Execution
{



	static auto compress_bytecode(std::string source) -> std::string
	{
		const auto data_size = source.size();
		const auto max_size = ZSTD_compressBound(data_size);
		auto buffer = std::vector<char>(max_size + 8);

		strcpy_s(&buffer[0], buffer.capacity(), "RSB1");
		memcpy_s(&buffer[4], buffer.capacity(), &data_size, sizeof(data_size));

		const auto compressed_size = ZSTD_compress(&buffer[8], max_size, source.data(), data_size, ZSTD_maxCLevel());
		if (ZSTD_isError(compressed_size))
			throw std::runtime_error("Failed to compress the bytecode.");

		const auto size = compressed_size + 8;
		const auto key = XXH32(buffer.data(), size, 42u);
		const auto bytes = reinterpret_cast<const uint8_t*>(&key);

		for (auto i = 0u; i < size; ++i)
			buffer[i] ^= bytes[i % 4] + i * 41u;

		return std::string(buffer.data(), size);
	}


	static void Set1Capabilities(Proto* Proto, uintptr_t* CapFlags)
	{
		if (!Proto)
			return;

		Proto->userdata = CapFlags;
		for (int i = 0; i < Proto->sizep; ++i)
			Set1Capabilities(Proto->p[i], CapFlags);
	}



	static uintptr_t DummyScript = 0;
	static auto execute_script(uintptr_t state, std::string source) -> void
	{
		if (source.empty())
			return;
	lua_State* state2 = lua_newthread((lua_State*)state);
	static auto encoder = CBytecodeEncoder();
	std::string a = Luau::compile(source, { }, { }, &encoder);
	std::string bytecode = compress_bytecode(a);
		if (Defs::rbx_luavmload((int64_t)state2, &bytecode, "@Skid", 0) != 0)
		{
			Defs::rbx_print(3, Luau::compile(source).c_str() + 1);
			return;
		}
		else
		{
			Set1Capabilities(((Closure*)lua_topointer((lua_State*)state2, -1))->l.p, & max_capabilities);
			Defs::rbx_taskDef((int64_t)state2);


		}
	}
}
