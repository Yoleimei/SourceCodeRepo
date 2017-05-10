#pragma once

#include <cstdio>
#include <cstdarg>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <list>

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
	TRANSFORM_COLOR,

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