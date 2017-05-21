#pragma once

#include "GL.h"

class GLMesh;
class GLTexture;
class GLShaderProgram;

class GLModel
{
public:
	GLModel(GLShaderProgram *cShaderProgram,std::string path);
	virtual ~GLModel();

	bool Init();
	std::vector<GLMesh> GetMeshes();

private:
	GLShaderProgram *m_cShaderProgram;

	std::string m_strPath;
	std::string m_strPathPrefix;

	std::vector<GLMesh> m_vecMesh;
	std::vector<GLTexture> m_vecTexture;
	
	void ProcessNode(aiNode *node, const aiScene *scene);
	GLMesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<GLTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
};