#pragma once

#include "GL.h"

#define GL_MODEL_USE_POSITION
//#define GL_MODEL_USE_COLOR
#define GL_MODEL_USE_TEXTURE

const int GL_MODEL_POSITION_SIZE = 3;
const int GL_MODEL_COLOR_SIZE = 3;
const int GL_MODEL_TEXTURE_SIZE = 2;

enum GLVertexShaderInputType
{
	VERTEX_SHADER_POSITION,
	VERTEX_SHADER_COLOR,
	VERTEX_SHADER_TEXTURE,

	VERTEX_SHADER,
	VERTEX_SHADER_MAX
};

#if 0
struct GLVertexShaderInputData
{
#ifdef GL_MODEL_USE_POSITION
	GLfloat position[GL_MODEL_POSITION_SIZE];
#endif
#ifdef GL_MODEL_USE_COLOR
	GLfloat color[GL_MODEL_COLOR_SIZE];
#endif
#ifdef GL_MODEL_USE_TEXTURE
	GLfloat texture[GL_MODEL_TEXTURE_SIZE];
#endif
};
#endif

struct GLVertexShaderInputSize
{
	GLint size[VERTEX_SHADER_MAX];
};

class GLModel
{
public:
	GLModel();
	virtual ~GLModel();

	GLfloat* GetVertices();
	GLint GetVertexSize();
	GLfloat* GetIndices();
	GLint GetIndexSize();

	void GetVertexShaderInputSize(GLVertexShaderInputSize *iVertexShaderInputSize);

public:
	GLfloat *m_fVertices;
	GLint m_iVertexSize;
	GLfloat *m_fIndices;
	GLint m_iIndexSize;
	
	GLVertexShaderInputSize m_sVertexShaderInputSize;
};