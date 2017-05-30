#include "GLModel.h"
#include "GLMesh.h"
#include "GLTexture.h"
#include "GLShaderProgram.h"

GLModel::GLModel(GLShaderProgram *cShaderProgram, std::string path)
{
	m_cShaderProgram = cShaderProgram;
	m_strPath = path;
}

GLModel::~GLModel()
{
	m_vecMesh.clear();
	m_vecTexture.clear();
}

bool GLModel::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(m_strPath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LOG_ERR("ERROR::ASSIMP:: %s\n", importer.GetErrorString());
		return false;
	}

	m_strPathPrefix = m_strPath.substr(0, m_strPath.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);

	return true;
}

std::vector<GLMesh> GLModel::GetMeshes()
{
	return m_vecMesh;
}

void GLModel::ProcessNode(aiNode *node, const aiScene *scene)
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	// search meshes in assimp tree
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		GLMesh cMesh = ProcessMesh(mesh, scene);
		m_vecMesh.push_back(cMesh);
	}

	// depth first traverse
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->ProcessNode(node->mChildren[i], scene);
	}
}

GLMesh GLModel::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	std::vector<GLVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<GLTexture> textures;

	// vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		GLVertex vertex;
		glm::vec3 vector;

		// postion
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// normal
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		// textureCoord, assimp support at most 8 textures in every mesh
		if (nullptr != mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.textureCoord = vec;
		}
		else {
			vertex.textureCoord = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	// indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		for (GLuint j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	// materials (textures)
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// diffuse textures
		std::vector<GLTexture> vecDiffuseTextures = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), vecDiffuseTextures.begin(), vecDiffuseTextures.end());

		// specular textures
		std::vector<GLTexture> vecSpecularTextures = this->LoadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), vecSpecularTextures.begin(), vecSpecularTextures.end());
	}

	GLMesh cMesh(m_cShaderProgram, vertices, indices, textures);
	cMesh.Init();
	return cMesh;
}

std::vector<GLTexture> GLModel::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	std::vector<GLTexture> vecTextures;

	GLuint uiTextureCount = mat->GetTextureCount(type);
	for (GLuint i = 0; i < uiTextureCount; i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		// get texture
		GLboolean bIsAlreadyContained = false;
		for (GLuint j = 0; j < m_vecTexture.size(); j++) {
			const char *pchExistedTexturePath = m_vecTexture[j].GetTexturePath().c_str();
			const char *pchMaterialTexturePath = str.C_Str();
			if (!strcmp(pchExistedTexturePath, pchMaterialTexturePath)) {
				vecTextures.push_back(m_vecTexture[j]);
				bIsAlreadyContained = true;
				break;
			}
		}
		if (!bIsAlreadyContained) {
			std::string strTexturePath(m_strPathPrefix + '/' + str.C_Str());
			GLTexture cTexture(strTexturePath, type);
			bool bRes = cTexture.Init();
			if (!bRes) {
				LOG_ERR("[%s:%d] Init GLTexture failed\n", __FUNCTION__, __LINE__);
				break;
			}
			vecTextures.push_back(cTexture);
			m_vecTexture.push_back(cTexture);
		}
	}

	return vecTextures;
}