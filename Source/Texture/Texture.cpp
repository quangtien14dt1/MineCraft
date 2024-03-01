#include "Texture.h"


void Texture::LoadFromFile(const std::string& name) {
	sf::Image i;
	if (!i.loadFromFile("Resource/textures/" + name + ".png")) {
		throw std::runtime_error("Unable to load texture: " + name);
	}
	/*
	* image buffer will read from top-left and become bottom-right
	* that why we need to flipverically before passing it to OpenGl
	*/
	i.flipVertically();

	LoadFromImage(i);

}

void Texture::LoadFromImage(const sf::Image& i) {
	glGenTextures(1,&_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

	glBindTexture(GL_TEXTURE_2D, 0); /* unbind OpenGL for safe accidentally */
}