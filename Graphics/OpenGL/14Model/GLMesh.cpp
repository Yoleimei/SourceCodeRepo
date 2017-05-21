#include "GLMesh.h"
#include "GLTexture.h"
#include "GLShaderProgram.h"

GLMesh::GLMesh(GLShaderProgram *cShaderProgram, std::vector<GLVertex> vec, std::vector<GLuint> idx, std::vector<GLTexture> tex)
{
	m_cShaderProgram = cShaderProgram;
	m_vecVertices = vec;
	m_vecIndices = idx;
	m_vecTextures = tex;
}

GLMesh::~GLMesh()
{
	m_vecVertices.clear();
	m_vecIndices.clear();
	m_vecTextures.clear();
	m_mapMaterialUniform.clear();

	// glDeleteVertexArrays(1, &m_uiVAO);
	// glDeleteBuffers(1, &m_uiVBO);
	// glDeleteBuffers(1, &m_uiEBO);
}

bool GLMesh::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	glGenVertexArrays(1, &m_uiVAO);
	glGenBuffers(1, &m_uiVBO);
	glGenBuffers(1, &m_uiEBO);
	LOG_INFO("[%s:%d] m_uiVAO=%u, m_uiVBO=%u, m_uiEBO=%u\n", __FUNCTION__, __LINE__, m_uiVAO, m_uiVBO, m_uiEBO);

	// bind Vertex Array Object 
	glBindVertexArray(this->m_uiVAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, m_vecVertices.size() * sizeof(GLVertex), &m_vecVertices[0], GL_STATIC_DRAW);
	// bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(GLuint), &m_vecIndices[0], GL_STATIC_DRAW);

	// set vertex attribution pointer
	int sizeOffset = 0;
	GLint sizeVertex = sizeof(GLVertex) / sizeof(GLfloat);
#ifdef GL_MODEL_USE_POSITION
	GLint sizePosition = sizeof(GLVertex::position) / sizeof(GLfloat);
	glVertexAttribPointer(GLuint(VERTEX_SHADER_POSITION), sizePosition, GL_FLOAT, GL_FALSE, sizeVertex * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
	glEnableVertexAttribArray(GLuint(VERTEX_SHADER_POSITION));
	sizeOffset += sizePosition;
#endif

#ifdef GL_MODEL_USE_NORMAL
	GLint sizeNormal = sizeof(GLVertex::normal) / sizeof(GLfloat);
	glVertexAttribPointer(GLuint(VERTEX_SHADER_NORMAL), sizeNormal, GL_FLOAT, GL_FALSE, sizeVertex * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
	glEnableVertexAttribArray(GLuint(VERTEX_SHADER_NORMAL));
	sizeOffset += sizeNormal;
#endif

#ifdef GL_MODEL_USE_TEXTURE
	GLint sizeTexture = sizeof(GLVertex::textureCoord) / sizeof(GLfloat);
	glVertexAttribPointer(GLuint(VERTEX_SHADER_TEXTURE), sizeTexture, GL_FLOAT, GL_FALSE, sizeVertex * sizeof(GLfloat), (GLvoid*)(sizeOffset * sizeof(GLfloat)));
	glEnableVertexAttribArray(GLuint(VERTEX_SHADER_TEXTURE));
	sizeOffset += sizeTexture;
#endif

#ifdef GL_MODEL_USE_NORMAL
	// TODO
#endif

	// unbind VBO
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// EBO should not be unbinded

	// unbind Vertex Array Object 
	glBindVertexArray(0);

	return true;
}

void GLMesh::SetMaterial()
{
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->m_vecTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		aiTextureType type = this->m_vecTextures[i].GetTextureType();
		std::string name;
		if (aiTextureType_DIFFUSE == type) {
			ss << diffuseNr++; // Transfer GLuint to stream
			name = "material_diffuse";
		}
		else if (aiTextureType_SPECULAR == type) {
			ss << specularNr++; // Transfer GLuint to stream
			name = "material_specular";
		}
		number = ss.str();
		// Now set the sampler to the correct texture unit
		m_mapMaterialUniform[(name + number).c_str()] = GLUniform(UNIFORM_1UI, i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, this->m_vecTextures[i].GetTextureId());
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	// m_mapMaterialUniform["material_shininess"] = GLUniform(UNIFORM_1F, 16.0f);
}

std::map<std::string, GLUniform> GLMesh::GetMaterialUniform()
{
	return m_mapMaterialUniform;
}

void GLMesh::Draw()
{
	// Draw mesh
	glBindVertexArray(this->m_uiVAO);
	glDrawElements(GL_TRIANGLES, this->m_vecIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < this->m_vecTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
