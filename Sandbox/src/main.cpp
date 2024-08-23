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
		shader.reset(Hazel::Shader::Create("res/shaders/lightning.shader"));

		Hazel::Input::GetMousePos(&lastX, &lastY);
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		Hazel::PerspectiveCamera camera(60.0, 1280.0 / 720.0);
		glm::mat4 view;
		glm::mat4 transform = glm::mat4(1.0f);

		view = glm::lookAt(cameraPos,
							cameraPos + cameraFront,
						    cameraUp
		);

		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));

		float xoffset = Hazel::Input::GetMouseX() - lastX;
		float yoffset = lastY - Hazel::Input::GetMouseY();

		lastX = Hazel::Input::GetMouseX();
		lastY = Hazel::Input::GetMouseY();
		xoffset *= 0.33;
		yoffset *= 0.33;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT)) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp) * 0.01f);
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT)) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp) * 0.01f);
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			cameraPos += cameraFront * 0.1f;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			cameraPos -= cameraFront * 0.1f;

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

	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 4.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float degrees = 0;
	float scale = 1.0;
	float color[3] = { 0.5f, 0.5f, 0.5f };
	float light[3] = { 1.0f, 1.0f, 1.0f };

	float lastX, lastY;

	float yaw = -90;
	float pitch = 0;
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