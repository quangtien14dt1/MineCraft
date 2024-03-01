#pragma once

#include <glad/glad.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class VBO {
public:
	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, _vboId); };
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
	void Delete() const { glDeleteBuffers(1, &_vboId); };

	VBO(std::vector<Vertex>& v ) {
		glGenBuffers(1,&_vboId);
		glBindBuffer(GL_ARRAY_BUFFER, _vboId);
		glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(v), v.data(), GL_STATIC_DRAW);
	};
	GLuint _vboId;
};

class VAO {
public:

	VAO() { glGenVertexArrays(1, &_vaoId); };
	void LinkAttrib(VBO& vbo, 
					GLuint layout, 
					GLuint num, 
					GLenum type, 
					GLsizei stride, 
					void* offset) 
	{
		vbo.Bind();
		glVertexAttribPointer(layout, num, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();
	};
	void Bind() { glBindVertexArray(_vaoId); };
	void Unbind() { glBindVertexArray(0); };
	void Delete() const { glDeleteVertexArrays(1, &_vaoId); };
	GLuint _vaoId;
};

class EBO {
public:
	EBO( std::vector<GLuint> & i) { 
		glGenBuffers(1, &_eboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(GLuint), i.data(), GL_STATIC_DRAW);
	};
	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId); };
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
	void Delete() const { glDeleteBuffers(1, &_eboId); };
	GLuint _eboId{0};
};
