#pragma once

#include "GL.h"

class GLTexture
{
public:
	GLTexture();
	virtual ~GLTexture();

	void GenerateMipMap(const GLchar * pcFilePath, GLint wrapParam);
	void ActiveTexture(GLenum texture);

	void BindTexture();
	void UnbindTexture();

private:
	GLuint m_uiTexture;
};
