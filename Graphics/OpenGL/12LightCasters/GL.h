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
