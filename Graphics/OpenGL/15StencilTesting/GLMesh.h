#pragma once

#include "GL.h"

class GLTexture;
class GLShaderProgram;

class GLMesh
{
public:
	GLMesh(GLShaderProgram *cShaderProgram, std::vector<GLVertex> vec, std::vector<GLuint> idx, std::vector<GLTexture> tex);
	virtual ~GLMesh();

	bool Init();

	void SetMaterial();
	std::map<std::string, GLUniform> GetMaterialUniform();

	void Draw();

private:
	GLShaderProgram *m_cShaderProgram;

	GLuint m_uiVAO; // Vertex Array Object
	GLuint m_uiVBO; // Vertex Buffer Object
	GLuint m_uiEBO; // Element Buffer Object

	std::vector<GLVertex> m_vecVertices;
	std::vector<GLuint> m_vecIndices;
	std::vector<GLTexture> m_vecTextures;

	std::map<std::string, GLUniform> m_mapMaterialUniform;
};
