#pragma once


#include "glm.h"
#include "ModelLoading.h"

#include <vector>


/*
* Mesh only handle 2/3 of matrixs 
* View * Projection matrixs 
*/

class Camera;

class BasicShader;

class Texture;

class Mesh {

public:
	Mesh( std::vector <Vertex>, std::vector <GLuint>, std::vector <Texture> );

	~Mesh();

	void DrawMesh(BasicShader& s,Camera& c );

	void AsString();

	/* temple function return default model matrix */
	glm::mat4 DefaultModel();

private:
	std::vector<Vertex> _vertices;

	std::vector<GLuint> _indices;

	std::vector<Texture> _textures;

private:
	VAO _vao;

	glm::mat4 _cameraMatrix;
};