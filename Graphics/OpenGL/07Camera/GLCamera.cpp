#include "GLCamera.h"

const GLfloat PITCH_MAX = 89.0f;
const GLfloat PITCH_MIN = -89.0f;

GLCamera::GLCamera()
{
	m_vCameraPos = glm::vec3(0.0f, 0.0f, 15.0f);
	m_vCameraViewFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vCameraWalkFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vCameraViewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vCameraViewRight = glm::normalize(glm::cross(m_vCameraViewFront, m_vWorldUp));
	m_vCameraWalkRight = glm::normalize(glm::cross(m_vCameraWalkFront, m_vWorldUp));

	m_fCameraYaw = -90.0f;
	m_fCameraPitch = 0.0f;

	m_fCameraSpeed = 0.15f;
	m_fCameraSensitivity = 0.2f;

	memset(m_bIsKeyPress, 0, sizeof(m_bIsKeyPress));
	memset(m_bIsMouseButtonPress, 0, sizeof(m_bIsMouseButtonPress));
}

GLCamera::~GLCamera()
{

}

glm::vec3 GLCamera::GetPos()
{
	return m_vCameraPos;
}

glm::vec3 GLCamera::GetTarget()
{
	return (m_vCameraPos + m_vCameraViewFront);
}

glm::vec3 GLCamera::GetUp()
{
	return m_vCameraViewUp;
}

void GLCamera::ProcessKeyEvent(bool *isKeyPress)
{
	memcpy(m_bIsKeyPress, isKeyPress, sizeof(m_bIsKeyPress));
	Move();
}

void GLCamera::ProcessMouseButtonEvent(bool *isMouseButtonPress)
{
	memcpy(m_bIsMouseButtonPress, isMouseButtonPress, sizeof(m_bIsMouseButtonPress));
}

// press state && first press: just record lastX & lastY
// press state && not fist press: update xoffset yoffset
// not press state: change first press flat to true
void GLCamera::ProcessMouseEvent(double xpos, double ypos)
{
	static bool isFirstPress = true;
	static double lastX = 0;
	static double lastY = 0;
	if (m_bIsMouseButtonPress[GLFW_MOUSE_BUTTON_LEFT] || m_bIsMouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT]) {
		if (isFirstPress) {
			isFirstPress == false;
			lastX = xpos;
			lastY = ypos;
		}
		if (isFirstPress) {
			lastX = xpos;
			lastY = ypos;
			isFirstPress = false;
			return;
		}

		GLfloat xoffset = (xpos - lastX) * m_fCameraSensitivity;
		GLfloat yoffset = (lastY - ypos) * m_fCameraSensitivity;
		lastX = xpos;
		lastY = ypos;

		m_fCameraYaw += xoffset;
		m_fCameraPitch += yoffset;
		m_fCameraPitch = (m_fCameraPitch > PITCH_MAX) ? PITCH_MAX : m_fCameraPitch;
		m_fCameraPitch = (m_fCameraPitch < PITCH_MIN) ? PITCH_MIN : m_fCameraPitch;

		AdjustViewAttitude();
		if (m_bIsMouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT])
			AdjustWalkAttitude();
	}
	else {
		isFirstPress = true;
	}

}

void GLCamera::Move()
{
	// LOG_DBG("start moving! %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), cameraPos.x, cameraPos.y, cameraPos.z);
	if (m_bIsKeyPress[GLFW_KEY_W]) {
		m_vCameraPos += m_vCameraWalkFront * m_fCameraSpeed;
	}
	if (m_bIsKeyPress[GLFW_KEY_S]) {
		m_vCameraPos -= m_vCameraWalkFront * m_fCameraSpeed;
	}
	if (m_bIsKeyPress[GLFW_KEY_A]) {
		m_vCameraPos -= m_vCameraWalkRight * m_fCameraSpeed;
	}
	if (m_bIsKeyPress[GLFW_KEY_D]) {
		m_vCameraPos += m_vCameraWalkRight * m_fCameraSpeed;
	}
}

void GLCamera::AdjustViewAttitude()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(this->m_fCameraPitch));
	front.y = sin(glm::radians(this->m_fCameraPitch));
	front.z = sin(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(this->m_fCameraPitch));

	// LOG_DBG("m_vCameraViewFront %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), front.x, front.y, front.z);
	m_vCameraViewFront = glm::normalize(front);
	m_vCameraViewRight = glm::normalize(glm::cross(m_vCameraViewFront, m_vWorldUp));
	m_vCameraViewUp = glm::normalize(glm::cross(m_vCameraViewRight, m_vCameraViewFront));
}

void GLCamera::AdjustWalkAttitude()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = sin(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(0.0f));

	// LOG_DBG("m_vCameraViewFront %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), front.x, front.y, front.z);
	m_vCameraWalkFront = glm::normalize(front);
	m_vCameraWalkRight = glm::normalize(glm::cross(m_vCameraWalkFront, m_vWorldUp));
}