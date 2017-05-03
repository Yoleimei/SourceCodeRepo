#pragma once

#include <cstdio>
#include <cstdarg>

#include <iostream>
#include <sstream>
#include <fstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

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
