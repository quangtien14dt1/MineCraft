#pragma once

#include "../ModelLoading.h"
#include "../Texture/Texture.h"
#include "../Mesh.h"
#include "Model.h"


class Cube : public Model {
public:
	void InitModel();
	void SetModelPosition(glm::vec3);
	void SetDefaultPosition(); // default position 0
	void DrawModel(BasicShader& , Camera& );

private:
	Mesh _mesh;
	std::vector <Vertex> _verts;
	std::vector <GLuint> _inds;
	std::vector <Texture> _tex;
};
