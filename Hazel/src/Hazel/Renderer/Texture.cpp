#include "Texture.h"
#include "Hazel/Core.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel {

	Texture* Texture::Create(const std::string& imagePath, TextureType type)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false && "RendererAPI::NONE is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLTexture(imagePath, type);
		}

		HZ_CORE_ASSERT(false && "Unknown Renderer API");
		return nullptr;
	}

}