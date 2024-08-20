#include "basemodel.h"
#include <algorithm>



/* default Model init */
void BaseModel::InitModel() {}

void BaseModel::AddData(const Mesh& mesh) {

	if (m_vao.getVaoId() != 0) {
		// delete vao and clean previous round 
		m_vao.deleteVao();
		DeleteData();
	}

	m_indicesCount = (GLuint)mesh.indices.size();

	// regenerate and bind data
	m_vao.generateVao();
	m_vao.bind();
	AddVBO(3, mesh.vertexPositions);
	AddVBO(2, mesh.textureCoords);
	AddEBO(mesh.indices);
	
};

void BaseModel::DeleteData() {

	std::for_each(m_buffers.begin(), m_buffers.end(), [](VBO v) {
		v.delete_();
	});

	m_buffers.clear();

	m_vboCount		= 0;
	m_indicesCount  = 0;

};

void BaseModel::AddVBO(
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
BaseModel::UpdateVBOTextureCoord(
	std::vector<GLfloat>& newTexCoord
) {
	m_vao.bind();
	m_buffers[1].bind();

	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		newTexCoord.size() * sizeof(GLfloat),
		newTexCoord.data()
	);

	m_buffers[1].unbind();
	m_vao.unbind();
};

void BaseModel::AddEBO(const std::vector<GLuint>& indices) {

	EBO ebo(indices);
	ebo.bind();

};

VAO BaseModel::GetVao() { return m_vao; };

GLuint BaseModel::GetIndiceCount() const { return m_indicesCount; };

sf::Vector3f BaseModel::GetModelLocation() {
	return _defaultLocation;
};

void BaseModel::SetModelLocation(sf::Vector3f l) {
	_defaultLocation = l;
};

BaseModel::~BaseModel() {

};


