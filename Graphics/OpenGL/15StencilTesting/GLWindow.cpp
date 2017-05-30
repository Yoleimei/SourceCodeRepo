#include "GLWindow.h"

// Window dimensions
const GLuint WIDTH = 1920;
const GLuint HEIGHT = 1080;

GLfloat uniMixValue = 0.2f;
static bool isKeyPress[1024] = { false };
static bool isMouseButtonPress[16] = { false };
static double dMousePosX = 0.0;
static double dMousePosY = 0.0;
static int iScrollPlusCnt = 0;
static int iScrollMinusCnt = 0;
static std::mutex scrollCntMutex;

glm::vec3 objectPositions[] = {
	glm::vec3(-1.0f,  -2.0f,  -1.0f),
	glm::vec3(2.0f,  -2.0f,  0.0f)
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// LOG_DBG("key:%d\n", key);
	if (GLFW_KEY_ESCAPE == key && GLFW_RELEASE == action) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (GLFW_KEY_UP == key && GLFW_RELEASE == action) {
		uniMixValue = (uniMixValue + 0.1f > 1.0f) ? 1.0f : (uniMixValue + 0.1f);
		// LOG_DBG("uniMixValue:%f\n", uniMixValue);
	}
	else if (GLFW_KEY_DOWN == key && GLFW_RELEASE == action) {
		uniMixValue = (uniMixValue - 0.1f < 0.0f) ? 0.0f : (uniMixValue - 0.1f);
		// LOG_DBG("uniMixValue:%f\n", uniMixValue);
	}
	else {
		if ((GLFW_PRESS == action) || GLFW_REPEAT == action) {
			isKeyPress[key] = true;
		}
		else {
			isKeyPress[key] = false;
		}
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	dMousePosX = xpos;
	dMousePosY = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (GLFW_PRESS == action) {
		isMouseButtonPress[button] = true;
	}
	else {
		isMouseButtonPress[button] = false;
	}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollCntMutex.lock();
	if (yoffset > 0)
		iScrollPlusCnt++;
	else
		iScrollMinusCnt++;
	scrollCntMutex.unlock();
}

GLWindow::GLWindow(std::string title, bool isFullScreen)
	: m_sWindow(nullptr)
	, m_iWidth(WIDTH)
	, m_iHeight(HEIGHT)
{
	m_strTtile = title;
	m_bIsFullScreen = isFullScreen;
}

GLWindow::~GLWindow()
{
	if (m_cCamera)
		delete m_cCamera;
}

void GLWindow::CreateWindow()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glfwDefaultWindowHints();

	GLFWmonitor *pcMonitor = nullptr;
	if (m_bIsFullScreen)
		pcMonitor = glfwGetPrimaryMonitor();
	m_sWindow = glfwCreateWindow(WIDTH, HEIGHT, m_strTtile.c_str(), pcMonitor, nullptr);
}

