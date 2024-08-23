cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
endif()

set(CORE_PATH "src/Hazel/Core")

set(SourceFiles 
    src/Hazel/ImGui/ImGuiLayer.cpp src/Hazel/ImGui/ImGuiBuild.cpp
    ${CORE_PATH}/Application.cpp ${CORE_PATH}/Log.cpp ${CORE_PATH}/Layer.cpp ${CORE_PATH}/LayerStack.cpp ${CORE_PATH}/Model.cpp src/Hazel/Renderer/Camera.cpp
    src/Hazel/Renderer/Renderer.cpp src/Hazel/Renderer/Buffer.cpp src/Hazel/Renderer/Shader.cpp  src/Hazel/Renderer/VertexArray.cpp src/Hazel/Renderer/Texture.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp src/Platform/OpenGL/OpenGLContext.cpp src/Platform/OpenGL/OpenGLShader.cpp src/Platform/OpenGL/OpenGLVertexArray.cpp src/Platform/OpenGL/OpenGLTexture.cpp
    src/Platform/OpenGL/OpenGLRendererAPI.cpp src/Hazel/Renderer/RendererAPI.cpp src/Hazel/Renderer/RenderCommand.cpp
)                                                                                                                                                           

set(HeaderFiles 
    src/Hazel.h
    ${CORE_PATH}/Timestep.h
    src/Hazel/Core/Timestep.h
    src/Hazel/ImGui/ImGuiLayer.h
    ${CORE_PATH}/Application.h ${CORE_PATH}/Base.h ${CORE_PATH}/Log.h ${CORE_PATH}/Window.h ${CORE_PATH}/EntryPoint.h
    ${CORE_PATH}/Layer.h ${CORE_PATH}/LayerStack.h ${CORE_PATH}/Input.h ${CORE_PATH}/KeyCodes.h ${CORE_PATH}/MouseCodes.h ${CORE_PATH}/Model.h src/Hazel/Renderer/Camera.h
    src/Hazel/Events/Event.h src/Hazel/Events/ApplicationEvent.h src/Hazel/Events/KeyEvent.h src/Hazel/Events/MouseEvent.h  src/Hazel/Renderer/RendererAPI.h src/Hazel/Renderer/RenderCommand.h
    src/Hazel/Renderer/Renderer.h src/Hazel/Renderer/Buffer.h src/Hazel/Renderer/GraphicsContext.h src/Hazel/Renderer/Shader.h src/Hazel/Renderer/VertexArray.h src/Hazel/Renderer/Texture.h
    src/Platform/OpenGL/OpenGLBuffer.h src/Platform/OpenGL/OpenGLContext.h src/Platform/OpenGL/OpenGLShader.h src/Platform/OpenGL/OpenGLVertexArray.h src/Platform/OpenGL/OpenGLTexture.h
    src/Platform/OpenGL/OpenGLRendererAPI.h src/Hazel/Renderer/RendererAPI.h
) 

add_library(Hazel STATIC ${SourceFiles} ${HeaderFiles})

set_property(TARGET Hazel PROPERTY CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles} ${HeaderFiles}) 

target_compile_definitions(Hazel 
        PRIVATE HZ_PLATFORM_WINDOWS
)

target_sources(Hazel
        PRIVATE src/Platform/Windows/WindowsWindow.cpp
        PRIVATE src/Platform/Windows/WindowsWindow.h
        PRIVATE src/Platform/Windows/WindowsInput.cpp
        PRIVATE src/Platform/Windows/WindowsInput.h
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES 
        src/Platform/Windows/WindowsWindow.h src/Platform/Windows/WindowsWindow.cpp
        src/Platform/Windows/WindowsInput.cpp src/Platform/Windows/WindowsInput.h
)

target_include_directories(
    Hazel
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/src"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/glm"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/imgui"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/stbimage"
    PUBLIC  "${CMAKE_SOURCE_DIR}/Hazel/vendor/glfw/include"
    PUBLIC  "${CMAKE_SOURCE_DIR}/Hazel/vendor/assimp/include"
    PUBLIC  "${CMAKE_SOURCE_DIR}/Hazel/vendor/glad/include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Hazel/vendor/tinyobjloader/"
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
        PRIVATE stbimage
        PRIVATE tinyobjloader
        PRIVATE assimp
)