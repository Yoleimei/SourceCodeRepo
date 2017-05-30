#include "GLObject.h"

GLObject::GLObject(std::list<GLTransform> listModelTransform)
{
	m_listModelTransform = listModelTransform;
}

GLObject::GLObject(std::list<GLTransform> listModelTransform, std::map<std::string, GLUniform> mapOwnUniform)
{
	m_listModelTransform = listModelTransform;
	m_mapOwnUniform = mapOwnUniform;
}

GLObject::~GLObject()
{

}

std::list<GLTransform> GLObject::GetModelTransforms()
{
	return m_listModelTransform;
}

std::map<std::string, GLUniform> GLObject::GetOwnUniform()
{
	return m_mapOwnUniform;
}
