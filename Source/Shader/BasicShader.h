#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader(const std::string& vert, const std::string& frag)
		:Shader(vert, frag)
	{
		GetUniforms();
	};

	void LoadProjectionMatrix(const glm::mat4& mat) { LoadMatrix4(_locationProjectionMatrix, mat );};

	void LoadModelMatrix(const glm::mat4& mat) { LoadMatrix4(_locationModelMatrix, mat);};

	void LoadViewMatrix(const glm::mat4& mat) { LoadMatrix4(_locationViewMatrix, mat); }

	void LoadImageShader( const GLuint value) { LoadInt(_texure, value); }
protected:
	/* most important get location for manipulate shader program */
	virtual void GetUniforms() override {
		Activate();
		_locationProjectionMatrix = glGetUniformLocation(_id, "projection");
		_locationViewMatrix = glGetUniformLocation(_id, "view");
		_locationModelMatrix = glGetUniformLocation(_id, "model");
		_texure = glGetUniformLocation(_id, "texture1");
	};
private:
	GLuint _locationProjectionMatrix;
	GLuint _locationViewMatrix;
	GLuint _locationModelMatrix;
	GLuint _texure;
};

