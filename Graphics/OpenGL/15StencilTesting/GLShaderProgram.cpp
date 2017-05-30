#include "GLShaderProgram.h"
#include "GLWindow.h"
#include "GLMesh.h"

GLShaderProgram::GLShaderProgram(GLWindow *cWindow, std::string strVertexShaderPath, std::string strFragmentShaderPath)
{
	m_cWindow = cWindow;
	m_strVertexShaderPath = strVertexShaderPath;
	m_strFramgmentShaderPath = strFragmentShaderPath;

	m_uiProgram = glCreateProgram();
	LOG_INFO("[%s:%d] m_uiProgram=%u\n", __FUNCTION__, __LINE__, m_uiProgram);
}

GLShaderProgram::~GLShaderProgram()
{
	m_vecObjects.clear();
	m_mapGlobalUniform.clear();

	if (m_cModel)
		delete m_cModel;
}

bool GLShaderProgram::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	bool bRet = false;

	// init GLModel
	// m_cModel = new GLModel(this, "nanosuit/nanosuit.obj");
	m_cModel = new GLModel(this, "cube/cube.obj");
	if (nullptr == m_cModel) {
		LOG_ERR("[%s:%d] m_cModel is nullptr\n", __FUNCTION__, __LINE__);
		goto ModelError;
	}
	bool bRes = m_cModel->Init();
	if (!bRes) {
		LOG_ERR("[%s:%d] Init GLModel failed\n", __FUNCTION__, __LINE__);
		goto ModelError;
	}

	// compule vertex shader
	m_cVertexShader = new GLShader(GL_VERTEX_SHADER);
	if (nullptr == m_cVertexShader) {
		LOG_ERR("[%s:%d] m_cVertexShader is nullptr\n", __FUNCTION__, __LINE__);
		goto VertexShaderError;
	}
	bRes = m_cVertexShader->CompileShader(m_strVertexShaderPath.c_str());
	if (!bRes) {
		LOG_DBG("[%s:%d] Compile Vertex Shader success.\n", __FUNCTION__, __LINE__);
		goto VertexShaderError;
	}

	m_cFragmentShader = new GLShader(GL_FRAGMENT_SHADER);
	if (nullptr == m_cFragmentShader) {
		LOG_ERR("[%s:%d] m_cFragmentShader is nullptr\n", __FUNCTION__, __LINE__);
		goto FragmentShaderError;
	}
	m_cFragmentShader->CompileShader(m_strFramgmentShaderPath.c_str());
	if (!bRes) {
		LOG_DBG("[%s:%d] Compile Fragment Shader success.\n", __FUNCTION__, __LINE__);
		goto FragmentShaderError;
	}

	// attach shader and link program
	glAttachShader(m_uiProgram, m_cVertexShader->GetShader());
	glAttachShader(m_uiProgram, m_cFragmentShader->GetShader());
	glLinkProgram(m_uiProgram);

	// Check for linking errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_uiProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_uiProgram, 512, NULL, infoLog);
		LOG_ERR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
		goto LinkProgramError;
	}

	bRet = true;

LinkProgramError:
FragmentShaderError:
	if (m_cFragmentShader)
	delete m_cFragmentShader;

VertexShaderError:
	if (m_cVertexShader)
		delete m_cVertexShader;

ModelError:
	return bRet;
}

GLenum GLShaderProgram::GetProgram() const
{
	return m_uiProgram;
}

void GLShaderProgram::UseProgram()
{
	glUseProgram(m_uiProgram);
}

void GLShaderProgram::AppendObject(GLObject cObject)
{
	m_vecObjects.push_back(cObject);
}

void GLShaderProgram::SetGlobalUniform(std::string name, GLUniform sUniform)
{
	// m_mapGlobalUniform.insert(std::pair<std::string, GLUniform>(std::string(name), sUniform));
	m_mapGlobalUniform[name] = sUniform;
}

void GLShaderProgram::RenderObjects()
{
	if (m_mapGlobalUniform.size() > 0) {
		for (auto it = m_mapGlobalUniform.begin(); it != m_mapGlobalUniform.end(); it++) {
			SetUniform(it->first.c_str(), it->second);
		}
	}
	if (m_vecObjects.size() > 0) {
		for (auto it = m_vecObjects.begin(); it != m_vecObjects.end(); it++) {
			std::map<std::string, GLUniform> mapOwnUniform = it->GetOwnUniform();
			if (mapOwnUniform.size() > 0) {
				for (auto it_uniform = mapOwnUniform.begin(); it_uniform != mapOwnUniform.end(); it_uniform++) {
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

			GLfloat fNear = 0.1f;
			GLfloat fFar = 100.0;
			glm::mat4 projection = glm::perspective(glm::radians(m_cWindow->GetCamera()->GetAspect()), (GLfloat)m_cWindow->GetWidth() / m_cWindow->GetHeight(), fNear, fFar);
			GLuint uniProjectionLocation = glGetUniformLocation(m_uiProgram, "uniProjection");
			glUniformMatrix4fv(uniProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

			std::vector<GLMesh> vecMeshes= m_cModel->GetMeshes();
			for (size_t i = 0; i < vecMeshes.size(); i++) {
				vecMeshes[i].SetMaterial();
				std::map<std::string, GLUniform> mapMaterialUniform = vecMeshes[i].GetMaterialUniform();
				if (mapMaterialUniform.size() > 0) {
					for (auto it_uniform = mapMaterialUniform.begin(); it_uniform != mapMaterialUniform.end(); it_uniform++) {
						SetUniform(it_uniform->first.c_str(), it_uniform->second);
					}
				}

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
	LOG_DBG("Set Uniform: %s\n", name);
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
