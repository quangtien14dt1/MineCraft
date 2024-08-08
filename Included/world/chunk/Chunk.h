#pragma once

#include <SFML/Graphics.hpp>
#include "world/worldcontant.h"
#include "world/block/blockcontribute.h"
#include <vector>

/* 
  make play ground ( x, y)  and z is ladder to sky
  so this is how we create world :
  we using fastsimplenoice library to create 2d map 256x256 point
  each chunk ocupile 16x16 point , and deep will be 256 
*/

class ChunkMesh;
class BlockDatabase;

class Chunk {
public:
	Chunk( sf::Vector2i );
	~Chunk();

	bool SetBlockType(int x, int y, int z, BlockType);

	bool OutOfBoundValidate(int x, int y, int z);

	/* chunk maintanance */
	void CreateChunk();
	const sf::Vector2i GetChunkLocation() const ;

	/* generator  */
	void ProcessPosition(const sf::Vector3i& );
	Block* GetBlockByLocation(int x, int y, int z);

private:

	static int GenerateRandomId();
	sf::Vector2i _chunkId;
	//std::array<Block*, CHUNK_VOLUME > _blocks;

	/* store 3D map chunk' block y, x, z */
	Block* _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	ChunkMesh* _mesh;

	
};

class  ChunkCache {};