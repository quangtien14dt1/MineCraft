#include "world/chunk/Chunk.h"
#include "world/block/blockdatabase.h"
#include "world/block/blockfactory.h"
#include <random>
#include <iostream>

Chunk::Chunk(sf::Vector3i location)
    : _chunkId(location)
{ 
    resetBlockChunk();
}

Chunk::~Chunk() {};

/*
* function setup all chunk'block
* my height map and type 
* 
*/
void Chunk::BlocksConfiguration() {
    int  h = 10;
    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int y = 0; y < CHUNK_SIZE; ++y)

        for (int z = 0; z < CHUNK_SIZE; ++z) {

            SetBlockType(x, y, z, BlockType::Grass);

            

        }

};

/* 
* function reset all block of chunk
* we point to NULL
*/
void Chunk::resetBlockChunk() {

    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int y = 0; y < CHUNK_SIZE; ++y)

        for (int z = 0; z < CHUNK_SIZE; ++z) {

            _blocks[x][y][z] = NULL;

        }
    
};

/*
* block type configuration
*/
void Chunk::SetBlockType(int x, int y, int z, BlockType type) {
    try {

        Block* block = GetBlockByLocation(x, y, z);

        BlockFactory* factory = BlockFactory::GetInstance();

        factory->PointToBlockType(type, &block);

        _blocks[x][y][z] = block;

    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
};

/*
* Checking if location is valid inside chunk'area
* block go from 0 to ( CHUNK_SIZE - 1 )
* 
*/
bool Chunk::isLocationValidate(int x, int y, int z) {
    
    if ( (x >= CHUNK_SIZE || x < 0) ) {
        return false;
    }
    else if ( (y >= CHUNK_SIZE || y < 0) ) {
        return false;
    }
    else if ( (z >= CHUNK_SIZE || z < 0) ) {
        return false;
    }

    return true;
};

/*
* return block of chunk which is and pointer
* point to an block of BlockFactory
*
*/
Block* Chunk::GetBlockByLocation(int x, int y, int z) {

    if (isLocationValidate(x, y, z)) {

        return _blocks[x][y][z];

    }
    
    return NULL;
};

sf::Vector3i Chunk::GetChunkLocation()const { return _chunkId; };

void Chunk::SetChunkLocation(sf::Vector3i l ) { _chunkId = l; };

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
