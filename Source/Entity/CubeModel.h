#pragma once

#include "ModelLoading.h"
#include "../Texture/Texture.h"
#include "../glm.h"
#include "Mesh.h"


class CubeModel {

public:

	/* abstrct functions */
	void InitModel();

	void addData(const Mesh& mesh);

	void deleteData();

	void addVBO(int dimensions, const std::vector<GLfloat>& data);

	void bindVAO() ;

	void SetDefaultLocation(); 

	/* manipulate with model itself */
	void TranslateModel();

	void RotateModel(float);

	void addEBO(const std::vector<GLuint>& indices);

	GLuint getIndiceCount() const;

private:

	VAO m_vao;
	GLuint m_vboCount = 0;
	GLuint m_indicesCount = 0;
	std::vector<VBO> m_buffers;
	std::vector<EBO> m_indices;
	Mesh m_mesh;

};
