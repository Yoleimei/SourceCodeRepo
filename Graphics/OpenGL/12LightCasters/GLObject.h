#pragma once

#include "GL.h"

class GLObject
{
public:
	GLObject(glm::vec3 vPosition);
	virtual ~GLObject();

	glm::vec3 GetPosition();

private:
	glm::vec3 m_vObjectPosition;
};