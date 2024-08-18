#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Hazel/Core/Base.h"
#include "OpenGLContext.h"

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle && "Window handle is nullptr!");
	}
	OpenGLContext::~OpenGLContext()
	{
		;
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int version = gladLoadGL(glfwGetProcAddress);
		if (version == 0) {
			HZ_CORE_ERROR("Couldn`t initialize OpenGL context");
			HZ_CORE_ASSERT(version && "Couldn`t initialize OpenGL context");
		}
		HZ_CORE_INFO("OpenGL Renderer: ");
		HZ_CORE_INFO("    Vendor: {}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("    Renderer: {}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("    OpenGL Version: {0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	void OpenGLContext::SwapBuffers()
	{
		int width, height;
		glfwGetFramebufferSize(m_WindowHandle, &width, &height);
		glViewport(0, 0, width, height);
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

}