#include "GLFramework.h"

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

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
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -5.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -2.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLfloat uniMixValue = 0.2f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat cameraYaw = 0.0f;
GLfloat cameraPitch = 0.0f;
static bool isKeyPress[1024] = { false };

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

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool isFirstPress = true;
	static GLfloat lastX = 0;
	static GLfloat lastY = 0;
	static const GLfloat sensitivity = 0.01f;
	if (isFirstPress) {
		lastX = xpos;
		lastY = ypos;
		isFirstPress = false;
		return;
	}

	GLfloat xoffset = (xpos - lastX) * sensitivity;
	GLfloat yoffset = (lastY - ypos) * sensitivity;
	lastX = xpos;
	lastY = ypos;
	cameraYaw += xoffset;
	cameraPitch += yoffset;
	cameraPitch = (cameraPitch >  89.0f) ?  89.0f : cameraPitch;
	cameraPitch = (cameraPitch < -89.0f) ? -89.0f : cameraPitch;

	glm::vec3 cameraFront = glm::normalize(targetPos - cameraPos);
	glm::vec3 cameraRight = glm::cross(cameraFront, worldUp);
	glm::vec3 cameraUp = glm::cross(cameraRight, cameraFront);
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(cameraYaw), cameraUp);
	trans = glm::rotate(trans, glm::radians(cameraPitch), cameraRight);
	glm::vec4 tmpVec = (trans * glm::vec4(cameraFront, 1));
	cameraFront.x = tmpVec.x;
	cameraFront.y = tmpVec.y;
	cameraFront.z = tmpVec.z;
	targetPos = cameraPos + cameraFront * glm::distance(cameraPos, targetPos);
}

static void do_movement()
{
	// LOG_DBG("start moving! %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), cameraPos.x, cameraPos.y, cameraPos.z);
	GLfloat cameraSpeed = 0.15f;
	glm::vec3 cameraFront = glm::normalize(targetPos - cameraPos);
	glm::vec3 cameraBack = glm::normalize(cameraPos - targetPos);
	glm::vec3 cameraLeft = glm::cross(cameraBack, worldUp);
	glm::vec3 cameraRight = glm::cross(cameraFront, worldUp);
	if (isKeyPress[GLFW_KEY_W]) {
		if (glm::distance(cameraPos, targetPos) > 1.0f)
			cameraPos += cameraFront * cameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_S]) {
		cameraPos += cameraBack * cameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_A]) {
		cameraPos += cameraLeft * cameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_D]) {
		cameraPos += cameraRight * cameraSpeed;
	}
}

bool GLFramework::Init()
{
	LOG_DBG("Starting GLFW context, OpenGL 3.3\n");

	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (!CreateWindow("LearnOpenGL")) {
		return false;
	}

	MakeContextCurrent();

	// Set the required callback functions
	SetCallback();

	// Cursor Options
	// glfwSetInputMode(m_sWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	GetFramebufferSize();
	LOG_DBG("Width=%d, Height=%d\n", m_iWidth, m_iHeight);
	glViewport(0, 0, m_iWidth, m_iHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	return true;
}

void GLFramework::Run()
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

	// Game loop
	while (!WindowShouldClose())
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		PollEvents();
		do_movement();

		// Render
		Render();

		// Swap the screen buffers
		SwapBuffers();
	}

	m_cShaderProgram->UnregisterVertexArray();
}

void GLFramework::Terminate()
{
	glfwTerminate();
}

bool GLFramework::CreateWindow(const char *title)
{
	// Create a GLFWwindow object that we can use for GLFW's functions
	m_sWindow = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);
	if (m_sWindow == nullptr)
	{
		LOG_ERR("Failed to create GLFW window\n");
		return false;
	}

	return true;
}

void GLFramework::SetWindowShouldClose(int value)
{
	glfwSetWindowShouldClose(m_sWindow, value);
}

int GLFramework::WindowShouldClose()
{
	return glfwWindowShouldClose(m_sWindow);
}

void GLFramework::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_sWindow);
}

void GLFramework::SetCallback()
{
	glfwSetKeyCallback(m_sWindow, key_callback);
	glfwSetCursorPosCallback(m_sWindow, mouse_callback);
}

void GLFramework::PollEvents()
{
	glfwPollEvents();
}

void GLFramework::GetFramebufferSize()
{
	glfwGetFramebufferSize(m_sWindow, &m_iWidth, &m_iHeight);
}

void GLFramework::SwapBuffers()
{
	glfwSwapBuffers(m_sWindow);
}

void GLFramework::Render()
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
		model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 0.2f * (i+1) * 90.0f), glm::vec3(1.0f, 0.7f, 0.3f));
		GLuint uniModelLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniModel");
		glUniformMatrix4fv(uniModelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view = glm::lookAt(cameraPos, targetPos, worldUp);
		GLuint uniViewLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniView");
		glUniformMatrix4fv(uniViewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		GLuint uniProjectionLocation = glGetUniformLocation(m_cShaderProgram->GetProgram(), "uniProjection");
		glUniformMatrix4fv(uniProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	m_cShaderProgram->UnbindVertexArray();
}
