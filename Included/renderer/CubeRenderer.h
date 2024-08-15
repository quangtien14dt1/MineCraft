#pragma once

#include "../glm.h"
#include <array>
#include <vector>

class BasicShader;
class Camera;
class BlockDatabase;
class Block;
class Model;

class CubeRenderer
{
public:
	CubeRenderer();

	void create(const Block& );

	void add(const glm::vec3& postion);

	void render( Camera* camera, bool );

	void RenderBySection( const std::vector<Block*>& );

	//std::vector<GLfloat> GetTextureCoords(Block* b);

	~CubeRenderer();

private:


	BlockDatabase* _blocksDatabase;

	BasicShader* _cubeShader;

	Model* _model;

	const glm::vec3 _default{ 0,0,0 };

};

