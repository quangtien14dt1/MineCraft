#pragma once

#include "ModelLoading.h"
#include "../glm.h"
#include "Mesh.h"
#include "ModelLoading.h"

class Model {

public:

	/* abstrct functions */
	void InitModel();
	void AddData(const Mesh& mesh);
	void DeleteData();
	void AddVBO(GLuint dimensions, const std::vector<GLfloat>& data);
	void UpdateVBOTextureCoord(std::vector<GLfloat>& );
	void AddEBO(const std::vector<GLuint>& indices);
	VAO	 GetVao() ;

	/* manipulate with model itself */
	static glm::mat4 ModelMatrix( const glm::vec3&,const glm::vec3&);
	GLuint GetIndiceCount() const;

private:
	
	/* 1 Model has 1 vao and add on many mesh */
	VAO		m_vao;
	Mesh	m_mesh;
	GLuint	m_vboCount = 0; // buffer location
	GLuint	m_indicesCount = 0;
	std::vector<VBO> m_buffers;

};
