cmake_minimum_required(VERSION 3.10)

set(SourceFiles 
    src/Hazel/Application.cpp src/Hazel/Log.cpp)

set(HeaderFiles 
    src/Hazel.h    
    src/Hazel/Application.h src/Hazel/Core.h src/Hazel/EntryPoint.h src/Hazel/Log.h src/Hazel/Window.h
    src/Hazel/Events/Event.h src/Hazel/Events/ApplicationEvent.h src/Hazel/Events/KeyEvent.h src/Hazel/Events/MouseEvent.h
)

add_library(Hazel SHARED ${SourceFiles} ${HeaderFiles})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles} ${HeaderFiles}) 

if(UNIX)
    target_compile_definitions(Hazel 
            PRIVATE HZ_PLATFORM_UNIX
            PRIVATE HZ_STATIC_LIB
    )
    target_sources(Hazel
            PRIVATE src/Platform/Unix/UnixWindow.cpp
            PRIVATE src/Platform/Unix/UnixWindow.h
    )
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES src/Platform/Unix/UnixWindow.cpp src/Platform/Unix/UnixWindow.h)
elseif(WIN32)
    target_compile_definitions(Hazel 
            PRIVATE HZ_PLATFORM_WINDOWS
            PRIVATE HZ_BUILD_DLL
    )
    target_sources(Hazel
            PRIVATE src/Platform/Windows/WindowsWindow.cpp
            PRIVATE src/Platform/Windows/WindowsWindow.h
    )
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES src/Platform/Windows/WindowsWindow.h src/Platform/Windows/WindowsWindow.cpp)
endif()

target_include_directories(
    Hazel
    PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/src/Hazel"
    PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/vendor/glfw/include"
    PUBLIC "${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include"
)

if(WIN32)
    target_link_libraries(Hazel opengl32)
endif()

target_link_libraries(
    Hazel glfw
)