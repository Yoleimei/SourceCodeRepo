#pragma once

#include "GL.h"

class GLObject
{
public:
	GLObject(std::list<GLTransform> listModelTransoform);
	GLObject(std::list<GLTransform> listModelTransoform, std::map<std::string, GLUniform> listSingleUniform);
	virtual ~GLObject();

	std::list<GLTransform> GetModelTransforms();
	std::map<std::string, GLUniform> GetSingleUniform();

private:
	std::list<GLTransform> m_listModelTransform;
	std::map<std::string, GLUniform> m_mapSingleUniform;
};