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
}

GLCamera::~GLCamera()
{

}

void GLCamera::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	m_v3CameraPosition = glm::vec3(0.0f, 0.0f, 15.0f);
	m_v3CameraViewFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_v3CameraWalkFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_v3CameraViewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_v3WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_v3CameraViewRight = glm::normalize(glm::cross(m_v3CameraViewFront, m_v3WorldUp));
	m_v3CameraWalkRight = glm::normalize(glm::cross(m_v3CameraWalkFront, m_v3WorldUp));

	m_fCameraYaw = -90.0f;
	m_fCameraPitch = 0.0f;

	m_fCameraSensitivity = 0.2f;

	m_fAspect = 45.0f;
}

glm::vec3 GLCamera::GetPosition()
{
	return m_v3CameraPosition;
}

glm::vec3 GLCamera::GetTarget()
{
	return (m_v3CameraPosition + m_v3CameraViewFront);
}

glm::vec3 GLCamera::GetFront()
{
	return m_v3CameraViewFront;
}

glm::vec3 GLCamera::GetUp()
{
	return m_v3CameraViewUp;
}

GLfloat GLCamera::GetAspect()
{
	return m_fAspect;
}

void GLCamera::SetDeltaTime()
{
	static bool bIsFirstFrame = true;
	static GLfloat fLastTime = (GLfloat)glfwGetTime();

	if (bIsFirstFrame) {
		bIsFirstFrame = false;
	}

	GLfloat fCurrentTime = (GLfloat)glfwGetTime();
	GLfloat fDeltaTime = fCurrentTime - fLastTime;

	m_fDeltaTime = fDeltaTime;
	m_fCameraSpeed = m_fDeltaTime * WALK_PER_SECOND;
}

void GLCamera::ProcessEvents()
{
	GLInputData sInputData = m_cWindow->GetInput();

	ProcessKeyEvent(sInputData.bIsKeyPress);
	ProcessMouseEvent(sInputData.bIsMouseButtonPress, sInputData.dMousePosX, sInputData.dMousePosY);

	if (sInputData.iScrollPlusCnt > 0) {
		ProcessScollEvent(1.0f);
		m_cWindow->DecreaseScrollPlusCnt();
	}
	if (sInputData.iScrollMinusCnt > 0) {
		ProcessScollEvent(-1.0f);
		m_cWindow->DecreaseScrollMinusCnt();
	}
}

void GLCamera::ProcessKeyEvent(bool *isKeyPress)
{
	// LOG_DBG("start moving! %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), cameraPos.x, cameraPos.y, cameraPos.z);
	if (isKeyPress[GLFW_KEY_W]) {
		m_v3CameraPosition += m_v3CameraWalkFront * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_S]) {
		m_v3CameraPosition -= m_v3CameraWalkFront * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_A]) {
		m_v3CameraPosition -= m_v3CameraWalkRight * m_fCameraSpeed;
	}
	if (isKeyPress[GLFW_KEY_D]) {
		m_v3CameraPosition += m_v3CameraWalkRight * m_fCameraSpeed;
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
			lastX = xpos;
			lastY = ypos;
			isFirstPress = false;
			return;
		}

		GLfloat xoffset = (GLfloat)(xpos - lastX) * m_fCameraSensitivity;
		GLfloat yoffset = (GLfloat)(lastY - ypos) * m_fCameraSensitivity;
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
	m_fAspect -= (GLfloat)yoffset;
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
	m_v3CameraViewFront = glm::normalize(front);
	m_v3CameraViewRight = glm::normalize(glm::cross(m_v3CameraViewFront, m_v3WorldUp));
	m_v3CameraViewUp = glm::normalize(glm::cross(m_v3CameraViewRight, m_v3CameraViewFront));
}

void GLCamera::AdjustWalkAttitude()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = sin(glm::radians(this->m_fCameraYaw)) * cos(glm::radians(0.0f));

	// LOG_DBG("m_vCameraViewFront %.2lfs (%3.2lf, %3.2lf, %3.2lf)\n", glfwGetTime(), front.x, front.y, front.z);
	m_v3CameraWalkFront = glm::normalize(front);
	m_v3CameraWalkRight = glm::normalize(glm::cross(m_v3CameraWalkFront, m_v3WorldUp));
}
