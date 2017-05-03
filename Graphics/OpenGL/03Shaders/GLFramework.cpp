#include "GLFramework.h"

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom Left,  Red
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right, Green
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Top,          Blue
};
GLuint indices[] = {  // Note that we start from 0!
	0, 1, 2
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool GLFramework::Init()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

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

	if (!GLExtensionWrangler::Init()) {
		return false;
	}

	// Define the viewport dimensions
	GetFramebufferSize();
	std::cout << "Width=" << m_iWidth << ", Height=" << m_iHeight << std::endl;
	GLLib::Viewport(0, 0, m_iWidth, m_iHeight);

	return true;
}

void GLFramework::Run()
{
	GLShaderProgram *cShaderProgram = new GLShaderProgram();
	std::cout << "ShaderProgram=" << cShaderProgram->GetProgram() << std::endl;
	cShaderProgram->LinkProgram();
	std::cout << "Link Shader Program success." << std::endl;
	cShaderProgram->RegisterVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));

	// Game loop
	while (!WindowShouldClose())
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		PollEvents();

		// Render
		Render(cShaderProgram);

		// Swap the screen buffers
		SwapBuffers();
	}

	cShaderProgram->UnregisterVertexArray();
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
		std::cout << "Failed to create GLFW window" << std::endl;
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

void GLFramework::Render(GLShaderProgram *cShaderProgram)
{
	// Clear the colorbuffer
	GLLib::ClearColor(0.78f, 0.93f, 0.8f, 1.0f);
	GLLib::Clear(GL_COLOR_BUFFER_BIT);

	// Draw our first triangle
	cShaderProgram->UseProgram();

	// Update uniform
	GLfloat timeValue = glfwGetTime();
	GLfloat redValue = sin(timeValue) / 2 + 0.5;
	GLint myUniformLocation = GLLib::GetUniformLocation(cShaderProgram->GetProgram(), "myRed");
	GLLib::Uniform1f(myUniformLocation, redValue);

	cShaderProgram->BindVertexArray();
	//GLLib::DrawArrays(GL_TRIANGLES, 0, 6);
	GLLib::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	cShaderProgram->UnbindVertexArray();
}
