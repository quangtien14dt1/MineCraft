#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "world/worldcontant.h"

/* 
  make play ground ( x, y)  and z is ladder to sky
  so this is how we create world :
  we using fastsimplenoice library to create 2d map 256x256 point
  each chunk ocupile 16x16 point , and deep will be 256 
*/

class ChunkModel;
class BlockDatabase;
class Block;

class Chunk {
public:
	Chunk( sf::Vector3i );
	~Chunk();

	void SetBlockType(int x, int y, int z, BlockType);

	bool OutOfBoundValidate(int x, int y, int z);

	/* chunk maintanance */
	void CreateChunk();

	sf::Vector3i GetChunkLocation() const ;

	void SetChunkLocation(sf::Vector3i);


	Block* GetBlockByLocation(int x, int y, int z);

private:

	static int GenerateRandomId();
	sf::Vector3i _chunkId;

	/* store 3D map chunk' block y, x, z */
	Block* _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

};

class  ChunkCache {};