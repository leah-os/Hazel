#pragma once

#include <memory>
#include <cassert>

#include "Log.h"

#define BIT(n) (1 << n)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#if defined HZ_PLATFORM_WINDOWS
	#define HZ_DEBUG_BREAK __debugbreak()
#elif defined HZ_PLATFORM_UNIX
	#include <signal.h>
	#define HZ_DEBUG_BREAK raise(SIGTRAP)
#else
	#error Hazel doesn`t support other platforms yet
#endif

#ifdef _DEBUG
	#define HZ_CORE_ASSERT(x) assert((x))
#else
	#define HZ_CORE_ASSERT(x)
#endif

namespace Hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}