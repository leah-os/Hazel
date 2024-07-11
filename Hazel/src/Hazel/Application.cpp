#include "Input.h"
#include "Application.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/gl.h>

namespace Hazel {

	unsigned int va;
	unsigned int vb;
	unsigned int eb;


	#define HZ_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance && "Application already exists!");
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
		
		s_Instance = this;

		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,


		};
		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		glGenVertexArrays(1, &va); glBindVertexArray(va);
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		Shader shader("C:\\Dev\\Hazel\\Sandbox\\res\\shaders\\basic.shader");

		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Bind();
			glBindVertexArray(va);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_Running = false;
		return true;
	}


}