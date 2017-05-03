#pragma once

class GLFragmentShader
{
public:
	GLFragmentShader() { }
	virtual ~GLFragmentShader() { }

private:
	unsigned int m_iFragmentShader;

	void CompileShader();
};