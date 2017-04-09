// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "GLLib.h"

void GLLib::Viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void GLLib::ClearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLLib::Clear(unsigned int mask)
{
	glClear(mask);
}

unsigned int GLLib::CreateShader(unsigned int type)
{
	return glCreateShader(type);
}

void GLLib::DeleteShader(unsigned int shader)
{
	glDeleteShader(shader);
}

void GLLib::ShaderSource(unsigned int shader, int count, const char * const *string, const int *length) {
	glShaderSource(shader, count, string, length);
}

void GLLib::CompileShader(unsigned int shader)
{
	glCompileShader(shader);
}

void GLLib::GetShaderiv(unsigned int shader, unsigned int pname, int *param)
{
	glGetShaderiv(shader, pname, param);
}

void GLLib::GetShaderInfoLog(unsigned int shader, int bufsize, int *length, char *infoLog)
{
	glGetShaderInfoLog(shader, bufsize, length, infoLog);
}

unsigned int GLLib::CreateProgram()
{
	return glCreateProgram();
}

void GLLib::AttachShader(unsigned int program, unsigned int shader)
{
	glAttachShader(program, shader);
}

void GLLib::LinkProgram(unsigned int program)
{
	glLinkProgram(program);
}

void GLLib::UseProgram(unsigned int program)
{
	glUseProgram(program);
}

void GLLib::GetProgramiv(unsigned int program, unsigned int pname, int *param)
{
	glGetProgramiv(program, pname, param);
}

void GLLib::GetProgramInfoLog(unsigned int program, int bufsize, int *length, char *infoLog)
{
	glGetProgramInfoLog(program, bufsize, length, infoLog);
}

void GLLib::GenVertexArrays(int n, unsigned int *arrays)
{
	glGenVertexArrays(n, arrays);
}

void GLLib::BindVertexArray(unsigned int array)
{
	glBindVertexArray(array);
}

void GLLib::DeleteVertexArrays(int n, unsigned int *arrays)
{
	glDeleteVertexArrays(n, arrays);
}

void GLLib::GenBuffers(int n, unsigned int *buffers)
{
	glGenBuffers(n, buffers);
}

void GLLib::BindBuffer(unsigned int target, unsigned int buffer)
{
	glBindBuffer(target, buffer);
}

void GLLib::DeleteBuffers(int n, unsigned int *buffers)
{
	glDeleteBuffers(n, buffers);
}

void GLLib::BufferData(unsigned int target, ptrdiff_t size, const void *data, unsigned int usage)
{
	glBufferData(target, size, data, usage);
}

void GLLib::VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void *pointer)
{
	glVertexAttribPointer(index, size, type, normalized, size, pointer);
}

void GLLib::EnableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(index);
}

void GLLib::DrawArrays(unsigned int mode, int first, int count)
{
	glDrawArrays(mode, first, count);
}

void GLLib::DrawElements(unsigned int mode, int count, unsigned int type, const void *indices)
{
	glDrawElements(mode, count, type, indices);
}
