#pragma once

#include <glad/gl.h>

#include "Hazel/Renderer/Texture.h"

namespace Hazel {

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& imagePath, TextureType type);
		~OpenGLTexture();

		void Bind() const override;
		void Unbind() const override;

	private:
		GLenum m_TextureType;
		unsigned int m_RendererID;
	};

}