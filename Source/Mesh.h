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
class Model;

class Mesh {

public:
	Mesh() {}

	Mesh( std::vector <Vertex> ,std::vector <GLuint>, Model*  );
	~Mesh();

	void DrawMesh(BasicShader& s,Camera& c);

	//void TranslateModel(glm::vec3);
	//void RoateModel(glm::vec3, float);
	void AsString();

	/* temple function return default model matrix */
	glm::mat4 DefaultModel();

	/* convert to uisng texture by cube map */
private:
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
	VAO _vao;
	glm::mat4 _cameraMatrix;
	Model* _model;

};