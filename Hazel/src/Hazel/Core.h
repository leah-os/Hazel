#pragma once

#include <cassert>

#define BIT(n) (1 << n)

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HZAPI __declspec(dllexport)
	#else
		#define HZAPI __declspec(dllimport)
	#endif
#elif HZ_PLATFORM_UNIX
	#define HZAPI
#else
	#error Hazel doesn`t support other platforms yet
#endif

#ifdef _DEBUG
	#define HZ_CORE_ASSERT(x, ...) assert(x, __VA_ARGS__)
#else
	#define HZ_CORE_ASSERT(x, ...)
#endif