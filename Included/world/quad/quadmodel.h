#pragma once
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "basemodel.h"

class Block;
class Mesh;
class QuadTexture;

class  QuadModel : public BaseModel
{
public:
	QuadModel();

	void CreateQuadMesh(const Block*);

	void AddMeshToModel();

	BaseModel* GetModel();

	QuadTexture* GetTexture();

private:
	std::vector< sf::Vector3i > _location;
	Mesh	_mesh;
	QuadTexture* _quadTexture;
};