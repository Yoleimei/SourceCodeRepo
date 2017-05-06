#include "GLTexture.h"

GLTexture::GLTexture()
{
	// Load and create a texture
	glGenTextures(1, &m_uiTexture);
}

GLTexture::~GLTexture()
{

}

void GLTexture::GenerateMipMap(const GLchar * pcFilePath, GLint wrapParam)
{
	BindTexture();
	
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);
	
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(pcFilePath, &width, &height, 0, SOIL_LOAD_RGB);
	// LOG_DBG("texture image width:%d, height:%d\n", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	
	UnbindTexture();
}

void GLTexture::ActiveTexture(GLenum texture)
{
	glActiveTexture(texture);
}

void GLTexture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_uiTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
}

void GLTexture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}