#include "GLShaderProgram.h"
#include "GLWindow.h"


GLShaderProgram::GLShaderProgram(GLWindow *cWindow, const char *cVertexShaderPath, const char *cFragmentShaderPath)
{
	m_cWindow = cWindow;

	m_uiProgram = glCreateProgram();
	m_cModel = new GLModel();

	AppendTexture(GLTexture("container2.png", GL_REPEAT));
	AppendTexture(GLTexture("container2_specular.png", GL_REPEAT));
	// AppendTexture(GLTexture("matrix.jpg", GL_REPEAT));

	cVertexShader = new GLShader(GL_VERTEX_SHADER);
	LOG_DBG("VertexShader=%d\n", cVertexShader->GetShader());
	cVertexShader->CompileShader(cVertexShaderPath);
	LOG_DBG("Compile Vertex Shader success.\n");

	cFragmentShader = new GLShader(GL_FRAGMENT_SHADER);
	LOG_DBG("FragmentShader=%d\n", cFragmentShader->GetShader());
	cFragmentShader->CompileShader(cFragmentShaderPath);
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

GLShaderProgram::~GLShaderProgram()
{
	m_listTexture.clear();
	m_listObjects.clear();
	m_mapGlobalUniform.clear();

	if (m_cModel)
		delete m_cModel;
}

GLenum GLShaderProgram::GetProgram() const
{
	return m_uiProgram;
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

	if (sSize.size[VERTEX_SHADER_NORMAL] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_NORMAL), sSize.size[VERTEX_SHADER_NORMAL], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_NORMAL));
		sizeOffset += sSize.size[VERTEX_SHADER_NORMAL];
	}

	if (sSize.size[VERTEX_SHADER_TEXTURE] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_TEXTURE), sSize.size[VERTEX_SHADER_TEXTURE], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_TEXTURE));
		sizeOffset += sSize.size[VERTEX_SHADER_TEXTURE];
	}

	if (sSize.size[VERTEX_SHADER_COLOR] > 0) {
		glVertexAttribPointer(GLuint(VERTEX_SHADER_COLOR), sSize.size[VERTEX_SHADER_COLOR], GL_FLOAT, GL_FALSE, sSize.size[VERTEX_SHADER] * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
		glEnableVertexAttribArray(GLuint(VERTEX_SHADER_COLOR));
		sizeOffset += sSize.size[VERTEX_SHADER_COLOR];
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

void GLShaderProgram::AppendTexture(GLTexture cTexture)
{
	m_listTexture.push_back(cTexture);
}

void GLShaderProgram::AppendObject(GLObject cObject)
{
	m_listObjects.push_back(cObject);
}

void GLShaderProgram::SetTexture()
{
	int i = 0;
	for (auto it = m_listTexture.begin(); it != m_listTexture.end(); it++) {
		it->ActiveTexture(GL_TEXTURE0 + i++);
		it->BindTexture();
	}
}

void GLShaderProgram::SetGlobalUniform(const char *name, GLUniform sUniform)
{
	// m_mapGlobalUniform.insert(std::pair<std::string, GLUniform>(std::string(name), sUniform));
	m_mapGlobalUniform[std::string(name)] = sUniform;
}

void GLShaderProgram::RenderObjects()
{
	if (m_mapGlobalUniform.size() > 0) {
		for (auto it = m_mapGlobalUniform.begin(); it != m_mapGlobalUniform.end(); it++) {
			SetUniform(it->first.c_str(), it->second);
		}
	}
	if (m_listObjects.size() > 0) {
		for (auto it = m_listObjects.begin(); it != m_listObjects.end(); it++) {
			std::map<std::string, GLUniform> listSingleUniform = it->GetSingleUniform();
			if (listSingleUniform.size() > 0) {
				for (auto it_uniform = listSingleUniform.begin(); it_uniform != listSingleUniform.end(); it_uniform++) {
					SetUniform(it_uniform->first.c_str(), it_uniform->second);
				}
			}

			// translate: need vector
			// rotate:    need angle and vector
			// scale:     need vector
			std::list<GLTransform> listModelTransforms = it->GetModelTransforms();
			glm::mat4 model = glm::mat4();
			for (auto it_trans = listModelTransforms.begin(); it_trans != listModelTransforms.end(); it_trans++) {
				if (TRANSFORM_TRANSLATE == it_trans->eTransformType) {
					model = glm::translate(model, it_trans->vector);
				}
				else if (TRANSFORM_ROTATE == it_trans->eTransformType) {
					model = glm::rotate(model, it_trans->angle, it_trans->vector);
				}
				else if (TRANSFORM_SCALE == it_trans->eTransformType) {
					model = glm::scale(model, it_trans->vector);
				}
				else {
					// do nothing
				}
			}
			GLuint uniModelLocation = glGetUniformLocation(m_uiProgram, "uniModel");
			glUniformMatrix4fv(uniModelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glm::mat4 view = glm::lookAt(m_cWindow->GetCamera()->GetPosition(), m_cWindow->GetCamera()->GetTarget(), m_cWindow->GetCamera()->GetUp());
			GLuint uniViewLocation = glGetUniformLocation(m_uiProgram, "uniView");
			glUniformMatrix4fv(uniViewLocation, 1, GL_FALSE, glm::value_ptr(view));

			glm::mat4 projection = glm::perspective(glm::radians(m_cWindow->GetCamera()->GetAspect()), (float)m_cWindow->GetWidth() / m_cWindow->GetHeight(), 0.1f, 1000.0f);
			GLuint uniProjectionLocation = glGetUniformLocation(m_uiProgram, "uniProjection");
			glUniformMatrix4fv(uniProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}

void GLShaderProgram::SetUniform(const char *name, GLUniform sUniform)
{
	if (UNIFORM_1I == sUniform.eUniformType) {
		SetUniform(name, sUniform.x.vali);
	}
	else if (UNIFORM_1F == sUniform.eUniformType) {
		SetUniform(name, sUniform.x.valf);
	}
	else if(UNIFORM_3F == sUniform.eUniformType) {
		SetUniform(name, sUniform.x.valf, sUniform.y.valf, sUniform.z.valf);
	}
	else {
		// do nothing
	}
}

void GLShaderProgram::SetUniform(const GLchar *name, GLint v0)
{
	glUniform1i(glGetUniformLocation(m_uiProgram, name), v0);
}

void GLShaderProgram::SetUniform(const GLchar *name, GLfloat v0)
{
	glUniform1f(glGetUniformLocation(m_uiProgram, name), v0);
}

void GLShaderProgram::SetUniform(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(glGetUniformLocation(m_uiProgram, name), v0, v1, v2);
}
