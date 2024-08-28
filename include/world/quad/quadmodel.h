#pragma once
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "basemodel.h"
#include "mesh.h"

class Block;
class QuadTexture;

/*
basemodel containt data and it default 
location, renderer will containt list of model
location
*/
class  QuadModel : public BaseModel
{
public:
	QuadModel(QuadTexture*);

	void CreateQuadMesh();

	void AddMeshToModel();

	BaseModel* GetModel();

	QuadTexture* GetTexture();

private:
	
	Mesh	_mesh;
	QuadTexture* _quadTexture;
};