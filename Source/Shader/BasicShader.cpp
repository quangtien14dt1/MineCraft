#include "BasicShader.h"


BasicShader::BasicShader()
	: _locationProjectionMatrix(0)
	, _locationViewMatrix(0)
	, _locationModelMatrix(0)

{ /* do nothing */ }

BasicShader::BasicShader(const std::string& vert, const std::string& frag)
	:Shader(vert, frag)
{
	GetUniforms();
};

void BasicShader::LoadProjectionMatrix(const glm::mat4& mat) { LoadMatrix4(_locationProjectionMatrix, mat); };

void BasicShader::LoadModelMatrix(const glm::mat4& mat) { LoadMatrix4(_locationModelMatrix, mat); };

void BasicShader::LoadViewMatrix(const glm::mat4& mat) { LoadMatrix4(_locationViewMatrix, mat); }

void BasicShader::GetUniforms() {

	Activate();

	_locationProjectionMatrix = glGetUniformLocation(_id, "projection");

	_locationViewMatrix = glGetUniformLocation(_id, "view");

	_locationModelMatrix = glGetUniformLocation(_id, "model");

};
