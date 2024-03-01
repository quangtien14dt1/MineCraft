#pragma once

#include <vector>
#include "glm.h"
#include "ModelLoading.h"
#include "shader/BasicShader.h"
#include "texture/Texture.h"
#include "entity/Camera.h"


/*
* Mesh only handle 2/3 of matrixs 
* View * Projection matrixs 
*/
class Mesh {

public:
	Mesh(	std::vector <Vertex>, 
			std::vector <GLuint>
			//std::vector <Texture>
	);

	~Mesh();
	void Draw(BasicShader& , Camera&);
	void SetupMesh();
	void DrawMeshIndices();
	void AsString();

	/* temple function return default model matrix */
	glm::mat4 DefaultModel();
private:
	std::vector<Vertex> m_vertices; // vbo , ebo 
	std::vector<GLuint> m_indices;
	std::vector<Texture> m_textures;

private:

	VAO m_vao;
	glm::mat4 m_cameraMatrix;
};