bool GLWindow::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	// set callback
	glfwSetKeyCallback(m_sWindow, key_callback);
	glfwSetMouseButtonCallback(m_sWindow, mouse_button_callback);
	glfwSetCursorPosCallback(m_sWindow, cursor_pos_callback);
	glfwSetScrollCallback(m_sWindow, scroll_callback);

	// cursor options
	// glfwSetInputMode(m_sWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwGetFramebufferSize(m_sWindow, &m_iWidth, &m_iHeight);
	LOG_INFO("[%s:%d] Width=%d, Height=%d\n", __FUNCTION__, __LINE__, m_iWidth, m_iHeight);
	glViewport(0, 0, m_iWidth, m_iHeight);

	// setup OpenGL options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// init GLCamera
	m_cCamera = new GLCamera(this);
	if (nullptr == m_cCamera) {
		LOG_ERR("[%s:%d] m_cCamera is nullptr\n", __FUNCTION__, __LINE__);
		return false;
	}
	m_cCamera->Init();

	// init GLShaderProgram
	std::string strVertexShaderPath = "vertex_lighting.shader";
	std::string strFragmentShaderPath = "fragment_lighting.shader";
	m_cLightingShaderProgram = new GLShaderProgram(this, strVertexShaderPath, strFragmentShaderPath);
	if ((nullptr == m_cLightingShaderProgram) || !m_cLightingShaderProgram->Init()) {
		LOG_ERR("[%s:%d] Init GLShaderProgram failed, pointer address:0x%p, vertex shader path:%s, fragment shader path:%s\n",
			__FUNCTION__, __LINE__, m_cLightingShaderProgram, strVertexShaderPath.c_str(), strFragmentShaderPath.c_str());
		return false;
	}
	strVertexShaderPath = "vertex_lighting.shader";
	strFragmentShaderPath = "fragment_single_color.shader";
	m_cSingleColorShaderProgram = new GLShaderProgram(this, strVertexShaderPath, strFragmentShaderPath);
	if ((nullptr == m_cSingleColorShaderProgram) || !m_cSingleColorShaderProgram->Init()) {
		LOG_ERR("[%s:%d] Init GLShaderProgram failed, pointer address:0x%p, vertex shader path:%s, fragment shader path:%s\n",
			__FUNCTION__, __LINE__, m_cSingleColorShaderProgram, strVertexShaderPath.c_str(), strFragmentShaderPath.c_str());
		return false;
	}

	// append objects
	for (int i = 0; i < sizeof(objectPositions) / sizeof(objectPositions[0]); i++) {
		std::list<GLTransform> listModelTransforms;
		listModelTransforms.push_back(GLTransform(TRANSFORM_TRANSLATE, objectPositions[i]));
		listModelTransforms.push_back(GLTransform(TRANSFORM_ROTATE, glm::vec3(1.0f, 0.3f, 0.5f), glm::radians(20.0f * i)));
		m_cLightingShaderProgram->AppendObject(GLObject(listModelTransforms));
		listModelTransforms.push_back(GLTransform(TRANSFORM_SCALE, glm::vec3(1.1f, 1.1f, 1.1f)));
		m_cSingleColorShaderProgram->AppendObject(GLObject(listModelTransforms));
	}

	return true;
}

void GLWindow::Run()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	// Game loop
	while (!glfwWindowShouldClose(m_sWindow))
	{
		m_cCamera->SetDeltaTime();

		glfwPollEvents();
		m_cCamera->ProcessEvents();

		// Render
		Render();

		glfwSwapBuffers(m_sWindow);
	}
}

GLFWwindow* GLWindow::GetWindow()
{
	return m_sWindow;
}

int GLWindow::GetWidth()
{
	return m_iWidth;
}

int GLWindow::GetHeight()
{
	return m_iHeight;
}

void GLWindow::DecreaseScrollPlusCnt()
{
	scrollCntMutex.lock();

	if (iScrollPlusCnt > 0)
		iScrollPlusCnt--;

	scrollCntMutex.unlock();
}

void GLWindow::DecreaseScrollMinusCnt()
{
	scrollCntMutex.lock();

	if (iScrollMinusCnt > 0)
		iScrollMinusCnt--;

	scrollCntMutex.unlock();
}

GLInputData GLWindow::GetInput()
{
	scrollCntMutex.lock();

	GLInputData sInputData;
	memset(&sInputData, 0, sizeof(sInputData));
	memcpy(sInputData.bIsKeyPress, isKeyPress, sizeof(sInputData.bIsKeyPress));
	memcpy(sInputData.bIsMouseButtonPress, isMouseButtonPress, sizeof(sInputData.bIsMouseButtonPress));
	sInputData.dMousePosX = dMousePosX;
	sInputData.dMousePosY = dMousePosY;
	sInputData.iScrollPlusCnt = iScrollPlusCnt;
	sInputData.iScrollMinusCnt = iScrollMinusCnt;

	scrollCntMutex.unlock();

	return sInputData;
}

GLCamera* GLWindow::GetCamera()
{
	return m_cCamera;
}

void GLWindow::Render()
{
	// Clear the colorbuffer
	// glClearColor(0.78f, 0.93f, 0.8f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Draw
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	m_cLightingShaderProgram->UseProgram();
	m_cLightingShaderProgram->RenderObjects();

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	m_cSingleColorShaderProgram->UseProgram();
	m_cSingleColorShaderProgram->RenderObjects();

	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
}
