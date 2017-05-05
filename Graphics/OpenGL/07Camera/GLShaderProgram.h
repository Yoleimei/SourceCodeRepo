#pragma once

#include "GL.h"

class GLShaderProgram
{
public:
	GLShaderProgram();
	virtual ~GLShaderProgram();

	GLenum GetProgram() const;

	void LinkProgram();
	void UseProgram();
	
	void BindVertexArray();
	void UnbindVertexArray();

	void RegisterVertexArray(float *vertices, int vertexSize, unsigned int *indices, int indexSize);
	void UnregisterVertexArray();


private:
	GLenum m_uiProgram;
	GLuint m_uiVAO; // Vertex Array Object
	GLuint m_uiVBO; // Vertex Buffer Object
	GLuint m_uiEBO; // Element Buffer Object
};