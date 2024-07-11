#pragma once

#include <string>

namespace Hazel {
	
	enum class ShaderType {
		VertexShader = 0,
		FragmentShader
	};

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& filePath);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		ShaderProgramSource ParseShader(const std::string& filePath);
		unsigned int CompileShader(unsigned int type, const char* source);
		unsigned int CreateShader(const std::string& VertexSource, const std::string& FragmentSource);
	private:
		unsigned int m_Id;
	};

}