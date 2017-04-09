#include "GLLib.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

void GLLib::Viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void GLLib::ClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLLib::Clear(unsigned int mask)
{
	glClear(mask);
}
