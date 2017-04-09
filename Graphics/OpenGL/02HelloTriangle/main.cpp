// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLFramework.h"
#include "windows.h"

int main()
{
	GLFramework *cFramework = new GLFramework();
	if (!cFramework->Init()) {
		cFramework->Terminate();
	}

	cFramework->Run();
	cFramework->Terminate();

	delete cFramework;

	Sleep(1000);
}
