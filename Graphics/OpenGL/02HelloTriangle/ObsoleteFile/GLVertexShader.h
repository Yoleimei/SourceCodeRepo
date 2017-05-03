#pragma once

class GLVertexShader
{
public:
	GLVertexShader() { }
	virtual ~GLVertexShader() { }

private:
	unsigned int m_iVertexShader;

	void CompileShader();
};