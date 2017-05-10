#include "GLObject.h"

GLObject::GLObject(std::list<GLTransform> listModelTransform)
{
	m_listModelTransform = listModelTransform;
}

GLObject::~GLObject()
{

}

std::list<GLTransform> GLObject::GetModelTransforms()
{
	return m_listModelTransform;
}