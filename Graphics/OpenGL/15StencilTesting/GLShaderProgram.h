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
	GLShaderProgram(GLWindow *cWindow, std::string strVertexShaderPath, std::string strFragmentShaderPath);
	virtual ~GLShaderProgram();

	bool Init();

	GLenum GetProgram() const;
	void UseProgram();
	
	void AppendObject(GLObject cObject);
	void SetGlobalUniform(std::string name, GLUniform sUniform);
	void RenderObjects();

private:
	GLWindow *m_cWindow;
	std::string m_strVertexShaderPath;
	std::string m_strFramgmentShaderPath;

	GLenum m_uiProgram;

	GLModel *m_cModel;
	GLShader *m_cVertexShader;
	GLShader *m_cFragmentShader;

	std::vector<GLObject> m_vecObjects;
	std::map<std::string, GLUniform> m_mapGlobalUniform;

	void SetUniform(const char *name, GLUniform sUniform);
	void SetUniform(const GLchar *name, GLint v0);
	void SetUniform(const GLchar *name, GLuint v0);
	void SetUniform(const GLchar *name, GLfloat v0);
	void SetUniform(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2);
};