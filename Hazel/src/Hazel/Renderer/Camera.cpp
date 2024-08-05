#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	PerspectiveCamera::PerspectiveCamera(float FOV, float aspect_ratio, float near, float far)
		: m_FOV(FOV), m_AspectRatio(aspect_ratio), m_Near(near), m_Far(far)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::UpdateProjectionMatrix(float ViewportWidth, float ViewportHeight)
	{
		m_AspectRatio = ViewportWidth / ViewportHeight;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{

	}



}
