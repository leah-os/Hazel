#include <Hazel.h>
#include <glad/gl.h>

#include "imgui.h"

#include <iostream>

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

class GameLayer : public Hazel::Layer
{
public:
	GameLayer() { ; }
	~GameLayer() { ; }

	void OnAttach() override
	{
		HZ_INFO("Game Layer attached");

		objmesh = Hazel::HzModel::LoadModel("res/models/alfa147.obj");

		m_VertexBuffer = Hazel::VertexBuffer::Create(objmesh->GetVertices(), objmesh->GetVertexSize());

		Hazel::BufferLayout layout = {
			{Hazel::ComponentType::Float3, "a_Position" },
			{Hazel::ComponentType::Float3, "a_Normal" },
			{Hazel::ComponentType::Float2, "a_TexCoord" },
		};
		m_VertexBuffer->SetLayout(layout);

		va.reset(Hazel::VertexArray::Create());
		va->AddVertexBuffer(m_VertexBuffer);

		glClearColor(0.8f, 0.8f, 0.8f, 1);
		
		shader.reset(Hazel::Shader::Create("res/shaders/lightning.shader"));

		texture = Hazel::Texture::Create("res/sprites/Livery.png");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OnUpdate() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		glm::mat4 model = glm::mat4(1.0f);
		Hazel::PerspectiveCamera camera(60.0f, (float)1280 / 720, 0.1f, 100.0f);

		view = glm::lookAt(cameraPos,
						   glm::vec3(0.0f, 0.0f, 0.0f),
						   cameraUp);

		HZ_CORE_INFO("{}", cameraPos + cameraFront);

		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
		//view  = glm::translate(view, glm::vec3(0, -1.2, -5.0));

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			degrees--;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			degrees++;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			cameraPos -= 0.05f * cameraFront;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			cameraPos += 0.05f * cameraFront;
		view = glm::scale(view, glm::vec3(scale));

		shader->Bind();
		shader->SetMat4("view", view);
		shader->SetMat4("proj", camera.GetProjectionMatrix());
		shader->SetMat4("model", model);
		shader->SetFloat3("ObjColor", glm::vec3(color[0], color[1], color[2]));
		shader->SetFloat3("LightPos", glm::vec3(5.0, 5.0, 5.0));
		shader->SetFloat3("LightColor", glm::vec3(light[0], light[1], light[2]));

		texture->Bind();

		Hazel::Renderer::Submit(va, objmesh);
		//va->Bind();
		//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		//glDrawArrays(GL_TRIANGLES, 0, objmesh->GetVertexCount());
	}

	void OnImGuiRender() override
	{
		bool active = true;
		ImGui::Begin("Light settings", &active);

		ImGui::ColorEdit3("Color", color);
		ImGui::ColorEdit3("Light", light);

		ImGui::End();
	}

	void OnDetach() override
	{
		HZ_INFO("Game Layer detached");
	}
private:
	float scale = 1;
	float degrees = 0;

	std::shared_ptr<Hazel::VertexArray> va;
	Hazel::VertexBuffer* m_VertexBuffer;
	Hazel::IndexBuffer* m_IndexBuffer;
	std::unique_ptr<Hazel::Shader> shader;

	Hazel::Texture* texture;

	std::shared_ptr<Hazel::HzModel> objmesh;

	glm::vec3 cameraPos   = glm::vec3(0.0f,  1.6f,  3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, -0.5f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f,  1.0f,  0.0f);

	float color[3] = { 0.5f, 0.5f, 0.5f };
	float light[3] = { 1.0f, 1.0f, 1.0f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		HZ_INFO("Sandbox started");
		PushLayer(new Hazel::ImGuiLayer());
		PushLayer(new GameLayer());
	}
	~Sandbox()
	{
		HZ_INFO("Sandbox terminated!");
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}