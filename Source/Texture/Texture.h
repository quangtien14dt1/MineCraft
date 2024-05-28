#pragma once

#include <string>
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "../NonCopyable.h"
#include "../shader/BasicShader.h"

class Texture 
{
public:
	Texture() = default;
	Texture(const std::string& name); 
	~Texture();

	/* handle load file */
	void LoadFromFile(const std::string&);
	void LoadFromImage(const sf::Image&);

	/* shader binding */
	void BindTexture() const;
	void UnbindTexture() const ;
	void DeleteTexture() const ;
	void TextureUnit(BasicShader& s, const char* l, GLuint i);

	GLuint GetTextureId() const;

private:
	GLuint _id;
	std::string m_type;
};

