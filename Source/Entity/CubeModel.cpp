#include "CubeModel.h"
#include "ModelLoading.h"
#include "../glm.h"

/* default CubeModel init */
void CubeModel::InitModel() {


}

void CubeModel::addData(const Mesh& mesh) {

	if (m_vao.getVaoId() != 0) deleteData();

	m_indicesCount = mesh.indices.size();

	m_vao.bind();

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
	
};

void CubeModel::deleteData() { 
	m_vao.delete_();
	std::for_each(m_buffers.begin(), m_buffers.end(), [](VBO v) {
		v.delete_();
	});

	m_buffers.clear();

};

void CubeModel::addVBO(int size, const std::vector<GLfloat>& data) {

	VBO vbo(data);

	m_vao.linkAttrib(vbo, m_vboCount, size, GL_FLOAT, (void*)0);

	m_buffers.push_back(vbo);

};

void CubeModel::bindVAO()  { m_vao.bind(); };

void CubeModel::TranslateModel() {  };

void CubeModel::RotateModel(float) {  };

glm::mat4 CubeModel::makeModelMatrix(glm::vec3 location) {
	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(m_rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(m_rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(m_rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, location);

	return matrix;
};

GLuint CubeModel::getIndiceCount() const { return m_indicesCount; };

void CubeModel::addEBO(const std::vector<GLuint>& indices) {

	EBO ebo(indices);

	ebo.bind();

	m_indices.push_back(ebo);

	ebo.unbind();
};

