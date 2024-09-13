#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "basemodel.h"
#include "utils/patterns/singleton.h"

class ChunkModel;
class Chunk;
class Block;
class CubeTexture;

class ChunkModelBuilder : public SingleTon
{
public:
	static ChunkModelBuilder* GetInstance();

	ChunkModelBuilder();

	ChunkModelBuilder* operator()();

	void BuildMesh(ChunkModel&, Chunk&, CubeTexture&);

	bool CheckingShouldAddFace(
		const sf::Vector3i& nextDoorBlock
		//const Block* block
	);

	void AddFaceToMesh(
		const std::vector<GLfloat>& blockFace,
		const sf::Vector2i& texcoord,
		const sf::Vector3i&,
		const sf::Vector3i& blockFacing);

private:
	static ChunkModelBuilder* _pChunkModelBuilder;

	ChunkModel* _chunkMesh{ NULL };
	CubeTexture* _cubeTexture{NULL};
	Chunk*		_chunk{NULL};
};

