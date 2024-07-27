#pragma once

#include "../glm.h"
#include <array>
#include <vector>

class BasicShader;
class Camera;
class BlockDatabase;
struct Block;

class CubeRenderer
{
public:
	CubeRenderer();

	void create(const Block& );

	void add(const glm::vec3& postion);

	void render( Camera* camera, bool );

	//std::vector<GLfloat> GetTextureCoords(Block* b);

	~CubeRenderer();

private:


	BlockDatabase* _blocksDatabase;

	BasicShader* _cubeShader;

};

