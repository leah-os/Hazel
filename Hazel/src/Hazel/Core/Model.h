#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include <assimp/scene.h>

#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	struct Material
	{

	};

	class Mesh
	{
	public:
		void SetupMesh()
		{
			VAO.reset(VertexArray::Create());
			VBO.reset(VertexBuffer::Create(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex)));
			BufferLayout layout = {
				{ ComponentType::Float3, "a_Position" },
				{ ComponentType::Float3, "a_Normal" },
				{ ComponentType::Float2, "a_TexCoord" }
			};
			VBO->SetLayout(layout);
			EBO.reset(IndexBuffer::Create(&m_Indices[0], m_Indices.size()));
			VAO->AddVertexBuffer(VBO);
			VAO->SetIndexBuffer(EBO);
		}
		void Draw() const;
	public:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
	private:
		Ref<VertexArray> VAO = nullptr;
		Ref<VertexBuffer> VBO = nullptr;
		Ref<IndexBuffer> EBO = nullptr;
	};

	class Model
	{
	public:
		bool LoadModel(const char* filename);
		void Draw() const;
	private:
		void processNode(const aiNode* node, const aiScene* scene);
		Mesh processMesh(const aiMesh* aimesh, const aiScene *scene);
	private:
		std::vector<Mesh> m_Meshes;
	};

}