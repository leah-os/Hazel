#include "OpenGLShader.h"

#include <sstream>
#include <fstream>
#include <glad/gl.h>

#include "Hazel/Core.h"

namespace Hazel {

    Shader::Shader(const std::string& filePath)
    {
        ShaderProgramSource src = ParseShader(filePath);
        m_Id = CreateShader(src.VertexSource, src.FragmentSource);
        HZ_CORE_INFO("SHADER ID: {0}", m_Id);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_Id);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_Id);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    ShaderProgramSource Shader::ParseShader(const std::string& filePath)
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
        HZ_CORE_INFO("Vertex: {}", sourceCode.VertexSource);
        HZ_CORE_INFO("Fragment: {}", sourceCode.FragmentSource);

        return sourceCode;
    }

    unsigned int Shader::CompileShader(unsigned int type, const char* source)
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

    unsigned int Shader::CreateShader(const std::string& VertexSource, const std::string& FragmentSource)
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