#pragma once

#include <cassert>

#define BIT(n) (1 << n)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#if defined HZ_PLATFORM_WINDOWS
	#ifdef HZ_SHARED_LIB
		#define HZAPI __declspec(dllexport)
	#else
		#define HZAPI __declspec(dllimport)
	#endif
#elif defined HZ_PLATFORM_UNIX
	#ifdef HZ_SHARED_LIB
		#define HZAPI __attribute__((visibility("default")))
	#else
		#define HZAPI
	#endif
#else
	#error Hazel doesn`t support other platforms yet
#endif

#ifdef _DEBUG
	#define HZ_CORE_ASSERT(x, ...) assert(x, __VA_ARGS__)
#else
	#define HZ_CORE_ASSERT(x, ...)
#endif