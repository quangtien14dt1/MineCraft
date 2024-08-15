#pragma once
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include "glm.h"
#include "basemodel.h"

class Block;
class Mesh;
class CubeTexture;

class BlockModel : public BaseModel
{
public:
	BlockModel();

	void CreateBlockMesh(const Block* );

	void AddMeshToModel();

	BaseModel* GetModel();

private:

	Mesh _mesh;
	GLuint _indexIndice;
	CubeTexture* _cubeTexture;
};