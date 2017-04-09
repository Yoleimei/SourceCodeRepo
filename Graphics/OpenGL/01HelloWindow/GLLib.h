#pragma once

static class GLLib
{
public:
	static void Viewport(int x, int y, int width, int  height);
	static void ClearColor(float red, float green, float blue, float alpha);
	static void Clear(unsigned int mask);
};
