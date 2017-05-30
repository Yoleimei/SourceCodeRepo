#pragma once

#include "GL.h"

class GLWindow;

class GLCamera
{
public:
	GLCamera(GLWindow *cWindow);
	virtual ~GLCamera();

	void Init();

	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	glm::vec3 GetFront();
	glm::vec3 GetUp();
	GLfloat GetAspect();

	void SetDeltaTime();
	void ProcessEvents();

private:
	GLWindow *m_cWindow;
	glm::vec3 m_v3CameraPosition;
	glm::vec3 m_v3CameraViewFront;
	glm::vec3 m_v3CameraViewRight;
	glm::vec3 m_v3CameraViewUp;
	glm::vec3 m_v3WorldUp;
	glm::vec3 m_v3CameraWalkFront;
	glm::vec3 m_v3CameraWalkRight;

	GLfloat m_fCameraYaw;
	GLfloat m_fCameraPitch;

	GLfloat m_fDeltaTime;
	GLfloat m_fCameraSpeed;
	GLfloat m_fCameraSensitivity;

	GLfloat m_fAspect;

	void ProcessKeyEvent(bool *isKeyPress);
	void ProcessMouseEvent(bool *isMouseButtonPress, double xpos, double ypos);
	void ProcessScollEvent(double yoffset);

	void AdjustViewAttitude();
	void AdjustWalkAttitude();
};