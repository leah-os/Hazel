#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HZAPI __declspec(dllexport)
	#else
		#define HZAPI __declspec(dllimport)
	#endif
#else
	#define HZAPI
#endif