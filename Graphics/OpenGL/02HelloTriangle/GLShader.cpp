// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLShader.h"

#include "GLLib.h"
#include "GLExtensionWrangler.h"

#include <iostream>

GLShader::GLShader(unsigned int type)
{
	m_uiShader = GLLib::CreateShader(type);
}

GLShader::~GLShader()
{
	GLLib::DeleteShader(m_uiShader);
}

unsigned int GLShader::GetShader() const
{
	return m_uiShader;
}

void GLShader::CompileShader(const char * const *pcShaderSource)
{
	GLLib::ShaderSource(m_uiShader, 1, pcShaderSource, NULL);
	GLLib::CompileShader(m_uiShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	GLLib::GetShaderiv(m_uiShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLLib::GetShaderInfoLog(m_uiShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
