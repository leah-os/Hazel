#include "OpenGLShader.h"

#include <sstream>
#include <fstream>
#include <glad/gl.h>

#include "Hazel/Core/Base.h"

#include "glm/gtc/type_ptr.hpp"

namespace Hazel {

    OpenGLShader::OpenGLShader(const std::string& filePath)
    {
        ShaderProgramSource src = ParseShader(filePath);
        m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);
        HZ_CORE_INFO("SHADER ID: {0}", m_RendererID);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }


    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniform1i(location, value);
    }
    void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniform1iv(location, count, values);
    }
    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }
    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniform2f(location, value.x, value.y);
    }
    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniform3f(location, value.x, value.y, value.z);
    }
    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        HZ_CORE_ASSERT(location != -1 && "Uniform doesn`t exist");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    ShaderProgramSource OpenGLShader::ParseShader(const std::string& filePath)
    {
        ShaderProgramSource sourceCode;
        std::string line;
        std::stringstream ss;
        std::stringstream fs;
        std::ifstream file(filePath);
        while (getline(file, line))
        {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                {
                    while (getline(file, line) && line.find("#shader") == std::string::npos)
                        ss << line << std::endl;
                    sourceCode.VertexSource = ss.str();
                }
                if (line.find("fragment") != std::string::npos)
                {
                    while (getline(file, line) && line.find("#shader") == std::string::npos)
                        fs << line << std::endl;
                    sourceCode.FragmentSource = fs.str();
                }
            }
        }

        return sourceCode;
    }

    unsigned int OpenGLShader::CompileShader(unsigned int type, const char* source)
    {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            int maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);

            HZ_CORE_WARN("Shader compilation failed: {0}", errorLog);

            glDeleteShader(shader);
            delete[] errorLog;
            return 0;
        }
        return shader;
    }

    unsigned int OpenGLShader::CreateShader(const std::string& VertexSource, const std::string& FragmentSource)
    {
        unsigned int vtxs = CompileShader(GL_VERTEX_SHADER, VertexSource.c_str());
        unsigned int fgms = CompileShader(GL_FRAGMENT_SHADER, FragmentSource.c_str());

        unsigned int program = glCreateProgram();
        glAttachShader(program, vtxs);
        glAttachShader(program, fgms);

        glLinkProgram(program);

        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            int maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            char* infoLog = new char[maxLength];
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

            HZ_CORE_WARN("Shader linking error: {0}", infoLog);

            glDeleteProgram(program);
            glDeleteShader(vtxs);
            glDeleteShader(fgms);

            return 0;
        }

        glDeleteShader(vtxs);
        glDeleteShader(fgms);

        return program;
    }

}