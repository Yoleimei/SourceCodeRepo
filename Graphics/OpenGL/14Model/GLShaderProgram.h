#pragma once

#include "GL.h"
#include "GLModel.h"
#include "GLCamera.h"
#include "GLShader.h"
#include "GLObject.h"

class GLWindow;

class GLShaderProgram
{
public:
	GLShaderProgram(GLWindow *cWindow, const char *cVertexShaderPath, const char *cFragmentShaderPath);
	virtual ~GLShaderProgram();

	GLenum GetProgram() const;

	void UseProgram();
	
	void BindVertexArray();
	void UnbindVertexArray();

	void AppendObject(GLObject cObject);
	void SetTexture();
	void SetGlobalUniform(const char *name, GLUniform sUniform);
	void RenderObjects();

private:
	GLWindow *m_cWindow;

	GLenum m_uiProgram;

	GLModel *m_cModel;
	GLShader *cVertexShader;

	GLShader *cFragmentShader;

	std::list<GLObject> m_listObjects;
	std::map<std::string, GLUniform> m_mapGlobalUniform;

	void SetUniform(const char *name, GLUniform sUniform);
	void SetUniform(const GLchar *name, GLint v0);
	void SetUniform(const GLchar *name, GLuint v0);
	void SetUniform(const GLchar *name, GLfloat v0);
	void SetUniform(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2);
};