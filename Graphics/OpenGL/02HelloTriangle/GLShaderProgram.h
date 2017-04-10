#pragma once

#include "GLExtensionWrangler.h"

class GLShaderProgram
{
public:
	GLShaderProgram();
	virtual ~GLShaderProgram();

	unsigned int GetProgram() const;

	void LinkProgram();
	void UseProgram();
	
	void BindVertexArray();
	void UnbindVertexArray();

	void RegisterVertexArray(float *vertices, int vertexSize, unsigned int *indices, int indexSize);
	void UnregisterVertexArray();


private:
	unsigned int m_uiProgram;
	unsigned int m_uiVAO; // Vertex Array Object
	unsigned int m_uiVBO; // Vertex Buffer Object
	unsigned int m_uiEBO; // Element Buffer Object
};