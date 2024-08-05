#include "Core.h"
#include "Model.h"

#include "tiny_obj_loader.h"

namespace Hazel
{
	static std::string GetBaseDir(const std::string& filepath);

	std::unique_ptr<HzModel> HzModel::LoadModel(const std::string& filename)
	{
		std::unique_ptr<HzModel> model = std::make_unique<HzModel>();

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string base_dir = GetBaseDir(filename);

		std::string warn, err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), base_dir.c_str());

		if (!warn.empty()) {
			HZ_CORE_INFO("{}", warn);
		}
		if (!err.empty()) {
			HZ_CORE_WARN("{}", err);
		}
		HZ_CORE_ASSERT(ret && "Cannot load model");

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				glm::vec3 position = {
					attrib.vertices[index.vertex_index * 3 + 0],
					attrib.vertices[index.vertex_index * 3 + 1],
					attrib.vertices[index.vertex_index * 3 + 2]
				};
				glm::vec3 normal;
				glm::vec2 texcoord;
				if (index.normal_index >= 0)
					normal = {
						attrib.normals[index.normal_index * 3 + 0],
						attrib.normals[index.normal_index * 3 + 1],
						attrib.normals[index.normal_index * 3 + 2]
					};
				if (index.texcoord_index >= 0)
					texcoord = {
						attrib.texcoords[index.texcoord_index * 2 + 0],
						attrib.texcoords[index.texcoord_index * 2 + 1]
					};
				Vertex vert = {
					position,
					normal,
					texcoord
				};
				model->m_Vertices.emplace_back(vert);
			}
		}
		return model;
	}

	static std::string GetBaseDir(const std::string& filepath) {
		std::string path;
		if (filepath.find_last_of("/\\") != std::string::npos)
			path = filepath.substr(0, filepath.find_last_of("/\\"));
		else
			path = "";
		if (path.empty()) {
			path = ".";
		}
#ifdef _WIN32
		path += "\\";
#else
		path += "/";
#endif
		return path;
	}

}