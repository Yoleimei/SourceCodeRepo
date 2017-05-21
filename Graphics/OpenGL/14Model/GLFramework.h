#pragma once

#include "GL.h"
#include "GLWindow.h"

class GLFramework
{
public:
	GLFramework() { }
	virtual ~GLFramework() { }

	bool Init();
	void Run();
	void Terminate();

private:
	GLFramework(const GLFramework &ref) { }
	GLFramework& operator=(const GLFramework &ref) { }

	GLWindow *m_cWindow;

	bool InitGlfw();
	bool InitGlew();
};
