#pragma once

#include <cstdio>
#include <cstdarg>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include <thread>
#include <mutex>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SOIL
#include <SOIL.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// LOG
#define ENABLE_ERROR
#define ENABLE_DEBUG

#ifdef ENABLE_ERROR
	#define LOG_ERR printf
#else
	#define LOG_ERR glPrintfNull
#endif

#ifdef ENABLE_DEBUG
#define LOG_DBG printf
#else
#define LOG_DBG glPrintfNull
#endif

extern void glPrintfNull(const char* const, ...);

// Vertex Shader / Model
#define GL_MODEL_USE_POSITION
#define GL_MODEL_USE_NORMAL
#define GL_MODEL_USE_TEXTURE
//#define GL_MODEL_USE_COLOR

struct GLVertex
{
#ifdef GL_MODEL_USE_POSITION
	glm::vec3 position;
#endif
#ifdef GL_MODEL_USE_NORMAL
	glm::vec3 normal;
#endif
#ifdef GL_MODEL_USE_TEXTURE
	glm::vec2 textureCoord;
#endif
#ifdef GL_MODEL_USE_COLOR
	glm::vec3 color;
#endif
};

const std::map<aiTextureType, std::string> mapTextureType {
	{ aiTextureType_DIFFUSE,  "texture_diffuse" },
	{ aiTextureType_SPECULAR, "texture_specular" }
};

enum GLVertexShaderInputType
{
	VERTEX_SHADER_POSITION,
	VERTEX_SHADER_NORMAL,
	VERTEX_SHADER_TEXTURE,
	VERTEX_SHADER_COLOR,

	VERTEX_SHADER,
	VERTEX_SHADER_MAX
};

// Model Transform
enum GLTransformType
{
	TRANSFORM_TRANSLATE,
	TRANSFORM_ROTATE,
	TRANSFORM_SCALE,

	TRANSFORM_MAX
};
struct GLTransform
{
	GLTransformType eTransformType;
	glm::vec3 vector;
	float angle;

	GLTransform(GLTransformType eType, glm::vec3 vec, float ang = 0.0f) {
		eTransformType = eType;
		vector = vec;
		angle = ang;
	}
};

// GLSL uniform
enum GLUniformType
{
	UNIFORM_1I,
	UNIFORM_2I,
	UNIFORM_3I,
	UNIFORM_4I,
	UNIFORM_1UI,
	UNIFORM_2UI,
	UNIFORM_3UI,
	UNIFORM_4UI,
	UNIFORM_1F,
	UNIFORM_2F,
	UNIFORM_3F,
	UNIFORM_4F,

	UNIFORM_MAX
};
struct GLUniform
{
	union GLUniformValue {
		int vali;
		unsigned int valui;
		float valf;
	};
	enum GLUniformType eUniformType;
	GLUniformValue x;
	GLUniformValue y;
	GLUniformValue z;
	GLUniformValue w;

	GLUniform() {
		eUniformType = UNIFORM_4I;
		x.vali = 0;
		y.vali = 0;
		z.vali = 0;
		w.vali = 0;
	}
	GLUniform(GLUniformType eType, int v0, int v1 = 0, int v2 = 0, int v3 = 0) {
		eUniformType = eType;
		x.vali = v0;
		y.vali = v1;
		z.vali = v2;
		w.vali = v3;
	}
	GLUniform(GLUniformType eType, unsigned int v0, unsigned int v1 = 0, unsigned int v2 = 0, unsigned int v3 = 0) {
		eUniformType = eType;
		x.valui = v0;
		y.valui = v1;
		z.valui = v2;
		w.valui = v3;
	}
	GLUniform(GLUniformType eType, float v0, float v1 = 0, float v2 = 0, float v3 = 0) {
		eUniformType = eType;
		x.valf = v0;
		y.valf = v1;
		z.valf = v2;
		w.valf = v3;
	}
};
