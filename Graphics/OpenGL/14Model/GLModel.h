#pragma once

#include "GL.h"

class GLMesh;
class GLTexture;
class GLShaderProgram;

class GLModel
{
public:
	GLModel(GLShaderProgram *cShaderProgram,const GLchar *path);
	virtual ~GLModel();

	std::vector<GLMesh> GetMeshes();

private:
	GLShaderProgram *m_cShaderProgram;

	std::vector<GLMesh> m_vecMesh;
	std::vector<GLTexture> m_vecLoadedTexture;
	
	void ProcessNode(aiNode *node, const aiScene *scene);
	GLMesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<GLTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
};