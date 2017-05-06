#include "GLShaderProgram.h"
#include "GLWindow.h"


GLShaderProgram::GLShaderProgram(GLWindow *cWindow, const char *cVertexShaderPath, const char *cFragmentShaderPath)
{
	m_cWindow = cWindow;

	m_uiProgram = glCreateProgram();
	m_cModel = new GLModel();

	m_cTexture1 = new GLTexture();
	m_cTexture1->GenerateMipMap("container.jpg", GL_REPEAT);
	m_cTexture2 = new GLTexture();
	m_cTexture2->GenerateMipMap("awesomeface.png", GL_MIRRORED_REPEAT);

	cVertexShader = new GLShader(GL_VERTEX_SHADER);
	LOG_DBG("VertexShader=%d\n", cVertexShader->GetShader());
	cVertexShader->CompileShader(cVertexShaderPath);
	LOG_DBG("Compile Vertex Shader success.\n");

	cFragmentShader = new GLShader(GL_FRAGMENT_SHADER);
	LOG_DBG("FragmentShader=%d\n", cFragmentShader->GetShader());
	cFragmentShader->CompileShader(cFragmentShaderPath);
	LOG_DBG("Compile Fragment Shader success.\n");

}

GLShaderProgram::~GLShaderProgram()
{
	m_listObjects.clear();

	if (m_cTexture1)
		delete m_cTexture1;

	if (m_cTexture2)
		delete m_cTexture2;
	
	if (m_cModel)
		delete m_cModel;
}

GLenum GLShaderProgram::GetProgram() const
{
	return m_uiProgram;
}

void GLShaderProgram::LinkProgram()
{
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

void GLShaderProgram::RegisterVertexArray()
{
	glGenVertexArrays(1, &m_uiVAO);
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiEBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	BindVertexArray();

	if (NULL != m_cModel->GetVertices()) {
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
		glBufferData(GL_ARRAY_BUFFER, m_cModel->GetVertexSize(), m_cModel->GetVertices(), GL_STATIC_DRAW);
	}

	if (NULL != m_cModel->GetIndices()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cModel->GetIndexSize(), m_cModel->GetIndices(), GL_STATIC_DRAW);
	}

	GLVertexShaderInputSize sSize;
	m_cModel->GetVertexShaderInputSize(&sSize);
	int sizeOffset = 0;

	if (sSize.size[VERTEX_SHADER_POSITION] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_POSITION), sSize.size[VERTEX_SHADER_POSITION], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_POSITION));
		sizeOffset += sSize.size[VERTEX_SHADER_POSITION];
	}

	if (sSize.size[VERTEX_SHADER_COLOR] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_COLOR), sSize.size[VERTEX_SHADER_COLOR], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_COLOR));
		sizeOffset += sSize.size[VERTEX_SHADER_COLOR];
	}

	if (sSize.size[VERTEX_SHADER_TEXTURE] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_TEXTURE), sSize.size[VERTEX_SHADER_TEXTURE], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_TEXTURE));
		sizeOffset += sSize.size[VERTEX_SHADER_TEXTURE];
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	UnbindVertexArray(); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void GLShaderProgram::UnregisterVertexArray()
{
	glDeleteVertexArrays(1, &m_uiVAO);
	glDeleteBuffers(1, &m_uiVBO);
	glDeleteBuffers(1, &m_uiEBO);
}

void GLShaderProgram::AppendObject(GLObject cObject)
{
	m_listObjects.push_back(cObject);
}

void GLShaderProgram::SetTexture(GLfloat uniMixValue)
{
	m_cTexture1->ActiveTexture(GL_TEXTURE0);
	m_cTexture1->BindTexture();
	GLint uniformLocation1 = glGetUniformLocation(m_uiProgram, "uniTexture1");
	glUniform1i(uniformLocation1, 0);

	m_cTexture2->ActiveTexture(GL_TEXTURE1);
	m_cTexture2->BindTexture();
	GLint uniformLocation2 = glGetUniformLocation(m_uiProgram, "uniTexture2");
	glUniform1i(uniformLocation2, 1);

	GLint myUniformLocation = glGetUniformLocation(m_uiProgram, "uniMixValue");
	glUniform1f(myUniformLocation, uniMixValue);
}

void GLShaderProgram::RenderObjects()
{
	int i = 1;
	for (auto it = m_listObjects.begin(); it != m_listObjects.end(); it++) {
		glm::mat4 model = glm::translate(glm::mat4(), it->GetPosition());
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 0.2f  * (i++) * 90.0f), glm::vec3(1.0f, 0.7f, 0.3f));
		GLuint uniModelLocation = glGetUniformLocation(m_uiProgram, "uniModel");
		glUniformMatrix4fv(uniModelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view = glm::lookAt(m_cWindow->GetCamera()->GetPosition(), m_cWindow->GetCamera()->GetTarget(), m_cWindow->GetCamera()->GetUp());
		GLuint uniViewLocation = glGetUniformLocation(m_uiProgram, "uniView");
		glUniformMatrix4fv(uniViewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::perspective(glm::radians(m_cWindow->GetCamera()->GetAspect()), (float)m_cWindow->GetWidth() / m_cWindow->GetHeight(), 0.1f, 100.0f);
		GLuint uniProjectionLocation = glGetUniformLocation(m_uiProgram, "uniProjection");
		glUniformMatrix4fv(uniProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

