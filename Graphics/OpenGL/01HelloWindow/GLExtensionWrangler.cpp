#include "GLExtensionWrangler.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

bool GLExtensionWrangler::Init()
{
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	return true;
}
