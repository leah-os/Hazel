#include <Hazel.h>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Hazel::Layer
{
public:
	GameLayer() { ; }
	~GameLayer() { ; }

	void OnAttach() override
	{
		model.LoadModel("res/models/AR_15.gltf");
		shader.reset(Hazel::Shader::Create("res/shaders/basic.shader"));
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		Hazel::PerspectiveCamera camera(60.0f, (float)1280 / 720, 0.1f, 100.0f);
		glm::mat4 view;
		glm::mat4 transform = glm::mat4(1.0f);

		view = glm::lookAt(glm::vec3(0.0f, 1.6f, 3.0f),
						   glm::vec3(0.0f, 0.0f, 0.0f),
						   glm::vec3(0.0f, 1.0f, 0.0f)
		);

		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		transform = glm::rotate(transform, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale));

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			degrees--;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			degrees++;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			scale += 0.005f;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			scale -= 0.005f;
		Hazel::Renderer::BeginScene(camera);

		shader->Bind();

		shader->SetMat4("view", view);
		shader->SetMat4("proj", camera.GetProjectionMatrix());
		shader->SetMat4("transform", transform);
		shader->SetFloat3("ObjColor", glm::vec3(color[0], color[1], color[2]));
		shader->SetFloat3("LightPos", glm::vec3(5.0, 5.0, 5.0));
		shader->SetFloat3("LightColor", glm::vec3(light[0], light[1], light[2]));

		model.Draw();

		Hazel::Renderer::EndScene();
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

	}
private:
	Hazel::Model model;
	Hazel::Ref<Hazel::Shader> shader = nullptr;

	float degrees = 0;
	float scale = 1.0;
	float color[3] = { 0.5f, 0.5f, 0.5f };
	float light[3] = { 1.0f, 1.0f, 1.0f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new Hazel::ImGuiLayer());
		PushLayer(new GameLayer());
	}
	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}