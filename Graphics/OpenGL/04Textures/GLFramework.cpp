#include "GLFramework.h"

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

GLfloat vertices[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   2.0f, 2.0f, // Top Right
	0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   2.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
	-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f  // Top Left 
};
GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};

GLfloat uniMixValue = 0.2f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (GLFW_KEY_ESCAPE == key && GLFW_RELEASE == action) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (GLFW_KEY_UP == key && GLFW_RELEASE == action) {
		uniMixValue = (uniMixValue + 0.1f > 1.0f) ? 1.0f : (uniMixValue + 0.1f);
		//LOG_DBG("uniMixValue:%f\n", uniMixValue);
	}
	if (GLFW_KEY_DOWN == key && GLFW_RELEASE == action) {
		uniMixValue = (uniMixValue - 0.1f < 0.0f) ? 0.0f : (uniMixValue - 0.1f);
		//LOG_DBG("uniMixValue:%f\n", uniMixValue);
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
	SetKeyCallback();

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	GetFramebufferSize();
	LOG_DBG("Width=%d, Height=%d\n", m_iWidth, m_iHeight);
	glViewport(0, 0, m_iWidth, m_iHeight);

	return true;
}

void GLFramework::Run()
{
	m_cShaderProgram = new GLShaderProgram();
	LOG_DBG("ShaderProgram=%d\n", m_cShaderProgram->GetProgram());
	m_cShaderProgram->LinkProgram();
	LOG_DBG("Link Shader Program success.\n");
	m_cShaderProgram->RegisterVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));

	m_cTexture1 = new GLTexture();
	m_cTexture1->GenerateMipMap("container.jpg", GL_REPEAT);
	m_cTexture2 = new GLTexture();
	m_cTexture2->GenerateMipMap("awesomeface.png", GL_MIRRORED_REPEAT);

	// Game loop
	while (!WindowShouldClose())
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		PollEvents();

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

void GLFramework::SetKeyCallback()
{
	glfwSetKeyCallback(m_sWindow, key_callback);
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
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw our first triangle
	m_cShaderProgram->UseProgram();

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

	m_cShaderProgram->BindVertexArray();
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_cShaderProgram->UnbindVertexArray();
}
