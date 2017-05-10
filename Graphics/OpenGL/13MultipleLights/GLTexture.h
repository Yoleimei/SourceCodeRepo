#pragma once

#include "GL.h"

class GLTexture
{
public:
	GLTexture(const GLchar * pcFilePath, GLint wrapParam);
	virtual ~GLTexture();

	void ActiveTexture(GLenum texture);

	void BindTexture();
	void UnbindTexture();

private:
	GLuint m_uiTexture;
};
