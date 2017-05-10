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
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwDefaultWindowHints();

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
		std::list<GLTransform> listModelTransforms;
		listModelTransforms.push_back(GLTransform(TRANSFORM_TRANSLATE, cubePositions[i]));
		listModelTransforms.push_back(GLTransform(TRANSFORM_ROTATE, glm::vec3(1.0f, 0.3f, 0.5f), glm::radians(20.0f * i)));
		m_cLightingShaderProgram->AppendObject(listModelTransforms);
	}

	m_cLampShaderProgram = new GLShaderProgram(this, "vertex_lamp.shader", "fragment_lamp.shader");
	LOG_DBG("m_cLampShaderProgram=%d\n", m_cLampShaderProgram->GetProgram());
	m_cLampShaderProgram->RegisterVertexArray();

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {
		std::list<GLTransform> listModelTransforms;
		listModelTransforms.push_back(GLTransform(TRANSFORM_TRANSLATE, pointLightPositions[i]));
		listModelTransforms.push_back(GLTransform(TRANSFORM_SCALE, glm::vec3(0.2f, 0.2f, 0.2f)));
		m_cLampShaderProgram->AppendObject(listModelTransforms);
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
	m_cLampShaderProgram->UnregisterVertexArray();
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

	glm::vec3 pointLightColors[] = {
		glm::vec3(0.2f, 0.2f, 0.6f),
		glm::vec3(0.3f, 0.3f, 0.7f),
		glm::vec3(0.0f, 0.0f, 0.3f),
		glm::vec3(0.4f, 0.4f, 0.4f)
	};

	// Draw our first triangle
	m_cLightingShaderProgram->UseProgram();
	m_cLightingShaderProgram->BindVertexArray();
	m_cLightingShaderProgram->SetTexture();
	glm::vec3 vCameraPos = m_cCamera->GetPosition();
	glm::vec3 vCameraFront = m_cCamera->GetFront();
	m_cLightingShaderProgram->SetUniform("viewPosition", vCameraPos.x, vCameraPos.y, vCameraPos.z);
	m_cLightingShaderProgram->SetUniform("material_diffuse", 0);
	m_cLightingShaderProgram->SetUniform("material_specular", 1);
	m_cLightingShaderProgram->SetUniform("material_emission", 2);
	m_cLightingShaderProgram->SetUniform("material_shininess", 32.0f);
	m_cLightingShaderProgram->SetUniform("dir_light_direction", 0.0f, 0.0f, -1.0f);
	m_cLightingShaderProgram->SetUniform("dir_light_ambient", 0.3f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("dir_light_diffuse", 0.5f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("dir_light_specular", 1.0f, 0.0f, 0.0f);

	m_cLightingShaderProgram->SetUniform("ptr_light_position[0]", 0.7f, 0.2f, 2.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_ambient[0]", pointLightColors[0].x * 0.3f, pointLightColors[0].y * 0.3f, pointLightColors[0].z * 0.3f);
	m_cLightingShaderProgram->SetUniform("ptr_light_diffuse[0]", pointLightColors[0].x * 0.5f, pointLightColors[0].y * 0.5f, pointLightColors[0].z * 0.5f);
	m_cLightingShaderProgram->SetUniform("ptr_light_specular[0]", pointLightColors[0].x * 1.0f, pointLightColors[0].y * 1.0f, pointLightColors[0].z * 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_constant[0]", 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_linear[0]", 0.09f);
	m_cLightingShaderProgram->SetUniform("ptr_light_quadratic[0]", 0.032f);

	m_cLightingShaderProgram->SetUniform("ptr_light_position[1]", 2.3f, -3.3f, -4.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_ambient[1]", pointLightColors[1].x * 0.3f, pointLightColors[1].y * 0.3f, pointLightColors[1].z * 0.3f);
	m_cLightingShaderProgram->SetUniform("ptr_light_diffuse[1]", pointLightColors[1].x * 0.5f, pointLightColors[1].y * 0.5f, pointLightColors[1].z * 0.5f);
	m_cLightingShaderProgram->SetUniform("ptr_light_specular[1]", pointLightColors[1].x * 1.0f, pointLightColors[1].y * 1.0f, pointLightColors[1].z * 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_constant[1]", 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_linear[1]", 0.09f);
	m_cLightingShaderProgram->SetUniform("ptr_light_quadratic[1]", 0.032f);

	m_cLightingShaderProgram->SetUniform("ptr_light_position[2]", -4.0f, 2.0f, -2.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_ambient[2]", pointLightColors[2].x * 0.3f, pointLightColors[2].y * 0.3f, pointLightColors[2].z * 0.3f);
	m_cLightingShaderProgram->SetUniform("ptr_light_diffuse[2]", pointLightColors[2].x * 0.5f, pointLightColors[2].y * 0.5f, pointLightColors[2].z * 0.5f);
	m_cLightingShaderProgram->SetUniform("ptr_light_specular[2]", pointLightColors[2].x * 1.0f, pointLightColors[2].y * 1.0f, pointLightColors[2].z * 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_constant[2]", 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_linear[2]", 0.09f);
	m_cLightingShaderProgram->SetUniform("ptr_light_quadratic[2]", 0.032f);

	m_cLightingShaderProgram->SetUniform("ptr_light_position[3]", 0.0f, 0.0f, -3.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_ambient[3]", pointLightColors[3].x * 0.3f, pointLightColors[3].y * 0.3f, pointLightColors[3].z * 0.3f);
	m_cLightingShaderProgram->SetUniform("ptr_light_diffuse[3]", pointLightColors[3].x * 0.5f, pointLightColors[3].y * 0.5f, pointLightColors[3].z * 0.5f);
	m_cLightingShaderProgram->SetUniform("ptr_light_specular[3]", pointLightColors[3].x * 1.0f, pointLightColors[3].y * 1.0f, pointLightColors[3].z * 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_constant[3]", 1.0f);
	m_cLightingShaderProgram->SetUniform("ptr_light_linear[3]", 0.09f);
	m_cLightingShaderProgram->SetUniform("ptr_light_quadratic[3]", 0.032f);

	m_cLightingShaderProgram->SetUniform("spt_light_position", vCameraPos.x, vCameraPos.y, vCameraPos.z);
	m_cLightingShaderProgram->SetUniform("spt_light_direction", vCameraFront.x, vCameraFront.y, vCameraFront.z);
	m_cLightingShaderProgram->SetUniform("spt_light_ambient", 0.0f, 0.0f, 0.0f);
	m_cLightingShaderProgram->SetUniform("spt_light_diffuse", 0.8f, 0.8f, 0.0f);
	m_cLightingShaderProgram->SetUniform("spt_light_specular", 0.8f, 0.8f, 0.0f);
	m_cLightingShaderProgram->SetUniform("spt_light_constant", 1.0f);
	m_cLightingShaderProgram->SetUniform("spt_light_linear", 0.09f);
	m_cLightingShaderProgram->SetUniform("spt_light_quadratic", 0.032f);
	m_cLightingShaderProgram->SetUniform("spt_light_cutoff", glm::cos(glm::radians(12.5f)));
	m_cLightingShaderProgram->SetUniform("spt_light_outerCutoff", glm::cos(glm::radians(15.0f)));

	m_cLightingShaderProgram->RenderObjects();
	m_cLightingShaderProgram->UnbindVertexArray();

	m_cLampShaderProgram->UseProgram();
	m_cLampShaderProgram->BindVertexArray();
	m_cLampShaderProgram->SetUniform("uniColor", 1.0f, 1.0f, 1.0f);
	m_cLampShaderProgram->RenderObjects();
	m_cLampShaderProgram->UnbindVertexArray();
}
