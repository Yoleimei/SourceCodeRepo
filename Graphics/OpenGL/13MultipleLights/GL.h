#pragma once

#include <cstdio>
#include <cstdarg>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <list>
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

// Other Libs
#include <SOIL.h>


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

// vertex shader
#define GL_MODEL_USE_POSITION
#define GL_MODEL_USE_NORMAL
#define GL_MODEL_USE_TEXTURE
//#define GL_MODEL_USE_COLOR

enum GLVertexShaderInputType
{
	VERTEX_SHADER_POSITION,
	VERTEX_SHADER_NORMAL,
	VERTEX_SHADER_TEXTURE,
	VERTEX_SHADER_COLOR,

	VERTEX_SHADER,
	VERTEX_SHADER_MAX
};

// model transform
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
	GLUniform(GLUniformType eType, float v0, float v1 = 0, float v2 = 0, float v3 = 0) {
		eUniformType = eType;
		x.valf = v0;
		y.valf = v1;
		z.valf = v2;
		w.valf = v3;
	}
};
