// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLFramework.h"
#include "GLLib.h"
#include "GLExtensionWrangler.h"

#include <iostream>

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

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
	GLLib::Viewport(0, 0, m_iWidth, m_iHeight);

	return true;
}

void GLFramework::Run()
{
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

bool GLFramework::WindowShouldClose()
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
	GLLib::ClearColor(0.78f, 0.93f, 0.8f, 1.0f);
	GLLib::Clear(GL_COLOR_BUFFER_BIT);
}
