#pragma once
#include "../NonCopyable.h"
#include "ShaderLoader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

class Shader
{
public:

	Shader() : _id(0) {}

	Shader(	const std::string& vert, 
			const std::string& frag) : _id(ShaderUtil::LoadShader(vert, frag)) {};
	virtual ~Shader() { glDeleteProgram(_id); };

	/* value buffer manipulate */
	void LoadInt(GLuint loca, int value) { glUniform1i(loca, value); };
	void LoadFloat(GLuint loca, float value) { glUniform1f(loca, value); };
	
	/* vector manipulate */
	void LoadVector2(GLuint loca, const glm::vec2& vect) { glUniform2f(loca, vect.x, vect.y); };
	void LoadVector3(GLuint loca, const glm::vec3& vect) { glUniform3f(loca, vect.x, vect.y, vect.z); };
	void LoadVector4(GLuint loca, const glm::vec4& vect) { glUniform4f(loca, vect.x, vect.y, vect.z, vect.w); };

	/* matrix 4 view projection */
	void LoadMatrix4(GLuint loca, const glm::mat4& mat) { 
		glUniformMatrix4fv(loca, 1, GL_FALSE, glm::value_ptr(mat)); 
	};
	void Activate() const { glUseProgram(_id); }
	GLuint GetShaderId() { return _id; }

protected:
	virtual void GetUniforms() = 0;
	GLuint _id;
};

