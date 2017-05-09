#include "GLCamera.h"
#include "GLWindow.h"

const GLfloat PITCH_MAX = 89.0f;
const GLfloat PITCH_MIN = -89.0f;
const GLfloat ASPECT_MAX = 45.0f;
const GLfloat ASPECT_MIN = 1.0f;
const GLfloat WALK_PER_SECOND = 0.05f;

GLCamera::GLCamera(GLWindow *cWindow)
{
	m_cWindow = cWindow;

	m_vCameraPosition = glm::vec3(0.0f, 0.0f, 15.0f);
	m_vCameraViewFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vCameraWalkFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_vCameraViewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_vCameraViewRight = glm::normalize(glm::cross(m_vCameraViewFront, m_vWorldUp));
	m_vCameraWalkRight = glm::normalize(glm::cross(m_vCameraWalkFront, m_vWorldUp));

	m_fCameraYaw = -90.0f;
	m_fCameraPitch = 0.0f;

	m_fCameraSensitivity = 0.2f;

	m_fAspect = 45.0f;
}

GLCamera::~GLCamera()
{

}

glm::vec3 GLCamera::GetPosition()
{
	return m_vCameraPosition;
}

glm::vec3 GLCamera::GetTarget()
{
	return (m_vCameraPosition + m_vCameraViewFront);
}

glm::vec3 GLCamera::GetFront()
{
	return m_vCameraViewFront;
}

glm::vec3 GLCamera::GetUp()
{
	return m_vCameraViewUp;
}

GLfloat GLCamera::GetAspect()
{
	return m_fAspect;
}

void GLCamera::SetDeltaTime()
{
	static bool bIsFirstFrame = true;
	static GLfloat fLastTime = glfwGetTime();

	if (bIsFirstFrame) {
		bIsFirstFrame = false;
	}

	GLfloat fCurrentTime = glfwGetTime();
	GLfloat fDeltaTime = fCurrentTime - fLastTime;

	m_fDeltaTime = fDeltaTime;
	m_fCameraSpeed = m_fDeltaTime * WALK_PER_SECOND;
}

void GLCamera::ProcessEvents()
{
	GLInputData cInputData;
	m_cWindow->GetInput(&cInputData);

	ProcessKeyEvent(cInputData.bIsKeyPress);
	ProcessMouseEvent(cInputData.bIsMouseButtonPress, cInputData.dMousePosX, cInputData.dMousePosY);

	if (cInputData.iScrollPlusCnt > 0) {
		ProcessScollEvent(1.0f);
		m_cWindow->DecreaseScrollPlusCnt();
	}
	if (cInputData.iScrollMinusCnt > 0) {
		ProcessScollEvent(-1.0f);
		m_cWindow->DecreaseScrollMinusCnt();
	}
}

void GLCamera::ProcessKeyEvent(bool *isKeyPress)
{
	// LOG_DBG("start moving! %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), cameraPos.x, cameraPos.y, cameraPos.z);
	if (isKeyPress[GLFW_KEY_W]) {
		m_vCameraPosition += m_vCameraWalkFront * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_S]) {
		m_vCameraPosition -= m_vCameraWalkFront * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_A]) {
		m_vCameraPosition -= m_vCameraWalkRight * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_D]) {
		m_vCameraPosition += m_vCameraWalkRight * m_fCameraSpeed;
	}
}

// press state && first press: just record lastX & lastY
// press state && not fist press: update xoffset yoffset
// not press state: change first press flat to true
void GLCamera::ProcessMouseEvent(bool *isMouseButtonPress, double xpos, double ypos)
{
	static bool isFirstPress = true;
	static double lastX = 0;
	static double lastY = 0;
	if (isMouseButtonPress[GLFW_MOUSE_BUTTON_LEFT] || isMouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT]) {
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
		if (isMouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT])
			AdjustWalkAttitude();
	}
	else {
		isFirstPress = true;
	}
}

void GLCamera::ProcessScollEvent(double yoffset)
{
	m_fAspect -= yoffset;
	m_fAspect = (m_fAspect > ASPECT_MAX) ? ASPECT_MAX : m_fAspect;
	m_fAspect = (m_fAspect < ASPECT_MIN) ? ASPECT_MIN : m_fAspect;
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
