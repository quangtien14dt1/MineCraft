#pragma once

#include <string>
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "../shader/BasicShader.h"

class QuadTexture
{
public:
	QuadTexture() = default;
	QuadTexture(const std::string& name);
	~QuadTexture();

	/* handle load file */
	void LoadFromFile(const std::string&);
	void LoadFromImage(const sf::Image&);

	/* shader binding */
	void bind() const;
	void unbind() const ;
	void DeleteTexture() const ;
	void TextureUnit(BasicShader& s, const char* l, GLuint i);

	GLuint GetTextureId() const;

private:
	GLuint _id;
	std::string m_type;
};

