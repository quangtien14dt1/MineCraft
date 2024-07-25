#pragma once

#include "ModelLoading.h"
#include "../glm.h"
#include "Mesh.h"
#include "ModelLoading.h"

class Model {

public:

	/* abstrct functions */
	void InitModel();
	void addData(const Mesh& mesh);
	void deleteData();
	void addVBO(GLuint dimensions, const std::vector<GLfloat>& data);
	void updateVBOTextureCoord(std::vector<GLfloat>& );
	void addEBO(const std::vector<GLuint>& indices);
	VAO getVao() ;

	/* manipulate with model itself */
	glm::mat4 modelMatrix(glm::vec3, glm::vec3);
	GLuint getIndiceCount() const;

private:
	
	/* 1 Model has 1 vao and add on many mesh */
	VAO		m_vao;
	Mesh	m_mesh;
	GLuint	m_vboCount = 0; // buffer location
	GLuint	m_indicesCount = 0;
	std::vector<VBO> m_buffers;

};
