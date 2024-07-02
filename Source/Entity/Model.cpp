#include "Model.h"
#include <algorithm>

/* default Model init */
void Model::InitModel() {}

void Model::addData(const Mesh& mesh) {

	if (m_vao.getVaoId() != 0) {
		// delete vao and clean previous round 
		m_vao.deleteVao();
		deleteData();
	}

	m_indicesCount = mesh.indices.size();

	// regenerate and bind data
	m_vao.generateVao();
	m_vao.bind();
	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
	
};

void Model::deleteData() { 

	std::for_each(m_buffers.begin(), m_buffers.end(), [](VBO v) {
		v.delete_();
	});

	m_buffers.clear();

	m_vboCount		= 0;
	m_indicesCount = 0;

};

void Model::addVBO(
		GLuint dimension, 
		const std::vector<GLfloat>& data ) 
{
	VBO vbo(data);
	vbo.bind();
	m_vao.linkAttrib( vbo, 
					  m_vboCount, 
					  dimension, 
					  GL_FLOAT, 
					  (void*)0 );

	m_buffers.push_back(vbo);

};

void Model::addEBO(const std::vector<GLuint>& indices) {

	EBO ebo(indices);
	ebo.bind();

};

VAO Model::getVao() { return m_vao; };


glm::mat4 Model::modelMatrix(glm::vec3 location, glm::vec3 rotation) {

	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, location);

	return matrix;

};


GLuint Model::getIndiceCount() const { return m_indicesCount; };



