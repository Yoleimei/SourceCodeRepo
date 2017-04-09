#pragma once

// GLFW
#include <GLFW/glfw3.h>

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
	int m_iWidth;
	int m_iHeight;

	bool CreateWindow(const char* title);
	void SetWindowShouldClose(int value);
	bool WindowShouldClose();
	void MakeContextCurrent();
	void SetKeyCallback();
	void PollEvents();

	void GetFramebufferSize();
	void SwapBuffers();

	void Render();
};
