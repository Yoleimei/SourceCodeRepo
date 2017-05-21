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
	GLWindow(std::string title, bool isFullScreen = true);
	virtual ~GLWindow();

	void CreateWindow();

	bool Init();
	void Run();

	GLFWwindow* GetWindow();
	int GetWidth();
	int GetHeight();

	void DecreaseScrollPlusCnt();
	void DecreaseScrollMinusCnt();
	GLInputData GetInput();

	GLCamera* GetCamera();

private:
	GLFWwindow *m_sWindow;

	std::string m_strTtile;
	bool m_bIsFullScreen;
	int m_iWidth;
	int m_iHeight;

	GLShaderProgram *m_cLightingShaderProgram;

	GLCamera *m_cCamera;

	void Render();
};
