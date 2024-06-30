cmake_minimum_required(VERSION 3.10)

project(Sandbox VERSION 0.1 LANGUAGES C CXX)
add_executable(Sandbox src/main.cpp)

target_compile_definitions(Sandbox PUBLIC HZ_PLATFORM_WINDOWS)

target_include_directories(Sandbox
PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/src/"
PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include"
)