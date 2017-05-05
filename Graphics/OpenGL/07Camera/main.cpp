// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLFramework.h"
#include "windows.h"

void glPrintfNull(const char* const, ...) { }

int main()
{
	GLFramework *cFramework = new GLFramework();
	if (cFramework->Init()) {
		cFramework->Run();
	}

	cFramework->Terminate();
	delete cFramework;

	Sleep(1000);
}
