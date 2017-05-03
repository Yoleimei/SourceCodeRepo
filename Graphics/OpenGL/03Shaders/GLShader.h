#pragma once

#include "GLExtensionWrangler.h"

class GLShader
{
public:
	GLShader(unsigned int type);
	virtual ~GLShader();

	GLenum GetShader() const;

	bool CompileShader(const GLchar * pcFilePath);

private:
	GLenum m_uiShader;
	std::string m_strShaderCode;

	bool ReadShaderCode(const GLchar * pcFilePath);
};