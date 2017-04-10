#include "GLShaderProgram.h"
#include "GLShader.h"

#include <iostream>

// Shaders
const GLchar* pcVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* pcFragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLShaderProgram::GLShaderProgram()
{
	m_uiProgram = GLLib::CreateProgram();
}

GLShaderProgram::~GLShaderProgram()
{

}

unsigned int GLShaderProgram::GetProgram() const
{
	return m_uiProgram;
}

void GLShaderProgram::LinkProgram()
{
	GLShader *cVertexShader = new GLShader(GL_VERTEX_SHADER);
	std::cout << "VertexShader=" << cVertexShader->GetShader() << std::endl;
	cVertexShader->CompileShader(&pcVertexShaderSource);
	std::cout << "Compile Vertex Shader success." << std::endl;

	GLShader *cFragmentShader = new GLShader(GL_FRAGMENT_SHADER);
	std::cout << "FragmentShader=" << cFragmentShader->GetShader() << std::endl;
	cFragmentShader->CompileShader(&pcFragmentShaderSource);
	std::cout << "Compile Fragment Shader success." << std::endl;

	GLLib::AttachShader(m_uiProgram, cVertexShader->GetShader());
	GLLib::AttachShader(m_uiProgram, cFragmentShader->GetShader());
	GLLib::LinkProgram(m_uiProgram);

	// Check for linking errors
	GLint success;
	GLchar infoLog[512];
	GLLib::GetProgramiv(m_uiProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLLib::GetProgramInfoLog(m_uiProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	delete cVertexShader;
	delete cFragmentShader;
}

void GLShaderProgram::UseProgram()
{
	GLLib::UseProgram(m_uiProgram);
}

void GLShaderProgram::BindVertexArray()
{
	GLLib::BindVertexArray(m_uiVAO);
}

void GLShaderProgram::UnbindVertexArray()
{
	GLLib::BindVertexArray(0);
}

void GLShaderProgram::RegisterVertexArray(float *vertices, int vertexSize, unsigned int *indices, int indexSize)
{
	GLLib::GenVertexArrays(1, &m_uiVAO);
	GLLib::GenBuffers(1, &m_uiVBO);
	GLLib::GenBuffers(1, &m_uiEBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	BindVertexArray();

	GLLib::BindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	GLLib::BufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

	GLLib::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	GLLib::BufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

	GLLib::VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	GLLib::EnableVertexAttribArray(0);

	GLLib::BindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	UnbindVertexArray(); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	// Uncommenting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLShaderProgram::UnregisterVertexArray()
{
	GLLib::DeleteVertexArrays(1, &m_uiVAO);
	GLLib::DeleteBuffers(1, &m_uiVBO);
	GLLib::DeleteBuffers(1, &m_uiEBO);
}
