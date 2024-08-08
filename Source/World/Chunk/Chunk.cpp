#include "world/chunk/Chunk.h"
#include "world/block/blockdatabase.h"
#include "world/block/blockfactory.h"
#include "world/worldcontant.h"

#include <random>
#include <iostream>

Chunk::Chunk(sf::Vector2i location )
    : _chunkId(location)
{ /* shoudl create blocks default */ }

Chunk::~Chunk() {};

bool Chunk::SetBlockType(int x, int y, int z, BlockType type) {
    Block* block = GetBlockByLocation(x,y,z);
    if (block != NULL) return false;

    delete block;
    sf::Vector3i location{x,y,z};
    block = BlockFactory::GetInstance()->CreateBlock(
        type, location, _chunkId);
};

const sf::Vector2i Chunk::GetChunkLocation()const {
    return _chunkId;
};

Block* Chunk::GetBlockByLocation(int x, int y, int z) {
    if (OutOfBoundValidate(x, y, z)) {
        return _blocks[x][y][z];
    }
    return NULL;
};

void Chunk::ProcessPosition(const sf::Vector3i& location ) {

    Block* block = BlockFactory::GetInstance()->CreateBlock(
        BlockType::Air, location , _chunkId
    );

    //BlockDatabase::GetInstance()->AddBlock ( location, block);
};

bool Chunk::OutOfBoundValidate(int x, int y, int z) {
    return (x < CHUNK_SIZE && x >= 0)
        && (y < CHUNK_SIZE && y >= 0)
        && (z < CHUNK_SIZE && z >= 0);
};

void Chunk::CreateChunk() {
    // look not very smart 
    for (float  x = 0; x < CHUNK_SIZE; ++x) {

        for (float  y = 0; y < CHUNK_SIZE; ++y) {

            for ( float z = 0; z < 2; ++z) {

                sf::Vector3f l{x,y,z};

                //ProcessPosition(l);

            }

        }
    }

    //std::cout << "size: " << 
    //    BlockDatabase::GetInstance()->CheckingSize() << std::endl;
};

//bool Chunk::OutOfBound() {};

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
