#include "GLObject.h"

GLObject::GLObject(glm::vec3 vPosition)
{
	m_vObjectPosition = vPosition;
}

GLObject::~GLObject()
{

}

glm::vec3 GLObject::GetPosition()
{
	return m_vObjectPosition;
}