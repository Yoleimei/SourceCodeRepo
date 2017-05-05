#pragma once

#include "GL.h"
#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLCamera.h"

class GLWindow
{
public:
	GLWindow(const char* title, bool isFullScreen = true);
	virtual ~GLWindow();

	GLFWwindow* GetWindow();

	void Init();
	void Run();

private:
	GLFWwindow *m_sWindow;
	int m_iWidth;
	int m_iHeight;

	GLShaderProgram *m_cShaderProgram;
	GLTexture *m_cTexture1;
	GLTexture *m_cTexture2;
	GLCamera *m_cCamera;

	void Render();
};