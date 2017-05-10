#include "GLObject.h"

GLObject::GLObject(std::list<GLTransform> listModelTransform)
{
	m_listModelTransform = listModelTransform;
}

GLObject::GLObject(std::list<GLTransform> listModelTransform, std::map<std::string, GLUniform> mapSingleUniform)
{
	m_listModelTransform = listModelTransform;
	m_mapSingleUniform = mapSingleUniform;
}

GLObject::~GLObject()
{

}

std::list<GLTransform> GLObject::GetModelTransforms()
{
	return m_listModelTransform;
}

std::map<std::string, GLUniform> GLObject::GetSingleUniform()
{
	return m_mapSingleUniform;
}
