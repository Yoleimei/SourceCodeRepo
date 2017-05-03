#pragma once

#include "GL.h"
#include "GLShaderProgram.h"
#include "GLTexture.h"

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

	GLFWwindow *m_sWindow;
	GLShaderProgram *m_cShaderProgram;
	GLTexture *m_cTexture1;
	GLTexture *m_cTexture2;

	int m_iWidth;
	int m_iHeight;

	bool CreateWindow(const char* title);
	void SetWindowShouldClose(int value);
	int WindowShouldClose();
	void MakeContextCurrent();
	void SetKeyCallback();
	void PollEvents();

	void GetFramebufferSize();
	void SwapBuffers();

	void Render();
};
