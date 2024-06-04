#include "CubeTexture.h"



CubeTexture::CubeTexture(const std::string& file) {
	sf::Image i;
	if (!i.loadFromFile("Res/Textures/" + file + ".png"))
	{
		throw std::runtime_error("Unable to open image: " + file);
	}

	LoadFromImage(i);

	m_imageSize				= 256;
	m_individualTextureSize = 16;
};

std::vector<GLfloat>  
CubeTexture::GetTexture(const sf::Vector2f& coords) {

	static const GLfloat TEX_PER_ROW	= (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
	static const GLfloat INDV_TEX_SIZE  = 1.0f / TEX_PER_ROW;
	static const GLfloat PIXEL_SIZE		= 1.0f / (float)m_imageSize;

	GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
	GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

	GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
	GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

	return {
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
		
};