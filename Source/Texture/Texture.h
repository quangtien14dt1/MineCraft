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
	Texture(const std::string& name) { LoadFromFile(name); };

	void LoadFromFile(const std::string&);

	void LoadFromImage(const sf::Image&);

	void BindTexture() const { glBindTexture(GL_TEXTURE_2D, _id); };

	void UnbindTexture() const { glBindTexture(GL_TEXTURE_2D, 0); };

	void DeleteTexture() const { glDeleteTextures(1, &_id); };

	void TextureUnit(BasicShader& s, const char* l, GLuint i) {

		GLuint location = glGetUniformLocation( s.GetShaderId(), l );

		s.Activate();

		s.LoadInt(location, 0);
	}

	GLuint GetTextureId() const { return _id; }

private:
	GLuint _id;
	std::string m_type;
};

