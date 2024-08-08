#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "model.h"
#include "utils/patterns/singleton.h"

class ChunkMesh;
class Chunk;
class Block;

class ChunkMeshBuilder : public SingleTon
{
public:
	static ChunkMeshBuilder* GetInstance();

	ChunkMeshBuilder();

	ChunkMeshBuilder* operator()();
	
	void BuildMesh( ChunkMesh&, Chunk&);

	bool CheckingShouldAddFace(
		 const sf::Vector3i& nextDoorBlock,
		 const Block* block
	);

	void AddFaceToMesh(
		 const std::vector<GLfloat>& blockFace,
		 const sf::Vector2f& textureCoords,
		 const Block* blockPosition,
		 const sf::Vector3i& blockFacing);
	
private:
	static ChunkMeshBuilder* _pChunkMeshBuilder;

	ChunkMesh*	_chunkMesh{nullptr};

	Chunk*		_chunk{nullptr};
	//const  GLuint _index;
};

