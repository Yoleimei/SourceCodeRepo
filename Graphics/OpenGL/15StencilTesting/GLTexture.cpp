#include "GLTexture.h"

GLTexture::GLTexture(std::string strFilePath, aiTextureType type, GLint wrapSParam, GLint wrapTParam, GLint MinFilter, GLint MagFilter)
{
	glGenTextures(1, &m_uiTexture);

	m_eType = type;
	m_strPath = strFilePath;
	m_iWrapSParam = wrapSParam;
	m_iWrapTParam = wrapTParam;
	m_iMinFilter = MinFilter;
	m_iMagFilter = MagFilter;
}

GLTexture::~GLTexture()
{

}

bool GLTexture::Init()
{
	LOG_DBG("[%s:%d]\n", __FUNCTION__, __LINE__);

	BindTexture();

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_iWrapSParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_iWrapTParam);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_iMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_iMagFilter);

	// load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(m_strPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (nullptr == image) {
		LOG_ERR("[%s:%d] Load texture image failed\n", __FUNCTION__, __LINE__);
		UnbindTexture();
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	UnbindTexture();

	return true;
}

GLuint GLTexture::GetTextureId()
{
	return m_uiTexture;
}

aiTextureType GLTexture::GetTextureType()
{
	return m_eType;
}

std::string GLTexture::GetTexturePath()
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