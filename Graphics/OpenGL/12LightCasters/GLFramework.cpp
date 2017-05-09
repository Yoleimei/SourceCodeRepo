#include "GLFramework.h"

bool GLFramework::Init()
{
	LOG_DBG("Starting GLFW context, OpenGL 3.3\n");

	// Init GLFW
	if (GL_FALSE == glfwInit()) {
		LOG_ERR("glfwInit error.\n");
		return false;
	}

	m_cWindow = new GLWindow("LearnOpenGL", false);
	if ((nullptr == m_cWindow) || nullptr == m_cWindow->GetWindow()) {
		LOG_ERR("Failed to create GLFW window\n");
		return false;
	}

	glfwMakeContextCurrent(m_cWindow->GetWindow());

	glewExperimental = GL_TRUE;
	GLenum eRet = glewInit();
	if (GLEW_OK != eRet) {
		LOG_ERR("glewInit error: %s\n", glewGetErrorString(eRet));
		return false;
	}

	m_cWindow->Init();

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
