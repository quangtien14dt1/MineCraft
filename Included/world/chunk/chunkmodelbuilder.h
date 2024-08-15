#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "basemodel.h"
#include "utils/patterns/singleton.h"

class ChunkModel;
class Chunk;
class Block;

class ChunkModelBuilder : public SingleTon
{
public:
	static ChunkModelBuilder* GetInstance();

	ChunkModelBuilder();

	ChunkModelBuilder* operator()();
	
	void BuildMesh( ChunkModel&, Chunk&);

	bool CheckingShouldAddFace(
		 const sf::Vector3i& nextDoorBlock,
		 const Block* block
	);

	void AddFaceToMesh(
		 const std::vector<GLfloat>& blockFace,
		 const Block* blockPosition,
		 const sf::Vector3i&,
		 const sf::Vector3i& blockFacing );
	
private:
	static ChunkModelBuilder* _pChunkModelBuilder;

	ChunkModel*	_chunkMesh{NULL};

	Chunk*		_chunk{NULL};
};

