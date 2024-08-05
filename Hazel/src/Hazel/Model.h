#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Hazel {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	class HzModel
	{
	public:
		HzModel() { }
		static std::unique_ptr<HzModel> LoadModel(const std::string& filename);

		const float* GetVertices() { return (const float *)& m_Vertices[0]; }
		unsigned int GetVertexSize() { return m_Vertices.size() * sizeof(Vertex); }
		unsigned int GetVertexCount() { return m_Vertices.size(); }

	private:
		std::vector<Vertex> m_Vertices;
	};

}