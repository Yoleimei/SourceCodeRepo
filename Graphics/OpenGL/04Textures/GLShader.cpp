#include "GLShader.h"

GLShader::GLShader(unsigned int type)
{
	m_uiShader = glCreateShader(type);
}

GLShader::~GLShader()
{
	glDeleteShader(m_uiShader);
}

GLenum GLShader::GetShader() const
{
	return m_uiShader;
}

bool GLShader::CompileShader(const GLchar * pcFilePath)
{
	if (!ReadShaderCode(pcFilePath)) {
		LOG_ERR("Read ShaderCode failed.\n");
		return false;
	}

	const GLchar * pcShaderCode = m_strShaderCode.c_str();
	glShaderSource(m_uiShader, 1, &pcShaderCode, NULL);
	glCompileShader(m_uiShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_uiShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_uiShader, 512, NULL, infoLog);
		LOG_ERR("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
		return false;
	}

	return true;
}

bool GLShader::ReadShaderCode(const GLchar * pcFilePath)
{
	if (nullptr == pcFilePath) {
		LOG_ERR("ShaderCodeFile not exist.\n");
		return false;
	}

	std::ifstream shaderFileStream(pcFilePath, std::ifstream::in);
	std::stringstream shaderStringStream;
	shaderStringStream << shaderFileStream.rdbuf();
	m_strShaderCode = shaderStringStream.str();
	shaderFileStream.close();

}
