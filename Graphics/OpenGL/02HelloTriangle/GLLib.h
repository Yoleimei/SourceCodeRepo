#pragma once

typedef int ptrdiff_t;

class GLLib
{
public:
	static void Viewport(int x, int y, int width, int  height);
	static void ClearColor(float red, float green, float blue, float alpha);
	static void Clear(unsigned int mask);

	static unsigned int CreateShader(unsigned int type);
	static void DeleteShader(unsigned int shader);
	static void ShaderSource(unsigned int shader, int count, const char * const * string, const int *length);
	static void CompileShader(unsigned int shader);
	static void GetShaderiv(unsigned int shader, unsigned int pname, int *param);
	static void GetShaderInfoLog(unsigned int shader, int bufsize, int *length, char *infoLog);

	static unsigned int CreateProgram();
	static void AttachShader(unsigned int program, unsigned int shader);
	static void LinkProgram(unsigned int program);
	static void UseProgram(unsigned int program);
	static void GetProgramiv(unsigned int program, unsigned int pname, int *param);
	static void GetProgramInfoLog(unsigned int program, int bufsize, int *length, char *infoLog);

	static void GenVertexArrays(int n, unsigned int *arrays);
	static void BindVertexArray(unsigned int array);
	static void DeleteVertexArrays(int n, unsigned int *arrays);

	static void GenBuffers(int n, unsigned int *buffers);
	static void BindBuffer(unsigned int target, unsigned int buffer);
	static void DeleteBuffers(int n, unsigned int *buffers);

	static void BufferData(unsigned int target, ptrdiff_t size, const void *data, unsigned int usage);
	static void VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void *pointer);
	static void EnableVertexAttribArray(unsigned int index);

	static void DrawArrays(unsigned int mode, int first, int count);
	static void DrawElements(unsigned int mode, int count, unsigned int type, const void *indices);
};
