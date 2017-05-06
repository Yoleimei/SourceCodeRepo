#include "GLModel.h"

GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // normal out
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

GLModel::GLModel()
	: m_fVertices(nullptr)
	, m_iVertexSize(0)
	, m_fIndices(nullptr)
	, m_iIndexSize(0)
{
	m_fVertices = vertices;
	m_iVertexSize = sizeof(vertices);

	memset(&m_sVertexShaderInputSize, 0, sizeof(m_sVertexShaderInputSize));

	m_sVertexShaderInputSize.size[VERTEX_SHADER] = 0;

#ifdef GL_MODEL_USE_POSITION
	m_sVertexShaderInputSize.size[VERTEX_SHADER_POSITION] = GL_MODEL_POSITION_SIZE;
	m_sVertexShaderInputSize.size[VERTEX_SHADER] += GL_MODEL_POSITION_SIZE;
#endif

#ifdef GL_MODEL_USE_COLOR
	m_sVertexShaderInputSize.size[VERTEX_SHADER_COLOR] = GL_MODEL_COLOR_SIZE;
	m_sVertexShaderInputSize.size[VERTEX_SHADER] += GL_MODEL_COLOR_SIZE;
#endif

#ifdef GL_MODEL_USE_TEXTURE
	m_sVertexShaderInputSize.size[VERTEX_SHADER_TEXTURE] = GL_MODEL_TEXTURE_SIZE;
	m_sVertexShaderInputSize.size[VERTEX_SHADER] += GL_MODEL_TEXTURE_SIZE;
#endif

#ifdef GL_MODEL_USE_NORMAL
	m_sVertexShaderInputSize.size[VERTEX_SHADER_NORMAL] = GL_MODEL_NORMAL_SIZE;
	m_sVertexShaderInputSize.size[VERTEX_SHADER] += GL_MODEL_NORMAL_SIZE;
#endif
}

GLModel::~GLModel()
{
	m_fVertices = nullptr;
	m_iVertexSize = 0;
}

GLfloat* GLModel::GetVertices()
{
	return m_fVertices;
}

GLint GLModel::GetVertexSize()
{
	return m_iVertexSize;
}

GLfloat* GLModel::GetIndices()
{
	return m_fIndices;
}

GLint GLModel::GetIndexSize()
{
	return m_iIndexSize;
}

void GLModel::GetVertexShaderInputSize(GLVertexShaderInputSize *iVertexShaderInputSize)
{
	if (nullptr == iVertexShaderInputSize)
		return;

	memcpy(iVertexShaderInputSize, &m_sVertexShaderInputSize, sizeof(GLVertexShaderInputSize));
}
