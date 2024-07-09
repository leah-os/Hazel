cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)

add_executable(Sandbox src/main.cpp)

set(SourceFiles src/main.cpp)
set(HeaderFiles)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles} ${HeaderFiles})

target_link_libraries(Sandbox PRIVATE Hazel)
target_compile_definitions(Sandbox 
	PRIVATE HZ_PLATFORM_WINDOWS
)

target_include_directories(Sandbox
	PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/src/"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/glm"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/imgui"
	PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include"
)