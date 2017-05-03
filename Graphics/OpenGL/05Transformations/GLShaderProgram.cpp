#include "GLShaderProgram.h"
#include "GLShader.h"

GLShaderProgram::GLShaderProgram()
{
	m_uiProgram = glCreateProgram();
}

GLShaderProgram::~GLShaderProgram()
{

}

GLenum GLShaderProgram::GetProgram() const
{
	return m_uiProgram;
}

void GLShaderProgram::LinkProgram()
{
	GLShader *cVertexShader = new GLShader(GL_VERTEX_SHADER);
	LOG_DBG("VertexShader=%d\n", cVertexShader->GetShader());
	cVertexShader->CompileShader("vertex.shader");
	LOG_DBG("Compile Vertex Shader success.\n");

	GLShader *cFragmentShader = new GLShader(GL_FRAGMENT_SHADER);
	LOG_DBG("FragmentShader=%d\n", cFragmentShader->GetShader());
	cFragmentShader->CompileShader("fragment.shader");
	LOG_DBG("Compile Fragment Shader success.\n");

	glAttachShader(m_uiProgram, cVertexShader->GetShader());
	glAttachShader(m_uiProgram, cFragmentShader->GetShader());
	glLinkProgram(m_uiProgram);

	// Check for linking errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_uiProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_uiProgram, 512, NULL, infoLog);
		LOG_ERR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	delete cVertexShader;
	delete cFragmentShader;
}

void GLShaderProgram::UseProgram()
{
	glUseProgram(m_uiProgram);
}

void GLShaderProgram::BindVertexArray()
{
	glBindVertexArray(m_uiVAO);
}

void GLShaderProgram::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void GLShaderProgram::RegisterVertexArray(float *vertices, int vertexSize, unsigned int *indices, int indexSize)
{
	glGenVertexArrays(1, &m_uiVAO);
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiEBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	BindVertexArray();

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	UnbindVertexArray(); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void GLShaderProgram::UnregisterVertexArray()
{
	glDeleteVertexArrays(1, &m_uiVAO);
	glDeleteBuffers(1, &m_uiVBO);
	glDeleteBuffers(1, &m_uiEBO);
}
