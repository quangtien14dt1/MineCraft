#pragma once

#include "ModelLoading.h"
#include "../Texture/Texture.h"
#include "../glm.h"
#include "Mesh.h"
#include "Model.h"
#include "ModelLoading.h"

class CubeModel : public Model {

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

	glm::mat4 makeModelMatrix(glm::vec3 location);

private:

	VAO m_vao;
	GLuint m_vboCount = 0; // buffer location
	GLuint m_indicesCount = 0;
	std::vector<VBO> m_buffers;
	std::vector<EBO> m_indices;
	Mesh m_mesh;

	// self state model
	glm::vec3 m_position;
	glm::vec3 m_rotation{ 0, 0, 0 };

};
