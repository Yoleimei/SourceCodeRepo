#pragma once

#include "GL.h"

class GLCamera
{
public:
	GLCamera();
	virtual ~GLCamera();

	glm::vec3 GetPos();
	glm::vec3 GetTarget();
	glm::vec3 GetUp();
	GLfloat GetAspect();

	void SetDeltaTime(GLfloat fDeltaTime);

	void ProcessKeyEvent(bool *isKeyPress);
	void ProcessMouseButtonEvent(bool *isMouseButtonPress);
	void ProcessMouseEvent(double xpos, double ypos);
	void ProcessScollEvent(double yoffset);

private:
	glm::vec3 m_vCameraPos;
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

	bool m_bIsKeyPress[1024];
	bool m_bIsMouseButtonPress[16];

	void Move();
	void AdjustViewAttitude();
	void AdjustWalkAttitude();
};