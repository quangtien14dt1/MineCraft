#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "world/worldcontant.h"
#include "world/block/blockcontribute.h"

/* 
  make play ground ( x, y)  and z is ladder to sky
  so this is how we create world :
  we using fastsimplenoice library to create 2d map 256x256 point
  each chunk ocupile 16x16 point , and deep will be 256 
*/

class ChunkModel;
class BlockDatabase;
class BlockFactory; 
class Block;



class Chunk {
public:

	Chunk( sf::Vector3i );

	~Chunk();

	void SetBlockType(int x, int y, int z, BlockType type);

	bool isLocationValidate(int x, int y, int z);

	/* chunk maintanance */
	void BlocksConfiguration();

	sf::Vector3i GetChunkLocation() const ;

	void SetChunkLocation(sf::Vector3i);

	Block* GetBlockByLocation(int x, int y, int z);

	void resetBlockChunk();

	void SetChunkHeightMap(std::array<int, CHUNK_AREA > );

	int GetHeight(int ,int);

	ChunkModel* GetChunkModel();

private:

	ChunkModel* _chunkModel;

	static int GenerateRandomId();

	sf::Vector3i _chunkId;

	Block* _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

	std::array<int, CHUNK_AREA > _heighMap;

};

class  ChunkCache {};