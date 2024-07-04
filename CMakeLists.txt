cmake_minimum_required(VERSION 3.10)

project(
	HazelEngine
	VERSION 0.1
	LANGUAGES C CXX
)

add_subdirectory(${CMAKE_SOURCE_DIR}/Hazel)
add_subdirectory(${CMAKE_SOURCE_DIR}/Sandbox)
add_subdirectory(${CMAKE_SOURCE_DIR}/Hazel/vendor/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/Hazel/vendor/glad)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT Sandbox)