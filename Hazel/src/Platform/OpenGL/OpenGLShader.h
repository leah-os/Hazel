#pragma once

#include "Hazel/Renderer/Shader.h"

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

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;


		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

	private:
		ShaderProgramSource ParseShader(const std::string& filePath);
		unsigned int CompileShader(unsigned int type, const char* source);
		unsigned int CreateShader(const std::string& VertexSource, const std::string& FragmentSource);


	private:
		unsigned int m_RendererID;
	};

}