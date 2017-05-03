#include "GLFragmentShader.h"

#include "GLLib.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

// Shaders
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLFragmentShader::GLFragmentShader()
{
	m_iFragmentShader = GLLib::CreateShader(GL_VERTEX_SHADER);
}

GLFragmentShader::~GLFragmentShader()
{
	GLLib::DeleteShader(m_iFragmentShader);
}

void GLFragmentShader::CompileShader()
{
	GLLib::ShaderSource(m_iFragmentShader, 1, &fragmentShaderSource, NULL);
	GLLib::CompileShader(m_iFragmentShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	GLLib::GetShaderiv(m_iFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLLib::GetShaderInfoLog(m_iFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
