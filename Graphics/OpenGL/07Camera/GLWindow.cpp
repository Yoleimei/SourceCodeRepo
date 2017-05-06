#include "GLWindow.h"

// Window dimensions
const GLuint WIDTH = 1920;
const GLuint HEIGHT = 1080;

GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

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

GLfloat uniMixValue = 0.2f;
static bool isKeyPress[1024] = { false };
static bool isMouseButtonPress[16] = { false };
static double dMousePosX = 0.0;
static double dMousePosY = 0.0;
static int iScrollPlusCnt = 0;
static int iScrollMinusCnt = 0;

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
	if (yoffset > 0)
		iScrollPlusCnt++;
	else
		iScrollMinusCnt++;
}

GLWindow::GLWindow(const char* title, bool isFullScreen)
	: m_iWidth(WIDTH)
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
}

GLWindow::~GLWindow()
{

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
	m_cShaderProgram = new GLShaderProgram();
	LOG_DBG("ShaderProgram=%d\n", m_cShaderProgram->GetProgram());
	m_cShaderProgram->LinkProgram();
	LOG_DBG("Link Shader Program success.\n");
	m_cShaderProgram->RegisterVertexArray(vertices, sizeof(vertices), NULL, 0);

	m_cTexture1 = new GLTexture();
	m_cTexture1->GenerateMipMap("container.jpg", GL_REPEAT);
	m_cTexture2 = new GLTexture();
	m_cTexture2->GenerateMipMap("awesomeface.png", GL_MIRRORED_REPEAT);

	m_cCamera = new GLCamera();

	GLfloat fLastTime = glfwGetTime();
	// Game loop
	while (!glfwWindowShouldClose(m_sWindow))
	{
		GLfloat fCurrentTime = glfwGetTime();
		GLfloat fDeltaTime = fCurrentTime - fLastTime;
		m_cCamera->SetDeltaTime(fDeltaTime);

		glfwPollEvents();
		m_cCamera->ProcessKeyEvent(isKeyPress);
		m_cCamera->ProcessMouseButtonEvent(isMouseButtonPress);
		m_cCamera->ProcessMouseEvent(dMousePosX, dMousePosY);
		if (iScrollPlusCnt > 0) {
			m_cCamera->ProcessScollEvent(1.0f);
			iScrollPlusCnt--;
		}
		if (iScrollMinusCnt > 0) {
			m_cCamera->ProcessScollEvent(-1.0f);
			iScrollMinusCnt--;
		}

		// Render
		Render();

		glfwSwapBuffers(m_sWindow);
	}

	m_cShaderProgram->UnregisterVertexArray();
}

void GLWindow::Render()
{
	// Clear the colorbuffer
	glClearColor(0.78f, 0.93f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw our first triangle
	m_cShaderProgram->UseProgram();
	m_cShaderProgram->BindVertexArray();

	m_cTexture1->ActiveTexture(GL_TEXTURE0);
	m_cTexture1->BindTexture();
	GLint uniformLocation1 = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniTexture1");
	glUniform1i(uniformLocation1, 0);

	m_cTexture2->ActiveTexture(GL_TEXTURE1);
	m_cTexture2->BindTexture();
	GLint uniformLocation2 = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniTexture2");
	glUniform1i(uniformLocation2, 1);

	GLint myUniformLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniMixValue");
	glUniform1f(myUniformLocation, uniMixValue);

	for (int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
		glm::mat4 model = glm::translate(glm::mat4(), cubePositions[i]);
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 0.2f * (i + 1) * 90.0f), glm::vec3(1.0f, 0.7f, 0.3f));
		GLuint uniModelLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniModel");
		glUniformMatrix4fv(uniModelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view = glm::lookAt(m_cCamera->GetPos(), m_cCamera->GetTarget(), m_cCamera->GetUp());
		GLuint uniViewLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniView");
		glUniformMatrix4fv(uniViewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::perspective(glm::radians(m_cCamera->GetAspect()), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		GLuint uniProjectionLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniProjection");
		glUniformMatrix4fv(uniProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	m_cShaderProgram->UnbindVertexArray();
}
