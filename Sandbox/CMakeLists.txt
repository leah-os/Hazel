cmake_minimum_required(VERSION 3.10)

add_executable(Sandbox src/main.cpp)

set(SourceFiles src/main.cpp)
set(HeaderFiles)

if(WIN32)
	add_custom_command(
		TARGET Sandbox PRE_LINK
		COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/Hazel/Debug/Hazel.dll
			${CMAKE_CURRENT_SOURCE_DIR}/Debug/Hazel.dll
	)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles} ${HeaderFiles})

target_link_libraries(Sandbox PRIVATE Hazel)
target_compile_definitions(Sandbox PRIVATE HZ_PLATFORM_WINDOWS)
target_include_directories(Sandbox
	PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/src/"
	PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include"
)