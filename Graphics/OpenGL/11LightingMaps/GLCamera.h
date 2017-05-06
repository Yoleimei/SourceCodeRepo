#pragma once

#include "GL.h"

class GLWindow;

class GLCamera
{
public:
	GLCamera(GLWindow *cWindow);
	virtual ~GLCamera();

	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	glm::vec3 GetUp();
	GLfloat GetAspect();

	void SetDeltaTime();
	void ProcessEvents();
	void ProcessKeyEvent(bool *isKeyPress);
	void ProcessMouseEvent(bool *isMouseButtonPress, double xpos, double ypos);
	void ProcessScollEvent(double yoffset);

private:
	GLWindow *m_cWindow;
	glm::vec3 m_vCameraPosition;
	glm::vec3 m_vCameraViewFront;
	glm::vec3 m_vCameraViewRight;
	glm::vec3 m_vCameraViewUp;
	glm::vec3 m_vCameraWalkFront;
	glm::vec3 m_vCameraWalkRight;
	glm::vec3 m_vWorldUp;

	GLfloat m_fCameraYaw;
	GLfloat m_fCameraPitch;

	GLfloat m_fDeltaTime;
	GLfloat m_fCameraSpeed;
	GLfloat m_fCameraSensitivity;

	GLfloat m_fAspect;

	void AdjustViewAttitude();
	void AdjustWalkAttitude();
};