#pragma once

#include <glm/glm.hpp>

namespace Hazel
{

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float FOVY, float aspect_ratio, float near = 0.1f, float far = 100.0f);
		~PerspectiveCamera() {}

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
		void UpdateProjectionMatrix(float ViewportWidth, float ViewportHeight);

	private:
		float m_FOV, m_AspectRatio, m_Near, m_Far;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;

		float m_Rotation = 0.0f;

	};

}