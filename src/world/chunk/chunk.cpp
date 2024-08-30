#include "world/chunk/Chunk.h"
#include "world/block/blockdatabase.h"
#include "world/block/blockfactory.h"
#include <random>
#include <iostream>

Chunk::Chunk(sf::Vector3i location, BlockFactory* f)
    : _chunkId(location), _blockFactory(f)
{ 
    /* shoudl create blocks default */
    CreateChunk();
}

Chunk::~Chunk() {};

void Chunk::SetBlockType(int x, int y, int z,Block* b) {
    _blocks[x][y][z] = b;
};

void Chunk::SetBlockType(int x, int y, int z, BlockType type) {

    Block* block = GetBlockByLocation(x, y, z);

    block = _blockFactory->_blocksType[0];

    SetBlockType(x,y,z,block);
    
};

bool Chunk::OutOfBoundValidate(int x, int y, int z) {
    return (x < CHUNK_SIZE && x >= 0)
        && (y < CHUNK_AREA && y >= 0)
        && (z < CHUNK_SIZE && z >= 0);
};


void Chunk::CreateChunk() {
    // now much better
    for (int x = 0; x < CHUNK_SIZE; ++x) {

        for (int y = 0; y < CHUNK_AREA; ++y) {

            for (int z = 0; z < CHUNK_SIZE; ++z) {

                SetBlockType(x, y, z, BlockType::Grass );

            }

        }
    }
};

sf::Vector3i Chunk::GetChunkLocation()const {
    return _chunkId;
};

void Chunk::SetChunkLocation(sf::Vector3i l ) {
    this->_chunkId = l;
};

Block* Chunk::GetBlockByLocation(int x, int y, int z) {
    if (OutOfBoundValidate(x, y, z)) {
        return _blocks[x][y][z];
    }
};

//void Chunk::ProcessPosition(const sf::Vector3i& location ) {
//
//    Block* block = BlockFactory::GetInstance()->CreateBlock(
//        BlockType::Air, location , _chunkId
//    );
//
//    //BlockDatabase::GetInstance()->AddBlock ( location, block);
//};




//bool Chunk::OutOfBound() {};

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
