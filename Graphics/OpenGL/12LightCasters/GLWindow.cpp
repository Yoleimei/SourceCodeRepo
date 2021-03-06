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

GLWindow::GLWindow(const char* title, bool isFullScreen)
	: m_sWindow(nullptr)
	, m_iWidth(WIDTH)
	, m_iHeight(HEIGHT)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glfwDefaultWindowHints();

	GLFWmonitor *pcMonitor = nullptr;
	if (isFullScreen)
		pcMonitor = glfwGetPrimaryMonitor();
	m_sWindow = glfwCreateWindow(WIDTH, HEIGHT, title, pcMonitor, nullptr);

	m_cCamera = new GLCamera(this);
}

GLWindow::~GLWindow()
{
	if (m_cCamera)
		delete m_cCamera;
}

GLFWwindow* GLWindow::GetWindow()
{
	return m_sWindow;
}

void GLWindow::Init()
{
	glfwSetKeyCallback(m_sWindow, key_callback);
	glfwSetMouseButtonCallback(m_sWindow, mouse_button_callback);
	glfwSetCursorPosCallback(m_sWindow, cursor_pos_callback);
	glfwSetScrollCallback(m_sWindow, scroll_callback);

	// Cursor Options
	// glfwSetInputMode(m_sWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwGetFramebufferSize(m_sWindow, &m_iWidth, &m_iHeight);
	LOG_DBG("Width=%d, Height=%d\n", m_iWidth, m_iHeight);
	glViewport(0, 0, m_iWidth, m_iHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);
}

void GLWindow::Run()
{
	m_cLightingShaderProgram = new GLShaderProgram(this, "vertex_lighting.shader", "fragment_lighting.shader");
	LOG_DBG("m_cLightingShaderProgram=%d\n", m_cLightingShaderProgram->GetProgram());
	m_cLightingShaderProgram->RegisterVertexArray();

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -5.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -2.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
		m_cLightingShaderProgram->AppendObject(GLObject(cubePositions[i]));
	}

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

	m_cLightingShaderProgram->UnregisterVertexArray();
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

void GLWindow::GetInput(GLInputData * sInputData)
{
	scrollCntMutex.lock();

	memcpy(sInputData->bIsKeyPress, isKeyPress, sizeof(sInputData->bIsKeyPress));
	memcpy(sInputData->bIsMouseButtonPress, isMouseButtonPress, sizeof(sInputData->bIsMouseButtonPress));
	sInputData->dMousePosX = dMousePosX;
	sInputData->dMousePosY = dMousePosY;
	sInputData->iScrollPlusCnt = iScrollPlusCnt;
	sInputData->iScrollMinusCnt = iScrollMinusCnt;

	scrollCntMutex.unlock();
}

GLCamera* GLWindow::GetCamera()
{
	return m_cCamera;
}

void GLWindow::Render()
{
	// Clear the colorbuffer
	glClearColor(0.78f, 0.93f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw our first triangle
	m_cLightingShaderProgram->UseProgram();
	m_cLightingShaderProgram->BindVertexArray();
	m_cLightingShaderProgram->SetTexture();
	glm::vec3 vCameraPos = m_cCamera->GetPosition();
	glm::vec3 vCameraFront = m_cCamera->GetFront();
	m_cLightingShaderProgram->SetUniform("viewPosition", vCameraPos.x, vCameraPos.y, vCameraPos.z);
	m_cLightingShaderProgram->SetUniform("material.diffuse", 0);
	m_cLightingShaderProgram->SetUniform("material.specular", 1);
	m_cLightingShaderProgram->SetUniform("material.emission", 2);
	m_cLightingShaderProgram->SetUniform("material.shininess", 32.0f);
	m_cLightingShaderProgram->SetUniform("dirLight.direction", 0.0f, 0.0f, -1.0f);
	m_cLightingShaderProgram->SetUniform("dirLight.ambient", 0.3f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("dirLight.diffuse", 0.5f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("dirLight.specular", 1.0f, 0.0f, 0.0f);

	m_cLightingShaderProgram->SetUniform("ptrLight.position", 2.0f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("ptrLight.ambient", 0.0f, 0.3f, 0.0f);
	m_cLightingShaderProgram->SetUniform("ptrLight.diffuse", 0.0f, 0.5f, 0.0f);
	m_cLightingShaderProgram->SetUniform("ptrLight.specular", 0.0f, 1.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("ptrLight.constant", 1.0f);
	m_cLightingShaderProgram->SetUniform("ptrLight.linear", 0.09f);
	m_cLightingShaderProgram->SetUniform("ptrLight.quadratic", 0.032f);

	m_cLightingShaderProgram->SetUniform("sptLight.position", vCameraPos.x, vCameraPos.y, vCameraPos.z);
	m_cLightingShaderProgram->SetUniform("sptLight.direction", vCameraFront.x, vCameraFront.y, vCameraFront.z);
	m_cLightingShaderProgram->SetUniform("sptLight.color", 0.0f, 0.0f, 0.3f);
	m_cLightingShaderProgram->SetUniform("sptLight.cutoff", glm::cos(glm::radians(12.5f)));
	m_cLightingShaderProgram->SetUniform("sptLight.outerCutoff", glm::cos(glm::radians(25.0f)));

	m_cLightingShaderProgram->RenderObjects();
	m_cLightingShaderProgram->UnbindVertexArray();
	m_cLightingShaderProgram->RenderObjects();
	m_cLightingShaderProgram->UnbindVertexArray();
}
