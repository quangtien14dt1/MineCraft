#include "world/chunk/Chunk.h"
#include "world/block/BlockDatabase.h"
#include "world/block/BlockFactory.h"
#include "world/WorldContant.h"

#include <random>
#include <iostream>

Chunk::Chunk()
    : _chunkId({ 1,1 })
{

}

Chunk::~Chunk() {};

void Chunk::SetBlockType(int x, int y, int z, uint8_t) {
    
};

void Chunk::ProcessPosition(const sf::Vector3f& location ) {

    Block* block = BlockFactory::GetInstance()->CreateBlock(
        BlockType::Air, location , _chunkId
    );

    BlockDatabase::GetInstance()->AddBlock ( location, block);
};

void Chunk::CreateChunk() {
    // look not very smart 
    for (float  x = 0; x < CHUNK_SIZE; ++x) {

        for (float  y = 0; y < CHUNK_SIZE; ++y) {

            for ( float z = 0; z < 2; ++z) {

                sf::Vector3f l{x,y,z};

                ProcessPosition(l);

            }

        }
    }

    //std::cout << "size: " << 
    //    BlockDatabase::GetInstance()->CheckingSize() << std::endl;
};

/* i dont know this shit @@ , never use before */
int Chunk::GenerateRandomId() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(1, 1000000);
    return dist(mt);
}
