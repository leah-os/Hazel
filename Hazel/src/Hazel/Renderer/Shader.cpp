#include "Shader.h"
#include "Renderer.h"
#include "Hazel/Core.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(filePath);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;
	}

}