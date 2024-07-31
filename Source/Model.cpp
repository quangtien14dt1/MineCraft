#include "Model.h"
#include <algorithm>

static const int ZERO = 0;

static const int BASE_X_AXIS = 1;

static const int BASE_Y_AXIS = 1;

static const int BASE_Z_AXIS = 1;

static const int POSITION = 0;

static const int TEXTURE_COORD = 1;

static const int POSITION_BUFFER_SIZE = 3;

static const int TEXTURE_BUFFER_SIZE = 2;

/* default Model init */
void Model::InitModel() {}

void Model::AddData(const Mesh& mesh) {

	if (m_vao.getVaoId() != 0) {
		// delete vao and clean previous round 
		m_vao.deleteVao();
		DeleteData();
	}

	m_indicesCount = (GLuint)mesh.indices.size();

	// regenerate and bind data
	m_vao.generateVao();
	m_vao.bind();
	AddVBO(POSITION_BUFFER_SIZE, mesh.vertexPositions);
	AddVBO(TEXTURE_BUFFER_SIZE, mesh.textureCoords);
	AddEBO(mesh.indices);
	
};

void Model::DeleteData() {

	std::for_each(m_buffers.begin(), m_buffers.end(), [](VBO v) {
		v.delete_();
	});

	m_buffers.clear();

	m_vboCount		= ZERO;
	m_indicesCount  = ZERO;

};

void Model::AddVBO(
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
Model::UpdateVBOTextureCoord(
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

void Model::AddEBO(const std::vector<GLuint>& indices) {

	EBO ebo(indices);
	ebo.bind();

};

VAO Model::GetVao() { return m_vao; };


glm::mat4 Model::ModelMatrix(
	const glm::vec3& location,
	const glm::vec3& rotation)
{
	glm::mat4 mat = glm::mat4(1.0f);

	auto rotateMatrix = [&mat](const glm::vec3& rotation) {
		glm::vec3 axes[] = {
			{BASE_X_AXIS, 0, 0},
			{0, BASE_Y_AXIS, 0},
			{0, 0, BASE_Z_AXIS}
		};

		for (int i = 0; i < 3; ++i) {
			mat = glm::rotate(mat, glm::radians(rotation[i]), axes[i]);
		}
	};

	rotateMatrix(rotation);

	mat = glm::translate(mat, location);

	return mat;

};


GLuint Model::GetIndiceCount() const { return m_indicesCount; };



