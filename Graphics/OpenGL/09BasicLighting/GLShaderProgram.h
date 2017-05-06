#pragma once

#include "GL.h"
#include "GLModel.h"
#include "GLTexture.h"
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

	void LinkProgram();
	void UseProgram();
	
	void BindVertexArray();
	void UnbindVertexArray();

	void RegisterVertexArray();
	void UnregisterVertexArray();

	void AppendObject(GLObject cObject);
	void SetTexture(GLfloat uniMixValue);
	void SetUniform(const GLchar *name, GLfloat v0, GLfloat v1, GLfloat v2);
	void SetUniform(const GLchar *name, GLfloat v0);
	void RenderObjects();

private:
	GLWindow *m_cWindow;

	GLenum m_uiProgram;

	GLuint m_uiVAO; // Vertex Array Object
	GLuint m_uiVBO; // Vertex Buffer Object
	GLuint m_uiEBO; // Element Buffer Object

	GLModel *m_cModel;
	GLShader *cVertexShader;

	GLTexture *m_cTexture1;
	GLTexture *m_cTexture2;
	GLShader *cFragmentShader;

	std::list<GLObject> m_listObjects;
};