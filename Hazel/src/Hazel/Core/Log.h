#pragma once

#include <memory>
#include <sstream>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include <glm/glm.hpp>

template<>
struct fmt::formatter<glm::mat4> : fmt::formatter<std::string>
{
	auto format(glm::mat4 matrix, format_context& ctx) const -> decltype(ctx.out())
	{
		std::stringstream ss;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ss << matrix[i][j] << " ";
			}
			ss << std::endl;
		}
		return fmt::format_to(ctx.out(), ss.str());
	}
};

template<>
struct fmt::formatter<glm::vec3> : fmt::formatter<std::string>
{
	auto format(glm::vec3 vector, format_context& ctx) const -> decltype(ctx.out())
	{
		std::stringstream ss;
		ss << vector.x << " " << vector.y << " " << vector.z << std::endl;
		return fmt::format_to(ctx.out(), ss.str());
	}
};

namespace Hazel {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define HZ_CORE_TRACE(...)		::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)		::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)		::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)		::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)		::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define HZ_TRACE(...)			::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)			::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)			::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)			::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)		::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)