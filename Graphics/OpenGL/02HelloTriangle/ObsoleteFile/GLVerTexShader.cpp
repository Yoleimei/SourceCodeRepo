#include "GLVertexShader.h"

#include "GLLib.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

GLVertexShader::GLVertexShader()
{
	m_iVertexShader = GLLib::CreateShader(GL_VERTEX_SHADER);
}

GLVertexShader::~GLVertexShader()
{
	GLLib::DeleteShader(m_iVertexShader);
}

void GLVertexShader::CompileShader()
{
	GLLib::ShaderSource(m_iVertexShader, 1, &vertexShaderSource, nullptr);
	GLLib::CompileShader(m_iVertexShader);

	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	GLLib::GetShaderiv(m_iVertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLLib::GetShaderInfoLog(m_iVertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
