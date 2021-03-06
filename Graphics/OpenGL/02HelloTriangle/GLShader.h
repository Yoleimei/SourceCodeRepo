#pragma once

#include "GLExtensionWrangler.h"

class GLShader
{
public:
	GLShader(unsigned int type);
	virtual ~GLShader();

	GLenum GetShader() const;

	void CompileShader(const char * const *pcShaderSource);

private:
	GLenum m_uiShader;
};