#include "GLShaderProgram.h"
#include "GLWindow.h"
#include "GLMesh.h"

GLShaderProgram::GLShaderProgram(GLWindow *cWindow, const char *cVertexShaderPath, const char *cFragmentShaderPath)
{
	m_cWindow = cWindow;

	m_uiProgram = glCreateProgram();
	m_cModel = new GLModel(this, "nanosuit.obj");

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

void GLShaderProgram::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void GLShaderProgram::AppendObject(GLObject cObject)
{
	m_listObjects.push_back(cObject);
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

			std::vector<GLMesh> vecMeshes= m_cModel->GetMeshes();
			for (int i = 0; i < vecMeshes.size(); i++) {
				vecMeshes[i].Draw();
			}
		}
	}
}

void GLShaderProgram::SetUniform(const char *name, GLUniform sUniform)
{
	if (UNIFORM_1I == sUniform.eUniformType) {
		SetUniform(name, sUniform.x.vali);
	}
	else if (UNIFORM_1UI == sUniform.eUniformType) {
		SetUniform(name, sUniform.x.valui);
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

void GLShaderProgram::SetUniform(const GLchar *name, GLuint v0)
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
