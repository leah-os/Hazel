#include "stb_image.h"
#include "Hazel/Core.h"
#include "OpenGLTexture.h"

namespace Hazel {

	GLenum TextureTypeToOpenGLenum(TextureType type);

	OpenGLTexture::OpenGLTexture(const std::string& imagePath, TextureType type)
	{
		m_TextureType = TextureTypeToOpenGLenum(type);

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);

		if (!data) {
			HZ_CORE_ASSERT(data && "Couldn`t load image from file");
			HZ_CORE_WARN("Couldn`t load image from file {}", imagePath);
		}

		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenTextures(1, &m_RendererID);
		glBindTexture(m_TextureType, m_RendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(m_TextureType);

		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::Bind() const
	{
		glBindTexture(m_TextureType, m_RendererID);
	}
	
	void OpenGLTexture::Unbind() const
	{
		glBindTexture(m_TextureType, 0);
	}

	GLenum TextureTypeToOpenGLenum(TextureType type)
	{
		switch (type) {
			case TextureType::Texture1D:			return GL_TEXTURE_1D;
			case TextureType::Texture2D:			return GL_TEXTURE_2D;
			case TextureType::Texture3D:			return GL_TEXTURE_3D;
			case TextureType::TextureBuffer:		return GL_TEXTURE_BUFFER;
			case TextureType::TextureCubemap:		return GL_TEXTURE_CUBE_MAP;
			case TextureType::TextureRectangle:		return GL_TEXTURE_RECTANGLE;
			default:								HZ_CORE_ASSERT(false && "Wrong Texture Type"); return GL_NONE;
		}
		HZ_CORE_ASSERT(false && "Wrong Texture Type");
		return GL_NONE;
	}

}