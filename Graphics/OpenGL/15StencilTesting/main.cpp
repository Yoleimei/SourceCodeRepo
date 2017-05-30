// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLFramework.h"
#include "windows.h"

int main()
{
	GLFramework *cFramework = new GLFramework();
	if (nullptr != cFramework) {
		bool bRes = cFramework->Init();
		if (bRes) {
			cFramework->Run();
		}
		else {
			LOG_ERR("[%s:%d] Init GLFramework failed\n", __FUNCTION__, __LINE__);
		}

		cFramework->Terminate();
		delete cFramework;
	}
	else {
		LOG_ERR("[%s:%d] cFramework is nullptr\n", __FUNCTION__, __LINE__);
	}

	Sleep(1000);
	getchar();
}
