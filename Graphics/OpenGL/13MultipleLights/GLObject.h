#pragma once

#include "GL.h"

class GLObject
{
public:
	GLObject(std::list<GLTransform> listModelTransoform);
	virtual ~GLObject();

	std::list<GLTransform> GetModelTransforms();

private:
	std::list<GLTransform> m_listModelTransform;
};