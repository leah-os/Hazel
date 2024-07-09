cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
endif()

set(SourceFiles 
    src/Hazel/Application.cpp src/Hazel/Log.cpp src/Hazel/Layer.cpp src/Hazel/LayerStack.cpp
    src/Hazel/ImGui/ImGuiBuild.cpp
    src/Hazel/ImGui/ImGuiLayer.cpp
)

set(HeaderFiles 
    src/Hazel.h
    src/Hazel/Layer.h src/Hazel/LayerStack.h src/Hazel/Input.h src/Hazel/KeyCodes.h src/Hazel/MouseCodes.h
    src/Hazel/Application.h src/Hazel/Core.h src/Hazel/EntryPoint.h src/Hazel/Log.h src/Hazel/Window.h
    src/Hazel/Events/Event.h src/Hazel/Events/ApplicationEvent.h src/Hazel/Events/KeyEvent.h src/Hazel/Events/MouseEvent.h
    src/Hazel/ImGui/ImGuiLayer.h
)

add_library(Hazel STATIC ${SourceFiles} ${HeaderFiles})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles} ${HeaderFiles}) 

if(UNIX)
    target_compile_definitions(Hazel 
            PRIVATE HZ_PLATFORM_UNIX
    )
    target_sources(Hazel
            PRIVATE src/Platform/Unix/UnixWindow.cpp
            PRIVATE src/Platform/Unix/UnixWindow.h
            PRIVATE src/Platform/Windows/WindowsInput.cpp
            PRIVATE src/Platform/Windows/WindowsInput.h
    )
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES src/Platform/Unix/UnixWindow.cpp src/Platform/Unix/UnixWindow.h 
                                                        src/Platform/Windows/WindowsInput.cpp src/Platform/Windows/WindowsInput.h)
elseif(WIN32)
    target_compile_definitions(Hazel 
            PRIVATE HZ_PLATFORM_WINDOWS
    )
    target_sources(Hazel
            PRIVATE src/Platform/Windows/WindowsWindow.cpp
            PRIVATE src/Platform/Windows/WindowsWindow.h
            PRIVATE src/Platform/Windows/WindowsInput.cpp
            PRIVATE src/Platform/Windows/WindowsInput.h

    )
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES src/Platform/Windows/WindowsWindow.h src/Platform/Windows/WindowsWindow.cpp
                                                        src/Platform/Windows/WindowsInput.cpp src/Platform/Windows/WindowsInput.h)
endif()

target_include_directories(
    Hazel
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/src"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/glm"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/imgui"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/glfw/include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/glad/include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/spdlog/include"
)

if(WIN32)
    target_link_libraries(Hazel PRIVATE opengl32)
elseif(UNIX)
    target_link_libraries(Hazel PRIVATE GL)
endif()

target_link_libraries(
        Hazel
        PRIVATE glfw
        PRIVATE glad
        PRIVATE ImGui
)