#include "GLTexture.h"

GLTexture::GLTexture(aiString strFilePath, aiTextureType type, GLint wrapSParam, GLint wrapTParam, GLint MinFilter, GLint MagFilter)
{
	// Load and create a texture
	glGenTextures(1, &m_uiTexture);
	m_eType = type;
	m_strPath = strFilePath;

	BindTexture();

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapSParam);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapTParam);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);

	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(strFilePath.C_Str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (nullptr == image) {
		LOG_ERR("load texture image error.\n");
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	UnbindTexture();
}

GLTexture::~GLTexture()
{

}

GLuint GLTexture::GetTextureId()
{
	return m_uiTexture;
}

aiTextureType GLTexture::GetTextureType()
{
	return m_eType;
}

aiString GLTexture::GetTexturePath()
{
	return m_strPath;
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