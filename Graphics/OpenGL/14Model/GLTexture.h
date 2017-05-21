#pragma once

#include "GL.h"

class GLTexture
{
public:
	GLTexture(std::string strFilePath, aiTextureType type, GLint wrapSParam = GL_REPEAT, GLint wrapTParam = GL_REPEAT, GLint MinFilter = GL_LINEAR_MIPMAP_LINEAR, GLint MagFilter = GL_LINEAR);
	virtual ~GLTexture();

	bool Init();

	GLuint GetTextureId();
	aiTextureType GetTextureType();
	std::string GetTexturePath();

	void ActiveTexture(GLenum texture);

	void BindTexture();
	void UnbindTexture();

private:
	GLuint m_uiTexture;

	aiTextureType m_eType;
	std::string m_strPath;

	GLint m_iWrapSParam;
	GLint m_iWrapTParam;
	GLint m_iMinFilter;
	GLint m_iMagFilter;
};
