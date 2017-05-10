#pragma once

#include "GL.h"

class GLTexture
{
public:
	GLTexture(aiString strFilePath, aiTextureType type, GLint wrapSParam = GL_REPEAT, GLint wrapTParam = GL_REPEAT, GLint MinFilter = GL_LINEAR_MIPMAP_LINEAR, GLint MagFilter = GL_LINEAR);
	virtual ~GLTexture();

	GLuint GetTextureId();
	aiTextureType GetTextureType();
	aiString GetTexturePath();

	void ActiveTexture(GLenum texture);

	void BindTexture();
	void UnbindTexture();

private:
	GLuint m_uiTexture;
	aiTextureType m_eType;
	aiString m_strPath;
};
