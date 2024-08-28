#pragma once

#include <glad/glad.h>
#include "glm.h"
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
};

class VBO {

public:

	void bind() { glBindBuffer(GL_ARRAY_BUFFER, _vboId); };

	void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };

	void delete_() const { glDeleteBuffers(1, &_vboId); };

	GLuint getVboId() { return _vboId; }

	VBO(const std::vector<GLfloat>& d ) {

		glGenBuffers(1,&_vboId);

		glBindBuffer(GL_ARRAY_BUFFER, _vboId);

		glBufferData(	GL_ARRAY_BUFFER, 
						d.size() * sizeof(GLfloat), 
						d.data(), 
						GL_STATIC_DRAW);
	};

	GLuint _vboId{0};
};

class VAO {
public:

	VAO() {
		//glGenVertexArrays(1, &_vaoId);
	};

	void linkAttrib(VBO& vbo, // buffer
					GLuint& m_vboCount,
					GLuint dimension,
					GLenum type,
					void* offset)
	{
		vbo.bind();

		glVertexAttribPointer(  
			m_vboCount, 
			dimension,
			type,
			GL_FALSE,
			0,
			offset);

		glEnableVertexAttribArray(m_vboCount++);

		vbo.unbind();
	};

	GLuint getVaoId() const { return _vaoId; }

	void bind() { glBindVertexArray(_vaoId); };

	void generateVao() { 
		glGenVertexArrays(1, &_vaoId); 
	};

	void unbind() { glBindVertexArray(0); };

	void deleteVao() const { glDeleteVertexArrays(1, &_vaoId); };

	GLuint _vaoId{0};
};

class EBO {
public:
	EBO( std::vector<GLuint> i) { 

		glGenBuffers(1, &_eboId);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(GLuint), i.data(), GL_STATIC_DRAW);
	};

	void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId); };

	void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

	void delete_() const { glDeleteBuffers(1, &_eboId); };

	GLuint _eboId{0};
};
