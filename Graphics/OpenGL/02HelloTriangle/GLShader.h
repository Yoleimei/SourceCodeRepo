#pragma once

#include "GLExtensionWrangler.h"

class GLShader
{
public:
	GLShader(unsigned int type);
	virtual ~GLShader();

	unsigned int GetShader() const;

	void CompileShader(const char * const *pcShaderSource);

private:
	unsigned int m_uiShader;
};