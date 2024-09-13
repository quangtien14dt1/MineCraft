#include "texture/CubeTexture.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void CubeTexture::SetupCubeImage(std::string file) {
	sf::Image i;
	if (!i.loadFromFile("res/textures/" + file + ".png"))
	{
		throw std::runtime_error("Unable to open image: " + file);
	}

	LoadFromImage(i);

	m_imageSize				= 256;
	m_individualTextureSize = 16;
};

std::vector<GLfloat>  
CubeTexture::GetTexture(const sf::Vector2i& coords) {

	GLfloat TEX_PER_ROW	= (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
	GLfloat INDV_TEX_SIZE  = 1.0f / TEX_PER_ROW;
	GLfloat PIXEL_SIZE		= 1.0f / (float)m_imageSize;

	GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;
	GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;

	GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;
	GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;

	//std::cout << xMax << yMax << xMin << yMin << std::endl;

	return {
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
		
};