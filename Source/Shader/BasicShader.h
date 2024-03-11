#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader();

	BasicShader(const std::string&, const std::string& );


	/* Model View Projection */
	void LoadProjectionMatrix(const glm::mat4& );

	void LoadModelMatrix(const glm::mat4& );

	void LoadViewMatrix(const glm::mat4& );

protected:
	/* most important get location for manipulate shader program */
	virtual void GetUniforms() override;

private:

	GLuint _locationProjectionMatrix;

	GLuint _locationViewMatrix;

	GLuint _locationModelMatrix;
};

