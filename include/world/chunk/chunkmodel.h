#pragma once

#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "basemodel.h"
#include "mesh.h"

class Block;

class ChunkModel : public BaseModel
{
public:
	ChunkModel();

	~ChunkModel();

	void AddFace(
		 const std::vector<GLfloat>& ,
		 const std::vector<GLfloat>& ,
		 const sf::Vector3i& ,
		 const sf::Vector3i& 
	);

	void AddMeshToModel();

	BaseModel* GetModel();

private:

	Mesh _mesh;
	GLuint _indexIndice;
};