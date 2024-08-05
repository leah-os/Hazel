#pragma once

#include <string>

namespace Hazel {

	enum class TextureType {
		None = 0,
		Texture1D, Texture2D, Texture3D,
		TextureRectangle, TextureCubemap, TextureBuffer
	};

	class Texture
	{
	public:
		static Texture* Create(const std::string& imagePath, TextureType type = TextureType::Texture2D);

		virtual ~Texture() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

}