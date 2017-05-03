#include "GLLib.h"

// typedef char         GLchar;
// typedef int          GLint;
// typedef unsigned int GLuint
// typedef ptrdiff_t    GLsizeiptr
// typedef unsigned int GLenum
// typedef int          GLsizei;
// typedef float        GLclampf
// typedef unsigned int GLbitfiled

void GLLib::Test()
{
}

void GLLib::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

void GLLib::ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(red, green, blue, alpha);
}

void GLLib::Clear(GLbitfield mask)
{
	glClear(mask);
}

GLenum GLLib::CreateShader(GLenum type)
{
	return glCreateShader(type);
}

void GLLib::DeleteShader(GLuint shader)
{
	glDeleteShader(shader);
}

void GLLib::ShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length)
{
	glShaderSource(shader, count, string, length);
}

void GLLib::CompileShader(GLuint shader)
{
	glCompileShader(shader);
}

void GLLib::GetShaderiv(GLuint shader, GLenum pname, GLint *param)
{
	glGetShaderiv(shader, pname, param);
}

void GLLib::GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infoLog)
{
	glGetShaderInfoLog(shader, bufsize, length, infoLog);
}

GLint GLLib::GetUniformLocation(GLuint program, const GLchar * name)
{
	return glGetUniformLocation(program, name);
}

void GLLib::Uniform1f(GLint location, GLfloat v0)
{
	glUniform1f(location, v0);
}

void GLLib::Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(location, v0, v1, v2, v3);
}

GLuint GLLib::CreateProgram()
{
	return glCreateProgram();
}

void GLLib::AttachShader(GLuint program, GLuint shader)
{
	glAttachShader(program, shader);
}

void GLLib::LinkProgram(GLuint program)
{
	glLinkProgram(program);
}

void GLLib::UseProgram(GLuint program)
{
	glUseProgram(program);
}

void GLLib::GetProgramiv(GLuint program, GLenum pname, GLint *param)
{
	glGetProgramiv(program, pname, param);
}

void GLLib::GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei *length, GLchar *infoLog)
{
	glGetProgramInfoLog(program, bufsize, length, infoLog);
}

void GLLib::GenVertexArrays(GLsizei n, GLuint *arrays)
{
	glGenVertexArrays(n, arrays);
}

void GLLib::BindVertexArray(GLuint array)
{
	glBindVertexArray(array);
}

void GLLib::DeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
	glDeleteVertexArrays(n, arrays);
}

void GLLib::GenBuffers(GLsizei n, GLuint *buffers)
{
	glGenBuffers(n, buffers);
}

void GLLib::BindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
}

void GLLib::DeleteBuffers(GLsizei n, const GLuint *buffers)
{
	glDeleteBuffers(n, buffers);
}

void GLLib::BufferData(GLenum target, GLsizeiptr size, const void *data, unsigned int usage)
{
	glBufferData(target, size, data, usage);
}

void GLLib::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GLLib::EnableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
}

void GLLib::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
}

void GLLib::DrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{
	glDrawElements(mode, count, type, indices);
}
