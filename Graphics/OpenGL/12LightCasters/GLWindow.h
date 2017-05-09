#pragma once

#include "GL.h"
#include "GLShaderProgram.h"

struct GLInputData
{
	bool bIsKeyPress[1024];
	bool bIsMouseButtonPress[16];
	double dMousePosX;
	double dMousePosY;
	int iScrollPlusCnt;
	int iScrollMinusCnt;
};

class GLWindow
{
public:
	GLWindow(const char* title, bool isFullScreen = true);
	virtual ~GLWindow();

	GLFWwindow* GetWindow();

	void Init();
	void Run();

	int GetWidth();
	int GetHeight();

	void DecreaseScrollPlusCnt();
	void DecreaseScrollMinusCnt();
	void GetInput(GLInputData *sInputData);

	GLCamera* GetCamera();

private:
	GLFWwindow *m_sWindow;
	int m_iWidth;
	int m_iHeight;

	GLShaderProgram *m_cLightingShaderProgram;

	GLCamera *m_cCamera;

	void Render();
};