#include "GLShader.h"

GLShader::GLShader(unsigned int type)
{
	m_uiShader = glCreateShader(type);
	LOG_INFO("[%s:%d] m_uiShader=%u\n", __FUNCTION__, __LINE__, m_uiShader);
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
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	if (!ReadShaderCode(pcFilePath)) {
		LOG_ERR("[%s:%d] Read ShaderCode failed.\n", __FUNCTION__, __LINE__);
		return false;
	}

	const GLchar *pchShaderCode = m_strShaderCode.c_str();
	glShaderSource(m_uiShader, 1, &pchShaderCode, NULL);
	glCompileShader(m_uiShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_uiShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(m_uiShader, 512, NULL, infoLog);
		LOG_ERR("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
		return false;
	}

	return true;
}

bool GLShader::ReadShaderCode(const GLchar * pcFilePath)
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	if (nullptr == pcFilePath) {
		LOG_ERR("[%s:%d] ShaderCodeFile not exist\n", __FUNCTION__, __LINE__);
		return false;
	}

	std::ifstream shaderFileStream(pcFilePath, std::ifstream::in);
	std::stringstream shaderStringStream;
	shaderStringStream << shaderFileStream.rdbuf();
	m_strShaderCode = shaderStringStream.str();
	shaderFileStream.close();

	return true;
}
