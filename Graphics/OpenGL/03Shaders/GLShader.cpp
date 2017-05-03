#include "GLShader.h"

GLShader::GLShader(unsigned int type)
{
	m_uiShader = GLLib::CreateShader(type);
}

GLShader::~GLShader()
{
	GLLib::DeleteShader(m_uiShader);
}

GLenum GLShader::GetShader() const
{
	return m_uiShader;
}

bool GLShader::CompileShader(const GLchar * pcFilePath)
{
	if (!ReadShaderCode(pcFilePath)) {
		std::cout << "Read ShaderCode failed." << std::endl;
		return false;
	}

	const GLchar * pcShaderCode = m_strShaderCode.c_str();
	GLLib::ShaderSource(m_uiShader, 1, &pcShaderCode, NULL);
	GLLib::CompileShader(m_uiShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	GLLib::GetShaderiv(m_uiShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLLib::GetShaderInfoLog(m_uiShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool GLShader::ReadShaderCode(const GLchar * pcFilePath)
{
	if (nullptr == pcFilePath) {
		std::cout << "ShaderCodeFile not exist." << std::endl;
		return false;
	}

	std::ifstream shaderFileStream(pcFilePath, std::ifstream::in);
	std::stringstream shaderStringStream;
	shaderStringStream << shaderFileStream.rdbuf();
	m_strShaderCode = shaderStringStream.str();
	shaderFileStream.close();

}
