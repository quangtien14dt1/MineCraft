#include "Model.h"
#include <algorithm>

static const int ZERO = 0;

static const int POSITION = 0;

static const int TEXTURE_COORD = 1;

static const int POSITION_BUFFER_SIZE = 3;

static const int TEXTURE_BUFFER_SIZE = 2;

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
	addVBO(POSITION_BUFFER_SIZE, mesh.vertexPositions);
	addVBO(TEXTURE_BUFFER_SIZE, mesh.textureCoords);
	addEBO(mesh.indices);
	
};

void Model::deleteData() { 

	std::for_each(m_buffers.begin(), m_buffers.end(), [](VBO v) {
		v.delete_();
	});

	m_buffers.clear();

	m_vboCount		= ZERO;
	m_indicesCount  = ZERO;

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

void 
Model::updateVBOTextureCoord(
	std::vector<GLfloat>& newTexCoord
) {
	m_vao.bind();
	m_buffers[TEXTURE_COORD].bind();

	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		newTexCoord.size() * sizeof(GLfloat),
		newTexCoord.data()
	);

	m_buffers[TEXTURE_COORD].unbind();
	m_vao.unbind();
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



