#include "Base.h"
#include "Model.h"
#include "Hazel/Renderer/Renderer.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Hazel
{
	void Mesh::Draw() const
	{
		Renderer::Submit(VAO);
	}

	void Model::Draw() const
	{
		for (int i = 0; i < m_Meshes.size(); i++) {
			m_Meshes[i].Draw();
		}
	}

	bool Model::LoadModel(const char* filename)
	{
		Assimp::Importer importer;
		HZ_CORE_INFO("Model {} is loading ...", filename);
		
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
		
		if (scene == nullptr) {
			HZ_CORE_WARN(importer.GetErrorString());
			return false;
		}
		
		processNode(scene->mRootNode, scene);
		for (int i = 0; i < m_Meshes.size(); i++) {
			m_Meshes[i].SetupMesh();
		}
		HZ_CORE_INFO("Model loaded {}", m_Meshes.size());
		return true;
	}

	void Model::processNode(const aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			const auto& aimesh = scene->mMeshes[node->mMeshes[i]];
			Mesh mesh = processMesh(aimesh, scene);
			m_Meshes.push_back(mesh);
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(const aiMesh* aimesh, const aiScene* scene)
	{
		Mesh mesh;
		HZ_CORE_INFO("Mesh {} has {} vertices and {} indices", aimesh->mName.C_Str(), aimesh->mNumVertices, aimesh->mNumFaces);
		for (unsigned int j = 0; j < aimesh->mNumVertices; j++) {
			glm::vec2 texcoords(0.0);
			if (aimesh->mTextureCoords[0]) {
				texcoords = glm::vec2(aimesh->mTextureCoords[0][j].x, aimesh->mTextureCoords[0][j].y);
			}
			Vertex vt = {
				glm::vec3(aimesh->mVertices[j].x, aimesh->mVertices[j].y, aimesh->mVertices[j].z),
				glm::vec3(aimesh->mNormals[j].x, aimesh->mNormals[j].y, aimesh->mNormals[j].z),
				texcoords
			};
			mesh.m_Vertices.push_back(vt);
		}
		for (unsigned int j = 0; j < aimesh->mNumFaces; j++)
		{
			aiFace face = aimesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; k++) {
				mesh.m_Indices.push_back(face.mIndices[k]);
			}
		}
		return mesh;
	}

}