#include "GLFramework.h"

bool GLFramework::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);
	LOG_INFO("[%s:%d] Starting GLFW context, OpenGL 3.3\n", __FUNCTION__, __LINE__);

	// init glfw
	bool bRet = InitGlfw();
	if (!bRet) {
		return false;
	}

	// create window and make it current context
	m_cWindow = new GLWindow("LearnOpenGL", false);
	if (nullptr == m_cWindow) {
		LOG_ERR("[%s:%d] m_cWindow is nullptr\n", __FUNCTION__, __LINE__);
		return false;
	}
	m_cWindow->CreateWindow();
	if (nullptr == m_cWindow->GetWindow()) {
		LOG_ERR("[%s:%d] Create GLFW window failed\n", __FUNCTION__, __LINE__);
		return false;
	}
	glfwMakeContextCurrent(m_cWindow->GetWindow());

	// init glew
	bRet = InitGlew();
	if (!bRet) {
		return false;
	}

	// init GLWindow
	bRet = m_cWindow->Init();
	if (!bRet) {
		LOG_ERR("[%s:%d] Init GLWindow failed\n", __FUNCTION__, __LINE__);
		return false;
	}

	return true;
}

void GLFramework::Run()
{
	m_cWindow->Run();
}

void GLFramework::Terminate()
{
	glfwTerminate();
}

bool GLFramework::InitGlfw()
{
	int iRet = glfwInit();
	if (GLFW_TRUE != iRet) {
		LOG_ERR("[%s:%d] glfwInit() error.\n", __FUNCTION__, __LINE__);
		return false;
	}
	return true;
}

bool GLFramework::InitGlew()
{
	glewExperimental = GL_TRUE;
	GLenum eRet = glewInit();
	if (GLEW_OK != eRet) {
		LOG_ERR("[%s:%d] glewInit() error: %s\n", __FUNCTION__, __LINE__, glewGetErrorString(eRet));
		return false;
	}
	return true;
}


