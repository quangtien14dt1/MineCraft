#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader();

	BasicShader(const std::string& vert, const std::string& frag);

	void LoadProjectionMatrix(const glm::mat4& mat);

	void LoadModelMatrix(const glm::mat4& mat);

	void LoadViewMatrix(const glm::mat4& mat);

	void LoadImageShader(const GLuint value);

protected:
	/* most important get location for manipulate shader program */
	virtual void GetUniforms() override;

private:

	GLuint _locationProjectionMatrix;

	GLuint _locationViewMatrix;

	GLuint _locationModelMatrix;

	GLuint _texure;
};

