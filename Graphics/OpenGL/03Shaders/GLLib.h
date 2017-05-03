#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class GLLib
{
public:
	static void Test();

	static void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	static void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	static void Clear(GLbitfield mask);

	static GLenum CreateShader(GLenum type);
	static void DeleteShader(GLuint shader);
	static void ShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length);
	static void CompileShader(GLuint shader);
	static void GetShaderiv(GLuint shader, GLenum pname, GLint *param);
	static void GetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infoLog);

	static GLint GetUniformLocation(GLuint program, const GLchar * name);
	static void Uniform1f(GLint location, GLfloat v0);
	static void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	static GLuint CreateProgram();
	static void AttachShader(GLuint program, GLuint shader);
	static void LinkProgram(GLuint program);
	static void UseProgram(GLuint program);
	static void GetProgramiv(GLuint program, GLenum pname, GLint *param);
	static void GetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei *length, GLchar *infoLog);

	static void GenVertexArrays(GLsizei n, GLuint *arrays);
	static void BindVertexArray(GLuint array);
	static void DeleteVertexArrays(GLsizei n, const GLuint *arrays);

	static void GenBuffers(GLsizei n, GLuint *buffers);
	static void BindBuffer(GLenum target, GLuint buffer);
	static void DeleteBuffers(GLsizei n, const GLuint *buffers);

	static void BufferData(GLenum target, GLsizeiptr size, const void *data, unsigned int usage);
	static void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	static void EnableVertexAttribArray(GLuint index);

	static void DrawArrays(GLenum mode, GLint first, GLsizei count);
	static void DrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices);
};
